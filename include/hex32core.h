#include <stdarg.h>

void OpCLI(void);
void OpSTI(void);
void OpSTIHLT(void);
int OpIn8(int port);
int OpIn16(int port);
int OpIn32(int port);
void OpOut8(int port, int data);
void OpOut16(int port, int data);
void OpOut32(int port, int data);
int LoadEFlags(void);
void StoreEFlags(int eflags);

void InitializePalette(void);
void PutFont(char *vram, int vramx, int x, int y, char color, char *font);
void PutString(char *vram, int vramx, int x, int y, char color, char *bmap, unsigned char *string);
void SetPalette(int start, int end, unsigned char *rgb);
void BoxFill(unsigned char* origin, int vramx, unsigned char value, int startx, int starty, int endx, int endy);
