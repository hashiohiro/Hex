#include <hex32core.h>
#include <hex32kernel.h>
#include <hex32graphic.h>


void InitializeGDT(void);
void InitializeIDT(void);

extern char DEFBitmap[4096];
struct SegmentDescriptor
{
  short LimitLow, BaseLow;
  char BaseMid, AccessRight;
  char LimitHigh, BaseHigh;
};

struct GateDescriptor
{
  short OffsetLow, Selector;
  char DwCount, AccessRight;
  short OffsetHigh;
};

void SetSegmentDescriptor(struct SegmentDescriptor *sd, unsigned int limit, int base, int ar);
void SetGateDescriptor(struct GateDescriptor *gd, int offset, int selector, int ar);


void HexMain(void)
{
  int i, MouseCursorX, MouseCursorY;
  char *vram;
  char mcursor[256];
  int screenx, screeny;
  struct LoaderConf *lconf;


	lconf = (struct LoaderConf*) 0x0ff0;
  vram  = lconf->VRAMOrigin;
  screenx = lconf->ScreenX;
  screeny = lconf->ScreenY;

	OpCLI();
	InitializeGDT();
	InitializeIDT();
  InitializePalette();
  InitScreen(vram, screenx, screeny);

  

	OpSTI();

  PutString(lconf->VRAMOrigin, lconf->ScreenX, 8, 8, COL8_ffffff, DEFBitmap, "ABC 123");
  PutString(lconf->VRAMOrigin, lconf->ScreenX, 31, 31, COL8_000000, DEFBitmap, "Hex OS.");
  PutString(lconf->VRAMOrigin, lconf->ScreenX, 30, 30, COL8_ffffff, DEFBitmap, "Hex OS.");


  InitMouseCursor(mcursor, COL8_008484);
  MouseCursorX = 100;
  MouseCursorY = 70;

  PutBMPImage(lconf->VRAMOrigin, lconf->ScreenX, 16, 16, MouseCursorX, MouseCursorY, mcursor, 16);

  for (;;)
  {
    OpHLT();
  }
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
