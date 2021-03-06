#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_piece_provider.c"
#include "tetris_piece_collision_checker.c"
#include "tetris_game_settings.h"
#include "tetris_random_piece_provider.c"

u16 tetrisMatrix[GRID_COLUMNS][GRID_ROWS];
u16 rowsCleared[ROWS_MAX_CLEARED];
u16 rowStartPoint = 0;
u16 columnStartPoint = 5;
struct TetrisPiece *nextTetrisPiece;
struct TetrisPiece *currentTetrisPiece;

void updateMatrixSlot(u16 column, u16 row, bool value) {
    tetrisMatrix[column][row] = value;
}

void clearMatrixSlot() {
    for (u8 i = 0; i < GRID_COLUMNS; ++i) {
        for (u8 j = 0; j < GRID_ROWS; ++j) {
            tetrisMatrix[i][j] = FALSE;
        }
    }
}

u16 getNextRandomTetrisPiece() {
    return getRandomTetrisPieceUsingNesAlgorithm(currentTetrisPiece);
}

struct TetrisPiece *createTetrisPiece(u16 type) {
    if (type == TETRISPIECE_I) {
        return createTetrisPiece_I(columnStartPoint, rowStartPoint, 0);
    }
    else if (type == TETRISPIECE_O) {
        return createTetrisPiece_O(columnStartPoint, rowStartPoint, 0);
    } 
    else if (type == TETRISPIECE_T) {
        return createTetrisPiece_T(columnStartPoint, rowStartPoint, 0);
    }
    else if (type == TETRISPIECE_J) {
        return createTetrisPiece_J(columnStartPoint, rowStartPoint, 0);
    }
    else if (type == TETRISPIECE_L) {
        return createTetrisPiece_L(columnStartPoint, rowStartPoint, 0);
    }
    else if (type == TETRISPIECE_S) {
        return createTetrisPiece_S(columnStartPoint, rowStartPoint, 0);
    }
    else if (type == TETRISPIECE_Z) {
        return createTetrisPiece_Z(columnStartPoint, rowStartPoint, 0);
    }

    return createTetrisPiece_Z(columnStartPoint, rowStartPoint, 0); 
}

void putNextPieceOnTop() {
    u16 nextTetrisPieceType = getNextRandomTetrisPiece();

    if (nextTetrisPiece != NULL) {
        deleteTetrisPieceOnNextGUI(nextTetrisPiece);
        nextTetrisPieceType = nextTetrisPiece->type;
    }
 
    currentTetrisPiece  = createTetrisPiece(nextTetrisPieceType);       
    nextTetrisPieceType = getNextRandomTetrisPiece();
    nextTetrisPiece     = createTetrisPiece(nextTetrisPieceType);

    drawTetrisPiece(currentTetrisPiece);
    drawTetrisPieceOnNextGUI(nextTetrisPiece);
}

bool isCurrentTetrisPieceOnBottom() {
    return isTetrisPieceOnBottom(currentTetrisPiece);
} 

bool isCurrentTetrisPieceTouchingAnotherPieceOnBottom() {
    return isTetrisPieceTouchingAnotherPieceOnBottom(tetrisMatrix, currentTetrisPiece);
}

bool isCurrentTetrisPieceOnGameOverZone() {
    return isTetrisPieceOnGameOverZone(currentTetrisPiece);
}

void occupyMatrixSlotForTetrisPiece(struct TetrisPiece *tetrisPiece) {
    updateMatrixSlot(tetrisPiece->block0->column, tetrisPiece->block0->row, tetrisPiece->type);
    updateMatrixSlot(tetrisPiece->block1->column, tetrisPiece->block1->row, tetrisPiece->type);
    updateMatrixSlot(tetrisPiece->block2->column, tetrisPiece->block2->row, tetrisPiece->type);
    updateMatrixSlot(tetrisPiece->block3->column, tetrisPiece->block3->row, tetrisPiece->type);
}

void lockTetrisPieceOnBackground() {
    occupyMatrixSlotForTetrisPiece(currentTetrisPiece);
}

void updateTetrisPiecePosition() {
    deleteTetrisPiece(currentTetrisPiece);
    if (currentTetrisPiece->type == TETRISPIECE_I) {
        currentTetrisPiece 
            = createTetrisPiece_I(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_O) {
        currentTetrisPiece 
            = createTetrisPiece_O(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    } 
    else if (currentTetrisPiece->type == TETRISPIECE_T) {
        currentTetrisPiece 
            = createTetrisPiece_T(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_J) {
        currentTetrisPiece 
            = createTetrisPiece_J(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_L) {
        currentTetrisPiece 
            = createTetrisPiece_L(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_S) {
        currentTetrisPiece 
            = createTetrisPiece_S(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_Z) {
        currentTetrisPiece 
            = createTetrisPiece_Z(
                currentTetrisPiece->pivotColumn, 
                currentTetrisPiece->pivotRow, 
                currentTetrisPiece->rotationCount);
    }

    drawTetrisPiece(currentTetrisPiece);
}

bool canCurrentTetrisPieceRotate(int nextRotationCount) {
    if (currentTetrisPiece->type == TETRISPIECE_I) {
        return canRotateTetrisPiece_I(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_T) {
        return canRotateTetrisPiece_T(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_J) {
        return canRotateTetrisPiece_J(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_L) {
        return canRotateTetrisPiece_L(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_Z) {
        return canRotateTetrisPiece_Z(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }
    else if (currentTetrisPiece->type == TETRISPIECE_S) {
        return canRotateTetrisPiece_S(
            tetrisMatrix, currentTetrisPiece, nextRotationCount);
    }

    return FALSE;
}

int getNextAntiClockwiseRotationCount() {
    if (currentTetrisPiece->rotationCount + 1 >= 4) {
        return 0;
    }
    else {
        return currentTetrisPiece->rotationCount + 1;
    }
}

int getNextClockwiseRotationCount() {
    if (currentTetrisPiece->rotationCount - 1 <= -1 ) {
        return 3;
    }
    else {
        return currentTetrisPiece->rotationCount - 1;
    }
}

void rotateAntiClockwiseCurrentTetrisPiece() {
    int nextRotationCount = getNextAntiClockwiseRotationCount();

    if (canCurrentTetrisPieceRotate(nextRotationCount)) {
        currentTetrisPiece->rotationCount = nextRotationCount;
        updateTetrisPiecePosition();
    }
}

void rotateClockwiseCurrentTetrisPiece() {
    int nextRotationCount = getNextClockwiseRotationCount();

    if (canCurrentTetrisPieceRotate(nextRotationCount)) {
        currentTetrisPiece->rotationCount = nextRotationCount;
        updateTetrisPiecePosition();
    }
}

void moveCurrentTetrisPieceDown() {
    currentTetrisPiece->pivotRow++;
    updateTetrisPiecePosition();
}

void moveCurrentTetrisPieceLeft() {
    if (!isTetrisPieceOnLeftLimit(currentTetrisPiece)
        && !isTetrisPieceTouchingAnotherPieceOnLeft(tetrisMatrix, currentTetrisPiece)) {
        currentTetrisPiece->pivotColumn--;
        updateTetrisPiecePosition();
    }
}

void moveCurrentTetrisPieceRight() {
    if (!isTetrisPieceOnRightLimit(currentTetrisPiece)
        && !isTetrisPieceTouchingAnotherPieceOnRight(tetrisMatrix, currentTetrisPiece)) {
        currentTetrisPiece->pivotColumn++;
        updateTetrisPiecePosition();
    }
}

void moveDownTetrisRow(u16 row, u16 offset) {
    deleteSpritesOnRow(row);

    for (u16 column = 0; column < GRID_COLUMNS; ++column) {    
        if (row + offset < GRID_ROWS) {
            if (tetrisMatrix[column][row]) {
                u16 type = tetrisMatrix[column][row];
                drawTetrisTileOnGrid(column, row + offset, type);
                tetrisMatrix[column][row + offset] = tetrisMatrix[column][row];
            }
            else {
                tetrisMatrix[column][row + offset] = FALSE;
            }

            tetrisMatrix[column][row] = FALSE;
        }
    }
}

u16 getCompletedRowLinesCount() {
    setCompletedLinesCount(tetrisMatrix, rowsCleared, currentTetrisPiece);

    if (rowsCleared[0] != 0) {
        return 4;
    } 
    
    if (rowsCleared[1] != 0) {
        return 3;
    } 

    if (rowsCleared[2] != 0) {
        return 2;
    } 

    if (rowsCleared[3] != 0) {
        return 1;
    } 

    return 0;
}

void clearRows() {
    u16 rowCount = 0;
    u16 startPoint = 0;
    for (u16 x = 0; x < ROWS_MAX_CLEARED; ++x) {
        if (rowsCleared[x] != 0) {
            deleteSpritesOnRow(rowsCleared[x]);
            ++rowCount;
            startPoint = rowsCleared[x];
        }
    }

    startPoint -= rowCount;

    for (u16 i = startPoint; i > 0; --i) {
        moveDownTetrisRow(i, rowCount);
    }

    rowsCleared[0] = 0;
    rowsCleared[1] = 0;
    rowsCleared[2] = 0;
    rowsCleared[3] = 0;
}