#define COL8_000000 0
#define COL8_ff0000 1
#define COL8_00ff00 2
#define COL8_ffff00 3
#define COL8_0000ff 4
#define COL8_ff00ff 5
#define COL8_00ffff 6
#define COL8_ffffff 7
#define COL8_c6c6c6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

// Draw
void PutFont(char *vram, int vramx, int x, int y, char color, char *font);
void PutBMPImage(char *vram, int vramx, int picturex, int picturey,
  int posx, int posy, char *bmap, int bufferx);
void PutString(char *vram, int vramx, int x, int y, char color, char *bmap, unsigned char *string);
void SetPalette(int start, int end, unsigned char *rgb);
void BoxFill(unsigned char* origin, int vramx, unsigned char value, int startx, int starty, int endx, int endy);
void PutBMPImage(char *vram, int vramx, int picturex, int picturey,
  int posx, int posy, char *bmap, int bufferx);
