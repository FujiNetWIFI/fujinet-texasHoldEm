-- resettest.lua: console-RESET continuity. Join, soft-reset the console
-- mid-session, rejoin; the FUJINET_DEBUG transaction log must show the
-- sequence numbers CONTINUING across the reset (the client derives SEQ
-- from the cart's persisted ACKSEQ, never a local counter). The autoboot
-- script re-runs after a soft reset, so all timing is relative to this
-- run's start, and only the first run pulls the reset.
--   FUJINET_DEBUG=1 mame arcadia -cartslot fujinet -cart build/texas.bin \
--       -autoboot_script emu/resettest.lua -video none -sound none \
--       -seconds_to_run 40 -snapshot_directory build

local first = manager.machine.time.seconds < 1   -- run start vs re-run after reset
local phase = 0

local function seq()
    return manager.machine.devices[":maincpu"].spaces["program"]:read_u8(0x2C00)
end

local frames = 0
_G.SUB = emu.add_machine_frame_notifier(function()
    frames = frames + 1
    local t = frames / 60
    local col3 = manager.machine.ioport.ports[":controller1_col3"]
    if col3 == nil then return end
    if phase == 0 and t >= 3 then col3:field(0x01):set_value(1); phase = 1
    elseif phase == 1 and t >= 4 then col3:field(0x01):set_value(0); phase = 2
    elseif phase == 2 and t >= 8 then col3:field(0x01):set_value(1); phase = 3
    elseif phase == 3 and t >= 9 then col3:field(0x01):set_value(0); phase = 4
    elseif phase == 4 and t >= 14 then
        if first then
            emu.print_info("resettest: SOFT RESET at ackseq " .. seq())
            manager.machine:soft_reset()
            phase = 99          -- the re-run takes over
        else
            phase = 5
        end
    elseif phase == 5 and t >= 16 then
        emu.print_info("resettest: after rejoin, ackseq " .. seq())
        manager.machine.video:snapshot()
        phase = 6
    elseif phase == 6 then manager.machine:exit() end
end)
