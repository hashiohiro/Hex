#include <hex32core.h>
#include <hex32kernel.h>
#include <hex32graphic.h>

extern char DEFBitmap[4096];

void HexMain(void)
{
  int i, MouseCursorX, MouseCursorY;
  char *vram;
  char mcursor[256];
  int screenx, screeny;
  struct LoaderConf *lconf;

  InitializePalette();

  lconf = (struct LoaderConf*) 0x0ff0;
  vram  = lconf->VRAMOrigin;
  screenx = lconf->ScreenX;
  screeny = lconf->ScreenY;

  InitScreen(vram, screenx, screeny);

  PutString(lconf->VRAMOrigin, lconf->ScreenX, 8, 8, COL8_ffffff, DEFBitmap, "ABC 123");
  PutString(lconf->VRAMOrigin, lconf->ScreenX, 31, 31, COL8_000000, DEFBitmap, "Hex OS.");
  PutString(lconf->VRAMOrigin, lconf->ScreenX, 30, 30, COL8_ffffff, DEFBitmap, "Hex OS.");


  InitMouseCursor(mcursor, COL8_008484);
  MouseCursorX = 100;
  MouseCursorY = 70;

  PutBMPImage(lconf->VRAMOrigin, lconf->ScreenX, 16, 16, MouseCursorX, MouseCursorY, mcursor, 16);

  for (;;)
  {
    OpHLT();
  }
}




