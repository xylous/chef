/* Copyright (c) 2021 xylous <xylous.e@gmail.com>
 *
 * This file is part of chef.
 * chef is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * chef is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * chef.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "board.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Allocate memory for a `struct ChessBoard`, but don't initialise it
 */
struct ChessBoard *new_chessboard()
{
    struct ChessBoard *cb = malloc(sizeof(struct ChessBoard));
    return cb;
}

/**
 * Given a bitboard (64 bit unsigned long long), print its contents
 * Useful for debugging
 */
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

/**
 * Given a ChessBoard, turn it into a printable and semi-understandable string
 */
char *chessboard_to_string(struct ChessBoard *b)
{
    char *str = calloc(64, sizeof(char));

    for (int side = 0; side < 2; side++) {
        for (int i = 0; i < 64; i++) {
            if (BIT_IS_SET(b->rooks[side], i)) {
                if (side == WHITE)
                    str[i] = 'R';
                else
                    str[i] = 'r';
            } else if (BIT_IS_SET(b->knights[side], i)) {
                if (side == WHITE)
                    str[i] = 'N';
                else
                    str[i] = 'n';
            } else if (BIT_IS_SET(b->bishops[side], i)) {
                if (side == WHITE)
                    str[i] = 'B';
                else
                    str[i] = 'b';
            } else if (BIT_IS_SET(b->queens[side], i)) {
                if (side == WHITE)
                    str[i] = 'Q';
                else
                    str[i] = 'q';
            } else if (BIT_IS_SET(b->kings[side], i)) {
                if (side == WHITE)
                    str[i] = 'K';
                else
                    str[i] = 'k';
            } else if (BIT_IS_SET(b->pawns[side], i)) {
                if (side == WHITE)
                    str[i] = 'P';
                else
                    str[i] = 'p';
            }
        }
    }

    return str;
}
