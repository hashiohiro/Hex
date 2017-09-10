#include <hex32graphic.h>

extern char CURBitmap[16][16];

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

void BoxFill(unsigned char* origin, int vramx, unsigned char value, int startx, int starty, int endx, int endy)
{
  int x, y;
  for (y = starty; y <= endy; y++)
  {
    for (x = startx; x <= endx; x++)
    {
      origin[y * vramx + x] = value;
    }
  }

  return;
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

void PutFont(char *vram, int vramx, int x, int y, char color, char *font)
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

void PutBMPImage(char *vram, int vramx, int picturex, int picturey,
  int posx, int posy, char *bmap, int bufferx)
{
  int x, y;

  for (y = 0; y < picturey; y++)
  {
    for (x = 0; x < picturex; x++)
    {
      vram[(posy + y) * vramx + (posx + x)] = bmap[y * bufferx + x];
    }
  }
  return;
}

void PutString(char *vram, int vramx, int x, int y, char color, char *bmap, unsigned char *string)
{
  for (; *string != 0x00; string++)
  {
    PutFont(vram, vramx,  x, y, color, bmap + *string * 16);
    x += 8;
  }

  return;
}

void InitMouseCursor(char *mouse, char bc)
{
  int x, y;

  for (y = 0; y < 16; y++)
  {
    for (x = 0; x < 16; x++)
    {
      if (CURBitmap[y][x] == '*')
      {
        mouse[y * 16 + x] = COL8_000000;
      }

      if (CURBitmap[y][x] == 'O')
      {
        mouse[y * 16 + x] = COL8_ffffff;
      }

      if (CURBitmap[y][x] == '.')
      {
        mouse[y * 16 + x] = bc;
      }
    }
  }

  return;
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
