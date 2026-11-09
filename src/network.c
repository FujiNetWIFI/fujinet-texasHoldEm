// ColecoVision has its own: see src/coleco/network.c.
#ifndef BUILD_COLECO

#include <fujinet-network.h>

#include "platform-specific/network.h"

static uint8_t initialized = 0;

uint8_t getResponse(char *url, unsigned char *buffer, uint16_t max_len)
{
    int16_t count;

    if (!initialized) {
        if (network_init() != FN_ERR_OK)
            return 0;
        initialized = 1;
    }

    // network_read() on a unit that never opened returns whatever status it polls.
    if (network_open(url, OPEN_MODE_HTTP_GET_H, OPEN_TRANS_NONE) != FN_ERR_OK)
        return 0;

    count = network_read(url, buffer, max_len);
    network_close(url);

    return count > 0;
}

#endif /* BUILD_COLECO */
