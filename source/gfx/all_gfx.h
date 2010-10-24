//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char again_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : again_Pal
extern const unsigned char easy_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : easy_Pal
extern const unsigned char hard_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : hard_Pal
extern const unsigned char impossible_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : impossible_Pal
extern const unsigned char normal_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : normal_Pal
extern const unsigned char oneplayer_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : oneplayer_Pal
extern const unsigned char spot_Sprite[12288] __attribute__ ((aligned (4))) ;  // Pal : spot_Pal
extern const unsigned char titlescreen_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : titlescreen_Pal
extern const unsigned char twoplayer_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : twoplayer_Pal
extern const unsigned char veryeasy_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : veryeasy_Pal

// Background files : 
extern const int board_Info[3]; // BgMode, Width, Height
extern const unsigned short board_Map[768] __attribute__ ((aligned (4))) ;  // Pal : board_Pal
extern const unsigned char board_Tiles[8320] __attribute__ ((aligned (4))) ;  // Pal : board_Pal
extern PAGfx_struct board; // background pointer

extern const int top_Info[3]; // BgMode, Width, Height
extern const unsigned short top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : top_Pal
extern const unsigned char top_Tiles[12992] __attribute__ ((aligned (4))) ;  // Pal : top_Pal
extern PAGfx_struct top; // background pointer

extern const int bottom_Info[3]; // BgMode, Width, Height
extern const unsigned short bottom_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bottom_Pal
extern const unsigned char bottom_Tiles[6144] __attribute__ ((aligned (4))) ;  // Pal : bottom_Pal
extern PAGfx_struct bottom; // background pointer


// Palette files : 
extern const unsigned short again_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short easy_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short hard_Pal[18] __attribute__ ((aligned (4))) ;
extern const unsigned short impossible_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short normal_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short oneplayer_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short spot_Pal[28] __attribute__ ((aligned (4))) ;
extern const unsigned short titlescreen_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short twoplayer_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short veryeasy_Pal[19] __attribute__ ((aligned (4))) ;
extern const unsigned short board_Pal[77] __attribute__ ((aligned (4))) ;
extern const unsigned short top_Pal[33] __attribute__ ((aligned (4))) ;
extern const unsigned short bottom_Pal[7] __attribute__ ((aligned (4))) ;


#endif

