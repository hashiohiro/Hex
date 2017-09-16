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
