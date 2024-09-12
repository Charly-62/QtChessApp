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
        connect(_socket, &QTcpSocket::readyRead, this, &Netzwerk::receiveMove);
    }
}

void Netzwerk::sendGameStart(bool ServerStarts) {

    QByteArray gameStartMessage;
    QDataStream stream(&gameStartMessage, QIODevice::WriteOnly);

    stream << quint8(0x01) << quint8(0x02)
           << quint8(ServerStarts) << quint8(0x01);

    _socket->write(gameStartMessage);
    _socket->flush();

}

void Netzwerk::sendMove(const MoveInfo& moveInfo) {
    QByteArray moveData;
    QDataStream stream(&moveData, QIODevice::WriteOnly);

    quint8 zusatzInfo = (moveInfo.promotion << 4) | (moveInfo.consequences & 0x0F);

    stream << quint8(0x03)
           << quint8(0x05)
           << quint8(moveInfo.s_col)
           << quint8(moveInfo.s_row)
           << quint8(moveInfo.e_col)
           << quint8(moveInfo.e_row)
           << zusatzInfo;

    moveData.toHex();

    if(_socket && _socket->isOpen()) {
        _socket->write(moveData);
        _socket->flush();
        qDebug() << "Move sent: " << moveData;
        emit logMessage("Move sent successfully.");
    } else {
        emit logMessage("Socket is not open, cannot send the move.");
    }

}

void Netzwerk::receiveMove() {
    QByteArray moveData = _socket->readAll();
    QDataStream stream(&moveData, QIODevice::ReadOnly);

    MoveInfo moveInfo;
    quint8 length, command;

    stream >> command; // receive command first and handle the message differently if it's a move, the start of the game, etc.

    // Game Start command
    if(command == 0x01) {
        quint8 StartingPlayer, groupNumber;
        stream >> length >> StartingPlayer >> groupNumber;

        QString group = QString::number(groupNumber);
        emit gameStarted(StartingPlayer & 1, group);
    }

    // Move command
    if(command == 0x03) {
        quint8 startCol, startRow, endCol, endRow, zusatzinfo; // store received data in to quint8

        stream >> length
               >> startCol
               >> startRow
               >> endCol
               >> endRow
               >> zusatzinfo;

        moveInfo.s_col = static_cast<int> (startCol);
        moveInfo.s_row = static_cast<int> (startRow);
        moveInfo.e_col = static_cast<int> (endCol);
        moveInfo.e_row = static_cast<int> (endRow);

        moveInfo.consequences = static_cast<int> (zusatzinfo & 0x0F); // Lower 4 bits for consequences
        moveInfo.promotion = static_cast<int> ((zusatzinfo >> 4) & 0x0F); // Upper 4 bits for promotion

        qDebug() << "Move received: " << "Length: " << length << ", s_col: " << moveInfo.s_col << ", s_row: " << moveInfo.s_row << ", e_col: " << moveInfo.e_col << ", e_row: " << moveInfo.e_row << ", zusatzinfo: " << zusatzinfo;

        moveInfo.islegal = gameInstance->logikInstance.isLegal(gameInstance, startCol, startRow, endCol, endRow);

        if(!moveInfo.islegal) {
            emit logMessage("Received move is illegal!");
            return;
        } else {
            emit logMessage("Received valid move.");
        }

        emit moveReceived(moveInfo);
    }
}
