/**
 * @file game.h
 * @brief This file contains the declaration of the logik class which handles game logic.
 */

#ifndef LOGIK_H
#define LOGIK_H

class game;

/**
 * @class logik
 * @brief Handles the logic and rules for move validation in the chess game.
 */
class logik
{
public:

    /**
     * @brief Checks if a move is legal for a specific piece in the game.
     * @param game Reference to the current game instance.
     * @param s_col The starting column of the move.
     * @param s_row The starting row of the move.
     * @param e_col The ending column of the move.
     * @param e_row The ending row of the move.
     * @return True if the move is legal, otherwise false.
     */
    bool isLegal(const game& game, int s_col, int s_row, int e_col, int e_row) const;

};

#endif // LOGIK_H
