#ifdef _CMOC_VERSION_

/*
  Platform specific utilities that don't fit in any category
*/
#include <cmoc.h>
#include <coco.h>
#include "hires.h"
#include <fujinet-fuji.h>

int lastCoCoKey=0;


void resetTimer()
{
  setTimer(0);
}

int getTime()
{
  return getTimer();
}

void waitvsync() {
    asm { sync } // wait for v-sync to change the palette and graphics mode
}

void quit()
{
  resetGraphics();
  fuji_set_boot_mode(FUJI_BOOT_MODE_LOBBY);
  coldStart();
}


unsigned char kbhit (void) {
    return (char)(lastCoCoKey || (lastCoCoKey=inkey()) || (lastCoCoKey=inkey()));
}

char cgetc (void) {
  int key=lastCoCoKey;

  lastCoCoKey=0;

  while (!key) {
    key=inkey();
  }

  return (char)key;
}



#endif
