#ifndef CHEF_BOARD_H
#define CHEF_BOARD_H

#include <stdint.h>

#define WHITE   0
#define BLACK   1

struct ChessBoard
{
    uint8_t  side;
    uint64_t rooks[2];
    uint64_t knights[2];
    uint64_t bishops[2];
    uint64_t queens[2];
    uint64_t kings[2];
    uint64_t pawns[2];
    uint64_t pieces[2];
};

struct ChessBoard *new_chessboard();

#endif
