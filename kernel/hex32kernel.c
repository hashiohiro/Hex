#include <hex32kernel.h>
#include <hex32corelib.h>
#include <hex32graphic.h>
#include <setup.h>

extern char DEFBitmap[4096];
extern char CURBitmap[16][16];

void HexMain(void)
{
  int i;
  struct InitializeConfig *iconf;

	iconf = (struct InitializeConfig*) 0x0ff0;
  SetupOnStartup(iconf);

  PutString(iconf->VRAMOrigin, iconf->ScreenX, 8, 8, COL8_ffffff, DEFBitmap, "ABC 123");
  PutString(iconf->VRAMOrigin, iconf->ScreenX, 31, 31, COL8_000000, DEFBitmap, "Hex OS.");
  PutString(iconf->VRAMOrigin, iconf->ScreenX, 30, 30, COL8_ffffff, DEFBitmap, "Hex OS.");


  

  for (;;)
  {
    OpHLT();
  }
}


