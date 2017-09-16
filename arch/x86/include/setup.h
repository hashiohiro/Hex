struct InitializeConfig
{
  unsigned char ReadSectors, KeyboardLEDs, VideoMode, Reserved;
  short ScreenX, ScreenY;
  unsigned char* VRAMOrigin;
};

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

void SetupOnStartup(struct InitializeConfig *config);
void InitializeGDT(void);
void InitializeIDT(void);
void InitializePalette(void);
void InitMouseCursor(char *mouse, char bc);
void InitScreen(unsigned char* vram, int screenx, int screeny);

void SetSegmentDescriptor(struct SegmentDescriptor *sd, unsigned int limit, int base, int ar);
void SetGateDescriptor(struct GateDescriptor *gd, int offset, int selector, int ar);
