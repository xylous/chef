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
#include <stdlib.h>
#include <string.h>

int digit_from_char(char c);
void fen_decode_piece_positions(struct ChessBoard **cb, char *str);
void fen_decode_side_to_play(struct ChessBoard **cb, char *str);
void fen_decode_castling_availability(struct ChessBoard **cb, char *str);
char *fen_encode_piece_positions(struct ChessBoard *cb);
char *fen_encode_side_to_play(struct ChessBoard *cb);
char *fen_encode_castling_availability(struct ChessBoard *cb);
char *fen_encode_clock_info(struct ChessBoard *cb);

/**
 * Given a valid FEN string, return a ChessBoard whose state matches the one
 * described by said string
 */
struct ChessBoard *board_from_fen(char *str)
{
    /* `str` might be a string literal; strtok() needs a modifiable variable */
    char *fen = strdup(str);

    struct ChessBoard *cb = new_chessboard();
    char *positions = strtok(fen, " ");
    fen_decode_piece_positions(&cb, positions);

    char *side = strtok(NULL, " ");
    fen_decode_side_to_play(&cb, side);

    char *castling = strtok(NULL, " ");
    fen_decode_castling_availability(&cb, castling);

    char *en_passant_sqr = strtok(NULL, " ");
    cb->en_passant_sqr = en_passant_sqr;

    char *halfmoves = strtok(NULL, " ");
    char *fullmoves = strtok(NULL, " ");
    cb->halfmoves = atoi(halfmoves);
    cb->fullmoves = atoi(fullmoves);

    cb->pieces[WHITE] = pieces_bitboard(cb, WHITE);
    cb->pieces[BLACK] = pieces_bitboard(cb, BLACK);

    return cb;
}

/**
 * Given a char representing a digit, return the digit as an int
 */
int digit_from_char(char c)
{
    return c - '0';
}

/**
 * Helper function; update `cb` with castling availability, as per `str`
 */
void fen_decode_castling_availability(struct ChessBoard **cb, char *str)
{
    (*cb)->can_castle_kingside[WHITE] = 0;
    (*cb)->can_castle_queenside[WHITE] = 0;
    (*cb)->can_castle_kingside[BLACK] = 0;
    (*cb)->can_castle_queenside[BLACK] = 0;

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case 'K':
                (*cb)->can_castle_kingside[WHITE] = 1;
                break;
            case 'Q':
                (*cb)->can_castle_queenside[WHITE] = 1;
                break;
            case 'k':
                (*cb)->can_castle_kingside[BLACK] = 1;
                break;
            case 'q':
                (*cb)->can_castle_queenside[BLACK] = 1;
                break;
            case '-':
                return;
        }
    }
}

/**
 * Helper function; update the side to play in `cb`
 */
void fen_decode_side_to_play(struct ChessBoard **cb, char *str)
{
    if (*str == 'w') {
        (*cb)->side = WHITE;
    } else {
        (*cb)->side = BLACK;
    }
}

/**
 * Helper function; update piece positions as per `str`
 */
void fen_decode_piece_positions(struct ChessBoard **cb, char *str)
{
    int sqr = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            // in FEN, white side has uppercase letters
            case 'P':
                TOGGLE_BIT((*cb)->pawns[WHITE], sqr);
                break;
            case 'R':
                TOGGLE_BIT((*cb)->rooks[WHITE], sqr);
                break;
            case 'N':
                TOGGLE_BIT((*cb)->knights[WHITE], sqr);
                break;
            case 'B':
                TOGGLE_BIT((*cb)->bishops[WHITE], sqr);
                break;
            case 'Q':
                TOGGLE_BIT((*cb)->queens[WHITE], sqr);
                break;
            case 'K':
                TOGGLE_BIT((*cb)->kings[WHITE], sqr);
                break;

            // ...and black side has lowercase letters
            case 'p':
                TOGGLE_BIT((*cb)->pawns[BLACK], sqr);
                break;
            case 'r':
                TOGGLE_BIT((*cb)->rooks[BLACK], sqr);
                break;
            case 'n':
                TOGGLE_BIT((*cb)->knights[BLACK], sqr);
                break;
            case 'b':
                TOGGLE_BIT((*cb)->bishops[BLACK], sqr);
                break;
            case 'q':
                TOGGLE_BIT((*cb)->queens[BLACK], sqr);
                break;
            case 'k':
                TOGGLE_BIT((*cb)->kings[BLACK], sqr);
                break;

            case '/':
                // note: '- 1', because it's going to be incremented anyways
                sqr -= 1;
                break;
            default:
                // note: '- 1', because it's going to be incremented anyways
                sqr += digit_from_char(str[i]) - 1;
                break;
        }
        sqr += 1;
    }

    return;
}

/**
 * Helper function: create a string containing the piece positions
 */
char *fen_encode_piece_positions(struct ChessBoard *b)
{
    char *str = calloc(64, sizeof(char));
    int seen_block = 0;
    int seen_blanks = 0;
    uint64_t pieces_heatmap = b->pieces[WHITE] ^ b->pieces[BLACK];

    for (int i = 0; i < 64; i++) {
        for (int side = 0; side < 2; side++) {
            if (BIT_IS_SET(b->rooks[side], i)) {
                if (side == WHITE)
                    strcat(str, "R");
                else
                    strcat(str, "r");
            } else if (BIT_IS_SET(b->knights[side], i)) {
                if (side == WHITE)
                    strcat(str, "N");
                else
                    strcat(str, "n");
            } else if (BIT_IS_SET(b->bishops[side], i)) {
                if (side == WHITE)
                    strcat(str, "B");
                else
                    strcat(str, "b");
            } else if (BIT_IS_SET(b->queens[side], i)) {
                if (side == WHITE)
                    strcat(str, "Q");
                else
                    strcat(str, "q");
            } else if (BIT_IS_SET(b->kings[side], i)) {
                if (side == WHITE)
                    strcat(str, "K");
                else
                    strcat(str, "k");
            } else if (BIT_IS_SET(b->pawns[side], i)) {
                if (side == WHITE)
                    strcat(str, "P");
                else
                    strcat(str, "p");
            }
        }
        seen_block++;

        if (!BIT_IS_SET(pieces_heatmap, i)) {
            seen_blanks++;
        }

        if (seen_blanks > 0
                && (seen_block == 8
                    || BIT_IS_SET(pieces_heatmap, (i+1)))) {
            char digit = seen_blanks + '0';
            strcat(str, &digit);
            seen_blanks = 0;
        }

        if (seen_block == 8 && i != 63) {
            strcat(str, "/");
            seen_block = 0;
        }
    }

    return str;
}

/**
 * Helper function: return a part of the FEN string for the side to play
 */
char *fen_encode_side_to_play(struct ChessBoard *cb)
{
    if (cb->side == WHITE)
        return "w";
    else
        return "b";
}

/**
 * Helper function: return a part of the FEN string for the castling
 * availability
 */
char *fen_encode_castling_availability(struct ChessBoard *cb)
{
    char *str = calloc(5, sizeof(char));

    if (cb->can_castle_kingside[WHITE]) {
        strcat(str, "K");
    }
    if (cb->can_castle_queenside[WHITE]) {
        strcat(str, "Q");
    }
    if (cb->can_castle_kingside[BLACK]) {
        strcat(str, "k");
    }
    if (cb->can_castle_queenside[BLACK]) {
        strcat(str, "q");
    }

    // check if there isn't castling availability
    if (strlen(str) == 0) {
        str[0] = '-';
    };

    return str;
}

/**
 * Helper function: return a part of the FEN string with clock/move information
 */
char *fen_encode_clock_info(struct ChessBoard *cb)
{
    char *str = calloc(10, sizeof(char));

    sprintf(str, "%d %d", cb->halfmoves, cb->fullmoves);

    return str;
}
