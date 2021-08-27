#ifndef CHEF_BOARD_H
#define CHEF_BOARD_H

#include <stdint.h>

#define WHITE   0
#define BLACK   1

#define TOGGLE_BIT(bb, ind) (bb ^= 1ULL << ind)
#define BIT_IS_SET(bb, ind) ((bb >> ind) & 1ULL)
#define POP_BIT(bb, ind) (BIT_IS_SET(bb, ind) ? TOGGLE_BIT(bb, ind) : 0)

struct ChessBoard
{
    uint8_t side;
    uint8_t can_castle_kingside[2];
    uint8_t can_castle_queenside[2];

    char *en_passant_sqr;

    uint32_t halfmoves;
    uint32_t fullmoves;

    uint64_t rooks[2];
    uint64_t knights[2];
    uint64_t bishops[2];
    uint64_t queens[2];
    uint64_t kings[2];
    uint64_t pawns[2];
    uint64_t pieces[2];
};

struct ChessBoard *new_chessboard();
void print_bitboard(uint64_t bb);

#endif
