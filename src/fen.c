#include "board.h"
#include "fen.h"

#include <stdlib.h>
#include <string.h>

int digit_from_char(char c);
void fen_piece_positions(struct ChessBoard **cb, char *str);
void fen_side_to_play(struct ChessBoard **cb, char *str);
void fen_castling_availability(struct ChessBoard **cb, char *str);

/**
 * Given a valid FEN string, return a ChessBoard whose state matches the one
 * described by said string
 */
struct ChessBoard *board_from_fen(char fen[])
{
    struct ChessBoard *cb = new_chessboard();
    char *positions = strtok(fen, " ");
    fen_piece_positions(&cb, positions);

    char *side = strtok(NULL, " ");
    fen_side_to_play(&cb, side);

    char *castling = strtok(NULL, " ");
    fen_castling_availability(&cb, castling);

    char *en_passant_sqr = strtok(NULL, " ");
    cb->en_passant_sqr = en_passant_sqr;

    char *halfmoves = strtok(NULL, " ");
    char *fullmoves = strtok(NULL, " ");
    cb->halfmoves = atoi(halfmoves);
    cb->fullmoves = atoi(fullmoves);

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
void fen_castling_availability(struct ChessBoard **cb, char *str)
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
void fen_side_to_play(struct ChessBoard **cb, char *str)
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
void fen_piece_positions(struct ChessBoard **cb, char *str)
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
