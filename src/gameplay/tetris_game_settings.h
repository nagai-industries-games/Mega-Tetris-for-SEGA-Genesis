#ifndef TETRIS_GAME_SETTINGS_
#define TETRIS_GAME_SETTINGS_

#define GRID_ROWS        24
#define GRID_COLUMNS     10
#define ROWS_MAX_CLEARED 4

const u16 POINTS_SINGLE    = 40;
const u16 POINTS_DOUBLE    = 100;
const u16 POINTS_TRIPLE    = 300;
const u16 POINTS_TETRIS    = 1200;
const u16 POINTS_PER_LINES = 1;

#define PALETTE_TETRIS_PIECE 2
#define PALETTE_TETRIS_BACKGOUND 3

#define MAINMENUSTATE 0
#define GAMEPLAYSTATE 1

u8 currentGameState = MAINMENUSTATE;

#endif