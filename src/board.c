#include "board.h"

#include <stdio.h>
#include <stdlib.h>

struct ChessBoard *new_chessboard()
{
    struct ChessBoard *cb = malloc(sizeof(struct ChessBoard));
    return cb;
}

void print_bitboard(uint64_t bb)
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int sqr = row * 8 + col;
            if (BIT_IS_SET(bb, sqr)) {
                printf("x");
            } else {
                printf("-");
            }
            printf(" ");
        }
        printf("\n");
    }

    return;
}
