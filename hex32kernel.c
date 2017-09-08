#include "hex32core.h"
#include "hex32kernel.h"

void HexMain(void)
{
  //char hoge[10] = {'H', 'E', 'X', 'H', 'E', 'R', 'E'};
  int i;
  char *p;

  InitializePalette();
  p = (char*) 0xa0000;

  BoxFill8(p, 320, COL8_ff0000, 20, 20, 120, 120);
  BoxFill8(p, 320, COL8_00ff00, 70, 50, 170, 150);
  BoxFill8(p, 320, COL8_0000ff, 120, 80, 220, 180);

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

void SetPalette(int start, int end, unsigned char *rgb)
{
  int i, eflags;
  eflags = LoadEFlags();
  OpCLI();
  OpOut8(0x03c8, start);
  for (i = start; i <= end; i++)
  {
    OpOut8(0x03c9, rgb[0] / 4);
    OpOut8(0x03c9, rgb[1] / 4);
    OpOut8(0x03c9, rgb[2] / 4);
    rgb += 3;
  }
  StoreEFlags(eflags);
  return;
}

void BoxFill8(unsigned char * vramOrigin, int maxWidth, unsigned char byteValue, int startX, int startY, int endX, int endY)
{
  int currentX, currentY;
  for (currentY = startY; currentY <= endY; currentY++)
  {
    for (currentX = startX; currentX <= endX; currentX++)
    {
      vramOrigin[currentY * maxWidth + currentX] = byteValue;
    }
    return ;
  }
}
