#include "netzwerk.h"

netzwerk::netzwerk(class game* game)
    : game(game) {

}

void netzwerk::sendMove(int s_col, int s_row, int e_col, int e_row) {

}

void netzwerk::receiveMove(QByteArray moveData) {

}

void netzwerk::setGame(class game* game) {
    this->game = game;
}
