//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .c, for easier inclusion in a project

#ifdef __cplusplus
extern "C" {
#endif

#include "all_gfx.h"


// Sprite files : 
#include "again.c"
#include "easy.c"
#include "hard.c"
#include "impossible.c"
#include "normal.c"
#include "oneplayer.c"
#include "spot.c"
#include "titlescreen.c"
#include "twoplayer.c"
#include "veryeasy.c"

// Background files : 
#include "board.c"
#include "top.c"
#include "bottom.c"

// Palette files : 
#include "again.pal.c"
#include "easy.pal.c"
#include "hard.pal.c"
#include "impossible.pal.c"
#include "normal.pal.c"
#include "oneplayer.pal.c"
#include "spot.pal.c"
#include "titlescreen.pal.c"
#include "twoplayer.pal.c"
#include "veryeasy.pal.c"
#include "board.pal.c"
#include "top.pal.c"
#include "bottom.pal.c"

// Background Pointers :
PAGfx_struct board = {(void*)board_Map, 768, (void*)board_Tiles, 8320, (void*)board_Pal, (int*)board_Info };
PAGfx_struct top = {(void*)top_Map, 768, (void*)top_Tiles, 12992, (void*)top_Pal, (int*)top_Info };
PAGfx_struct bottom = {(void*)bottom_Map, 768, (void*)bottom_Tiles, 6144, (void*)bottom_Pal, (int*)bottom_Info };


#ifdef __cplusplus
}
#endif

