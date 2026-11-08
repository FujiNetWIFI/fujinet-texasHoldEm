#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#include <stdio.h>
#include <fujinet-fuji.h>

extern unsigned char oldmode;

#define FUJI_SIGNATURE   "FUJI"

typedef struct {
    uint8_t query;
    char    signature[4];
    uint8_t unit;
} fuji_ioctl_query;

static int find_slot_drive(int slot)
{
    int drive;
    union REGS regs;
    struct SREGS sregs;
    fuji_ioctl_query query;

    for (drive = 3; drive <= 26; drive++) {
        memset(&query, 0, sizeof(query));
        regs.h.ah = 0x44;
        regs.h.al = 0x04;
        regs.h.bl = (unsigned char)drive;
        regs.w.cx = sizeof(query);
        regs.x.dx = FP_OFF(&query);
        sregs.ds  = FP_SEG(&query);
        int86x(0x21, &regs, &regs, &sregs);
        if (!(regs.x.cflag & INTR_CF) &&
            memcmp(query.signature, FUJI_SIGNATURE, 4) == 0 &&
            query.unit == slot)
            return drive;
    }
    return -1;
}

// Screen specific player/bet coordinates
unsigned char playerXMaster[] = { 17,1, 1, 1, 15, 37,37, 37 };
unsigned char playerYMaster[] = { 18, 17, 10, 3, 2,3,10,17 };

char playerDirMaster[] = { 1,1,1,1,1,-1,-1,-1 };
// Texas Hold'em: mid-row seats (idx 2/6) anchor their bet/move text beside
// their own cards so nothing overlaps the community board (columns 15-24)
char playerBetXMaster[] = { 7,10,8,10,3,-8,-3,-4 };
char playerBetYMaster[] = { -2, -2, 1,4,5,4,1,-3 };

// Simple hard coded arrangement of players around the table based on player count.
// These refer to index positions in the Master arrays above
// Downside is new players will cause existing player positions to move.

//                               2                3                4
char playerCountIndex[] = {0,4,0,0,0,0,0,0, 0,2,6,0,0,0,0,0, 0,2,4,6,0,0,0,0,
// 5                6                 7                8
    0,2,3,5,6,0,0,0, 0,2,3,4,5,6,0,0,  0,2,3,4,5,6,7,0, 0,1,2,3,4,5,6,7};

static clock_t startClock;

void resetTimer() {
  startClock = clock();
}

int getTime() {
  return (int)((clock() - startClock) * 60 / CLOCKS_PER_SEC);
}

void quit()
{
	union REGS r;
	unsigned int total;
	int drive;

	r.h.ah = 0x00;
	r.h.al = oldmode;
	int86(0x10,&r,&r);

	printf("Loading Lobby...\n");
	fuji_set_boot_mode(FUJI_BOOT_MODE_LOBBY);

	// Disk reset, so DOS rereads the drive the lobby was mounted on.
	r.h.ah = 0x0D;
	int86(0x21,&r,&r);

	drive = find_slot_drive(0);
	if (drive < 0)
		return;

	_dos_setdrive(drive, &total);
	chdir("\\");
	spawnlp(P_OVERLAY, "COMMAND.COM", "COMMAND.COM", "/C", "AUTOEXEC.BAT", NULL);
}
