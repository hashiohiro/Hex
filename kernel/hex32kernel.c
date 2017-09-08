#include "hex32core.h"
#include "hex32kernel.h"

void HexMain(void)
{
  int i;
  char *vram;
  int xsize, ysize;

  InitializePalette();
  vram = (char*) 0xa0000;
  xsize = 320;
  ysize = 200;

  // GUI
  BoxFill8(vram, xsize, COL8_008484,          0,          0, xsize -  1, ysize - 29);
  BoxFill8(vram, xsize, COL8_c6c6c6,          0, ysize - 28, xsize -  1, ysize - 28);
  BoxFill8(vram, xsize, COL8_ffffff,          0, ysize - 27, xsize -  1, ysize - 27);
  BoxFill8(vram, xsize, COL8_c6c6c6,          0, ysize - 26, xsize -  1, ysize -  1);

  BoxFill8(vram, xsize, COL8_ffffff,          3, ysize - 24,         59, ysize - 24);
  BoxFill8(vram, xsize, COL8_ffffff,          2, ysize - 24,          2, ysize -  4);
  BoxFill8(vram, xsize, COL8_848484,          3, ysize -  4,         59, ysize -  4);
  BoxFill8(vram, xsize, COL8_848484,         59, ysize - 23,         59, ysize -  5);
  BoxFill8(vram, xsize, COL8_000000,          2, ysize -  3,         59, ysize -  3);
  BoxFill8(vram, xsize, COL8_000000,         60, ysize - 24,         60, ysize -  3);

  BoxFill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
  BoxFill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
  BoxFill8(vram, xsize, COL8_ffffff, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
  BoxFill8(vram, xsize, COL8_ffffff, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

  for (;;)
  {
    OpHLT();
  }
}


void InitializePalette(void)
{
  static unsigned char tableRgb[16 * 3] = {
    /*  0: 黒 */
    0x00, 0x00, 0x00,
    /*  1: 明るい赤 */
    0xff, 0x00, 0x00,
    /*  2: 明るい緑 */
    0x00, 0xff, 0x00,
    /*  3: 明るい黄色*/
    0xff, 0xff, 0x00,
    /*  4: 明るい青色*/
    0x00, 0x00, 0xff,
    /*  5: 明るい紫 */
    0xff, 0x00, 0xff,
    /*  6: 明るい水色 */
    0x00, 0xff, 0xff,
    /*  7: 白色*/
    0xff, 0xff, 0xff,
    /*  8: 明るい灰色 */
    0xc6, 0xc6, 0xc6,
    /*  9: 暗い赤色 */
    0x84, 0x00, 0x00,
    /* 10: 暗い緑色*/
    0x00, 0x84, 0x00,
    /* 11: 暗い黄色 */
    0x84, 0x84, 0x00,
    /* 12: 暗い青色 */
    0x00, 0x00, 0x84,
    /* 13: 暗い紫色 */
    0x84, 0x00, 0x84,
    /* 14: 暗い水色 */
    0x00, 0x84, 0x84,
    /* 15: 暗い灰色 */
    0x84, 0x84, 0x84
  };

  SetPalette(0, 15, tableRgb);
  return;
}
