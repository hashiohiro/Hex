#include <hex32corelib.h>

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


