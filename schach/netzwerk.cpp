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

void Netzwerk::sendMove(const MoveInfo& moveInfo) {

    QByteArray moveData;
    QDataStream stream(&moveData, QIODevice::WriteOnly);

    quint8 zusatzInfo = (moveInfo.promotion << 4) | (moveInfo.consequences & 0x0F);

    stream << quint8(0x03) << quint8(moveInfo.s_col)
           << quint8(moveInfo.s_row) << quint8(moveInfo.e_col)
           << quint8(moveInfo.e_row) << zusatzInfo;

    if(_socket && _socket->isOpen()) {
        _socket->write(moveData);
        emit logMessage("Move sent successfully.");
    } else {
        emit logMessage("Socket is not open, cannot send the move.");
    }

}

void Netzwerk::receiveMove() {
    QByteArray moveData = _socket->readAll();
    QDataStream stream(&moveData, QIODevice::ReadOnly);

    MoveInfo moveInfo;
    quint8 command;
    quint8 zusatzinfo;

    stream >> command; // receive command first and handle the message differently if it's a move, the start of the game, etc.
    if(command != 0x03) {
        emit logMessage("Not a valid move command.");
        return;
    }

    if(command == 0x03) {
        stream >> moveInfo.s_col >> moveInfo.s_row
               >> moveInfo.e_col >> moveInfo.e_row
               >> zusatzinfo;
        moveInfo.consequences = zusatzinfo & 0x0F; // Lower 4 bits for consequences
        moveInfo.promotion = (zusatzinfo >> 4) & 0x0F; // Upper 4 bits for promotion

        MoveInfo result = gameInstance->tryMove(moveInfo.s_col, moveInfo.s_row, moveInfo.e_col, moveInfo.e_row);
        if(!result.islegal) {
            emit logMessage("Received move is illegal!");
        } else {
            emit logMessage("Received valid move!");
        }

        emit moveReceived(moveInfo);
    }
}
