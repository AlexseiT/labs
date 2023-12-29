#ifndef UTILITY
#define UTILITY

#define MATRIX_SIZE 512
#define NUM_ELEMENTS (MATRIX_SIZE * MATRIX_SIZE)
#define BLOCK_SIZE 16 // programm crashes if > 22
#define TILE_DIM (BLOCK_SIZE * 2)
#define SCALAR 10

const bool PRINT_MODE = false;
#define FILE_OUTPUT false // change between true/false

#endif