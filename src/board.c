#include "board.h"

#include <stdlib.h>

struct ChessBoard *new_chessboard()
{
    struct ChessBoard *cb = malloc(sizeof(struct ChessBoard));
    return cb;
}
