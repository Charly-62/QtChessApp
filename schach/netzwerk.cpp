#include "netzwerk.h"

Netzwerk::Netzwerk(class Game* gameInstance, QObject *parent)
    : QObject{parent}, gameInstance(gameInstance) {

}

Netzwerk::~Netzwerk() {
    if(_socket) {
        delete _socket;
    }
}

void Netzwerk::initializeSocket() {
    if (!_socket) {
        _socket = new QTcpSocket(this);
    }
}

void Netzwerk::sendMove(int s_col, int s_row, int e_col, int e_row) {

}

void Netzwerk::receiveMove(QByteArray moveData) {

}
