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

  PutFont8(lconf->VRAMOrigin, lconf->ScreenX,  8, 8, COL8_ffffff, DEFBitmap + 'A' * 16);
  PutFont8(lconf->VRAMOrigin, lconf->ScreenX, 16, 8, COL8_ffffff, DEFBitmap + 'B' * 16);
  PutFont8(lconf->VRAMOrigin, lconf->ScreenX, 24, 8, COL8_ffffff, DEFBitmap + 'C' * 16);
  PutFont8(lconf->VRAMOrigin, lconf->ScreenX, 40, 8, COL8_ffffff, DEFBitmap + '1' * 16);
  PutFont8(lconf->VRAMOrigin, lconf->ScreenX, 48, 8, COL8_ffffff, DEFBitmap + '2' * 16);
  PutFont8(lconf->VRAMOrigin, lconf->ScreenX, 56, 8, COL8_ffffff, DEFBitmap + '3' * 16);


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

void PutFont8(char *vram, int vramx, int x, int y, char color, char *font)
{
  int i;
  char *p, data;
  for (i = 0; i < 16; i++)
  {
    p = vram + (y + i) * vramx + x;
    data = font[i];
    if ((data & 0x80) != 0) { p[0] = color; }
    if ((data & 0x40) != 0) { p[1] = color; }
    if ((data & 0x20) != 0) { p[2] = color; }
    if ((data & 0x10) != 0) { p[3] = color; }
    if ((data & 0x08) != 0) { p[4] = color; }
    if ((data & 0x04) != 0) { p[5] = color; }
    if ((data & 0x02) != 0) { p[6] = color; }
    if ((data & 0x01) != 0) { p[7] = color; }
  }

  return;
}
