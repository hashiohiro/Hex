#include <hex32core.h>
#include <hex32kernel.h>

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


  for (;;)
  {
    OpHLT();
  }
}

void InitializePalette(void)
{
  static unsigned char tableRgb[16 * 3] = {
    /*  0: Black           */
    0x00, 0x00, 0x00,
    /*  1: Light Red       */
    0xff, 0x00, 0x00,
    /*  2: Light Green     */
    0x00, 0xff, 0x00,
    /*  3: Light Yellow    */
    0xff, 0xff, 0x00,
    /*  4: Light Blue      */
    0x00, 0x00, 0xff,
    /*  5: Light Purple    */
    0xff, 0x00, 0xff,
    /*  6: Light Aqua Blue */
    0x00, 0xff, 0xff,
    /*  7: White           */
    0xff, 0xff, 0xff,
    /*  8: Light Glay      */
    0xc6, 0xc6, 0xc6,
    /*  9: Dark Red        */
    0x84, 0x00, 0x00,
    /* 10: Dark Green      */
    0x00, 0x84, 0x00,
    /* 11: Dark Yellow     */
    0x84, 0x84, 0x00,
    /* 12: Dark Blue       */
    0x00, 0x00, 0x84,
    /* 13: Dark Purple     */
    0x84, 0x00, 0x84,
    /* 14: Dark Aqua Color */
    0x00, 0x84, 0x84,
    /* 15: Dark Glay       */
    0x84, 0x84, 0x84
  };

  SetPalette(0, 15, tableRgb);
  return;
}

void InitScreen(unsigned char* vram, int screenx, int screeny)
{
  BoxFill8(vram, screenx, COL8_008484,            0,            0, screenx -  1, screeny - 29);
  BoxFill8(vram, screenx, COL8_c6c6c6,            0, screeny - 28, screenx -  1, screeny - 28);
  BoxFill8(vram, screenx, COL8_ffffff,            0, screeny - 27, screenx -  1, screeny - 27);
  BoxFill8(vram, screenx, COL8_c6c6c6,            0, screeny - 26, screenx -  1, screeny -  1);

  BoxFill8(vram, screenx, COL8_ffffff,            3, screeny - 24,           59, screeny - 24);
  BoxFill8(vram, screenx, COL8_ffffff,            2, screeny - 24,            2, screeny -  4);
  BoxFill8(vram, screenx, COL8_848484,            3, screeny -  4,           59, screeny -  4);
  BoxFill8(vram, screenx, COL8_848484,           59, screeny - 23,           59, screeny -  5);
  BoxFill8(vram, screenx, COL8_000000,            2, screeny -  3,           59, screeny -  3);
  BoxFill8(vram, screenx, COL8_000000,           60, screeny - 24,           60, screeny -  3);

  BoxFill8(vram, screenx, COL8_848484, screenx - 47, screeny - 24, screenx -  4, screeny - 24);
  BoxFill8(vram, screenx, COL8_848484, screenx - 47, screeny - 23, screenx - 47, screeny -  4);
  BoxFill8(vram, screenx, COL8_ffffff, screenx - 47, screeny -  3, screenx -  4, screeny -  3);
  BoxFill8(vram, screenx, COL8_ffffff, screenx -  3, screeny - 24, screenx -  3, screeny -  3);
  return;
}
