#include <hex32graphic.h>
#include <setup.h>

extern char CURBitmap[16][16];

void SetupOnStartup(struct InitializeConfig *iconf)
{
  int mouseCursorX, mouseCursorY;
  char mcursor[256];

  OpCLI();

  // GDT・IDT Setup
	InitializeGDT();
	InitializeIDT();

  // Graphic Setup
  InitializePalette();
  InitScreen(iconf->VRAMOrigin, iconf->ScreenX, iconf->ScreenY);

  // Mouse Cursor Setup
  InitMouseCursor(mcursor, COL8_008484);
  mouseCursorX = 100;
  mouseCursorY = 70;
  PutBMPImage(iconf->VRAMOrigin, iconf->ScreenX, 16, 16, mouseCursorX, mouseCursorY, mcursor, 16);

	OpSTI();

  return;
}

void InitializeGDT(void)
{
  struct SegmentDescriptor *gdt = (struct SegmentDescriptor *) 0x00270000;

  int i;

  /* GDTを初期化する */
  for (i = 0; i < 8192; i++)
  {
    SetSegmentDescriptor(gdt + i, 0, 0, 0);
  }

  SetSegmentDescriptor(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
  SetSegmentDescriptor(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
  LoadGDTR(0xffff, 0x00270000);

  return;
}

void InitializeIDT(void)
{
  struct GateDescriptor *idt = (struct GateDescriptor *) 0x0026f800;

  int i;
	/* IDTを初期化する */
  for (i = 0; i < 256; i++)
  {
    SetGateDescriptor(idt + i, 0, 0, 0);
  }
  LoadIDTR(0x7ff, 0x0026f800);

  return;
}

void SetSegmentDescriptor(struct SegmentDescriptor *sd, unsigned int limit, int base, int ar)
{
  if (limit > 0xffffff)
  {
    ar |= 0x8000; /* G_bit = 1; */
    limit /= 0x1000;
  }

  sd->LimitLow = limit & 0xffff;
  sd->BaseLow = base & 0xffff;
  sd->BaseMid = (base >> 16) & 0xff;
  sd->LimitHigh = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
  sd->BaseHigh = (base >> 24) & 0xff;

  return;
}

void SetGateDescriptor(struct GateDescriptor *gd, int offset, int selector, int ar)
{
  gd->OffsetLow = offset & 0xffff;
  gd->Selector = selector;
  gd->DwCount = (ar >> 8) & 0xff;
  gd->AccessRight = ar & 0xff;
  gd->OffsetHigh = (offset >> 16) & 0xffff;

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
