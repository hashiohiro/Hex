#include <hex32core.h>
#include <hex32kernel.h>
#include "../fonts/default.c"

void HexMain(void)
{
  int i;
  char *vram;
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

  for (;;)
  {
    OpHLT();
  }
}

void InitScreen(unsigned char* vram, int screenx, int screeny)
{
  BoxFill(vram, screenx, COL8_008484,            0,            0, screenx -  1, screeny - 29);
  BoxFill(vram, screenx, COL8_c6c6c6,            0, screeny - 28, screenx -  1, screeny - 28);
  BoxFill(vram, screenx, COL8_ffffff,            0, screeny - 27, screenx -  1, screeny - 27);
  BoxFill(vram, screenx, COL8_c6c6c6,            0, screeny - 26, screenx -  1, screeny -  1);

  BoxFill(vram, screenx, COL8_ffffff,            3, screeny - 24,           59, screeny - 24);
  BoxFill(vram, screenx, COL8_ffffff,            2, screeny - 24,            2, screeny -  4);
  BoxFill(vram, screenx, COL8_848484,            3, screeny -  4,           59, screeny -  4);
  BoxFill(vram, screenx, COL8_848484,           59, screeny - 23,           59, screeny -  5);
  BoxFill(vram, screenx, COL8_000000,            2, screeny -  3,           59, screeny -  3);
  BoxFill(vram, screenx, COL8_000000,           60, screeny - 24,           60, screeny -  3);

  BoxFill(vram, screenx, COL8_848484, screenx - 47, screeny - 24, screenx -  4, screeny - 24);
  BoxFill(vram, screenx, COL8_848484, screenx - 47, screeny - 23, screenx - 47, screeny -  4);
  BoxFill(vram, screenx, COL8_ffffff, screenx - 47, screeny -  3, screenx -  4, screeny -  3);
  BoxFill(vram, screenx, COL8_ffffff, screenx -  3, screeny - 24, screenx -  3, screeny -  3);
  return;
}
