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
           << quint8(!ServerStarts) << quint8(0x01);

    _socket->write(gameStartMessage);
    _socket->flush();

}

void Netzwerk::sendUndo() {
    QByteArray UndoMessage;
    QDataStream stream(&UndoMessage, QIODevice::WriteOnly);

    stream << quint8(0x05) << quint8(0x01) << quint8(0x01);

    _socket->write(UndoMessage);
    _socket->flush();
}

void Netzwerk::sendUndoResponse(bool accepted) {
    QByteArray responseMessage;
    QDataStream stream(&responseMessage, QIODevice::WriteOnly);

    stream << quint8(0x06) << quint8(0x01) << quint8(accepted);

    _socket->write(responseMessage);
    _socket->flush();
}

void Netzwerk::sendMove(const MoveInfo& moveInfo) {
    QByteArray moveData;
    QDataStream stream(&moveData, QIODevice::WriteOnly);

    quint8 zusatzInfo = (moveInfo.promotion << 4) | (moveInfo.consequences & 0x0F);
    qDebug() << "Sending Move - zusatzInfo: " << QString::number(zusatzInfo, 16).toUpper();

    stream << quint8(0x03)
           << quint8(0x05)
           << quint8(moveInfo.s_col)
           << quint8(moveInfo.s_row)
           << quint8(moveInfo.e_col)
           << quint8(moveInfo.e_row)
           << zusatzInfo;

    if (_socket && _socket->isOpen()) {
        qint64 bytesWritten = 0;
        while (bytesWritten < moveData.size()) {
            qint64 result = _socket->write(moveData.mid(bytesWritten));  // Write remaining bytes
            if (result == -1) {
                emit logInGameMsg("Could not send move.");
                return;
            }
            bytesWritten += result;
        }

        qDebug() << "Move sent: " << moveData.toHex();
        emit logInGameMsg("Move sent successfully.");
        _socket->flush();
    } else {
        emit logInGameMsg("Socket is not open, cannot send the move.");
    }
}

void Netzwerk::receiveMove() {

    const int MAX_PACKET_SIZE = 7;

    if (_socket->bytesAvailable() > MAX_PACKET_SIZE) {
        emit logInGameMsg("Packet too large, possible attack. Disconnecting.");
        _socket->disconnect();
        return;
    }

    QByteArray moveData = _socket->readAll();
    buffer.append(moveData);

    while(true) {

        if (buffer.size() < 2) {
            break; // Not enough data for command yet
        }

        QDataStream stream(buffer);
        quint8 length, command;

        stream >> command >> length; // receive command first and handle the message differently if it's a move, the start of the game, etc.

        int expectedSize = 2 + length;

        if(buffer.size() < expectedSize) {
            break; // Not enough data yet
        }

        QByteArray messageData = buffer.left(expectedSize);

        buffer.remove(0, expectedSize);

        QDataStream messageStream(messageData);
        processMessage(messageStream);
    }
}

void Netzwerk::processMessage(QDataStream& stream) {

    quint8 command, length;

    stream >> command >> length;

    // Game Start command
    if(command == 0x01) {
        if(length != 2) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        quint8 StartingPlayer, groupNumber;
        stream >> StartingPlayer >> groupNumber;
        opponentgroup = groupNumber;

        QString group = QString::number(groupNumber);
        bool ServerStarts = !StartingPlayer;
        emit gameStarted(ServerStarts, group);

        sendGameStartResponse();
    }

    // Game Start Response command
    else if(command == 0x02) {
        if(length != 1) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }
        quint8 groupNumber;
        stream >> groupNumber;
        opponentgroup = groupNumber;
        emit logInGameMsg("Playing against Group " + QString::number(groupNumber));
    }

    // Move command
    else if(command == 0x03) {
        if(length != 5) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        quint8 startCol, startRow, endCol, endRow, zusatzinfo; // store received data in to quint8

        stream >> startCol
               >> startRow
               >> endCol
               >> endRow
               >> zusatzinfo;

        if (startCol >= 8 || startRow >= 8 || endCol >= 8 || endRow >= 8) {
            emit logInGameMsg("Invalid position values in Move message.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
            return;
        }

        MoveInfo moveInfo;

        moveInfo.s_col = static_cast<int> (startCol);
        moveInfo.s_row = static_cast<int> (startRow);
        moveInfo.e_col = static_cast<int> (endCol);
        moveInfo.e_row = static_cast<int> (endRow);

        moveInfo.consequences = static_cast<int> (zusatzinfo & 0x0F); // Lower 4 bits for consequences
        moveInfo.promotion = static_cast<int> ((zusatzinfo >> 4) & 0x0F); // Upper 4 bits for promotion

        qDebug() << "Move received: " << "Length: " << length
                         << ", s_col: " << moveInfo.s_col
                         << ", s_row: " << moveInfo.s_row
                         << ", e_col: " << moveInfo.e_col
                         << ", e_row: " << moveInfo.e_row
                         << ", zusatzinfo: " << QString::number(zusatzinfo, 16).toUpper()
                         << ", promotion: " << QString::number(moveInfo.promotion, 16).toUpper();

        quint8 statusCode;

        moveInfo.islegal = gameInstance->logikInstance.isLegal(gameInstance, startCol, startRow, endCol, endRow, moveInfo.promotion);

        if(!moveInfo.islegal) {
            emit logInGameMsg("Received move is illegal!");
            return;
        } else {
            emit logInGameMsg("Received valid move.");

            // Determine the status code based on move consequences
            if (moveInfo.consequences & 0x02) { // Checkmate
                statusCode = 0x02; // OK, checkmate
            } else if (moveInfo.consequences & 0x01) { // Capture
                statusCode = 0x01; // OK, capture
            } else {
                statusCode = 0x00; // OK
            }

            emit moveReceived(moveInfo);
            sendMoveResponse(statusCode);
        }
    }

    // Move response command
    else if(command == 0x04) {
        if(length != 1) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }
        quint8 status;
        stream >> status;

        switch(status) {
            case 0x00:
                emit logInGameMsg("Move accepted.");
                break;
            case 0x01:
                emit logInGameMsg("Move accepted with capture.");
                break;
            case 0x02:
                emit logInGameMsg("Move accepted with checkmate.");
                break;
            case 0x03:
                emit logInGameMsg("Move rejected: No piece at start position.");
                break;
            case 0x04:
                emit logInGameMsg("Move rejected: Move not allowed.");
                break;
            case 0x06:
                emit logInGameMsg("Move rejected: No capture made.");
                break;
            case 0x07:
                emit logInGameMsg("Move rejected: Not your turn.");
                break;
            case 0x08:
                emit logInGameMsg("Move rejected: No checkmate.");
                break;
            default:
                emit logInGameMsg("Unknown move response received.");
                break;
        }
    }

    // Undo move command
    else if(command == 0x05) {
        if(length != 1) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }
        quint8 groupNumber;
        stream >> groupNumber;
        if(groupNumber == 1) {
            qDebug() << "Undo last move requested";
            undoMovetmp = true;
            emit undoMove();
        }
    }

    // Undo move response command
    else if(command == 0x06) {
        if(length != 1) {
            emit logInGameMsg("Invalid message length.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }
        quint8 accepted;
        stream >> accepted;
        qDebug() << "Undo received" << accepted;
        emit undoAccepted(accepted);
    }

    // Unvalid command
    else {
        emit logInGameMsg("Invalid command received.");
        emit logInGameMsg("Disconnecting for safety.");
        _socket->disconnect();
    }
}

void Netzwerk::sendGameStartResponse() {
    QByteArray responseMessage;
    QDataStream stream(&responseMessage, QIODevice::WriteOnly);

    stream << quint8(0x02) << quint8(0x01)
           << quint8(0x01);

    _socket->write(responseMessage);
    _socket->flush();
}

void Netzwerk::sendMoveResponse(quint8 status) {
    QByteArray responseMessage;
    QDataStream stream(&responseMessage, QIODevice::WriteOnly);

    stream << quint8(0x04) << quint8(0x01)
           << quint8(status);

    _socket->write(responseMessage);
    _socket->flush();
}
