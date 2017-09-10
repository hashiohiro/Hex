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

void PutString(char *vram, int vramx, int x, int y, char color, char *bmap, unsigned char *string)
{
  for (; *string != 0x00; string++)
  {
    PutFont(vram, vramx,  x, y, color, bmap + *string * 16);
    x += 8;
  }

  return;
}
