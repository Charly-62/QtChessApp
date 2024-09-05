#include "netzwerk.h"

Netzwerk::Netzwerk(class Game* gameInstance)
    : gameInstance(gameInstance) {

}

void Netzwerk::sendMove(int s_col, int s_row, int e_col, int e_row) {

}

void Netzwerk::receiveMove(QByteArray moveData) {

}

void Netzwerk::setGame(class Game* gameInstance) {
    this->gameInstance = gameInstance;
}
