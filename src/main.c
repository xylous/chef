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
#include "fen.h"

#include <stdio.h>
#include <string.h>

#define DEFAULT_FEN_STRING "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

void print_help_message()
{
    printf("chef, v0.1.0\n");

    return;
}

int main(int argc, char *argv[])
{
    print_help_message();

    /*struct ChessBoard *b = board_from_fen(DEFAULT_FEN_STRING);*/
    /*print_chessboard(b);*/

    return 0;
}
