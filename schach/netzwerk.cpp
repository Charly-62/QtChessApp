#include "netzwerk.h"

netzwerk::netzwerk(class game* gameInstance)
    : gameInstance(gameInstance) {

}

void netzwerk::sendMove(int s_col, int s_row, int e_col, int e_row) {

}

void netzwerk::receiveMove(QByteArray moveData) {

}

void netzwerk::setGame(class game* gameInstance) {
    this->gameInstance = gameInstance;
}
