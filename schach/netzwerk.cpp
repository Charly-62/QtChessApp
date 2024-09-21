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
        // connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &Netzwerk::onSocketError);
        // connect(_socket, &QTcpSocket::errorOccurred, this, &Netzwerk::onSocketError);
    }
}

void Netzwerk::sendName(QString NameToSend) {
    QByteArray NameMsg = NameToSend.toUtf8();
    quint8 length = NameMsg.size();

    QByteArray SendMessage;
    QDataStream stream(&SendMessage, QIODevice::WriteOnly);

    stream << quint8(0x91) << quint8(length);
    stream.writeRawData(NameMsg.constData(), length);

    _socket->write(SendMessage);
    _socket->flush();
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

    stream << quint8(0x90) << quint8(0x01) << quint8(accepted);

    _socket->write(responseMessage);
    _socket->flush();
}

void Netzwerk::sendChatMsg(QString message) {
    QByteArray ChatMessage = message.toUtf8();
    quint8 length = ChatMessage.size();

    QByteArray SendMessage;
    QDataStream stream(&SendMessage, QIODevice::WriteOnly);

    stream << quint8(0x80) << quint8(length);
    stream.writeRawData(ChatMessage.constData(), length);

    _socket->write(SendMessage);
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


    const int MAX_PACKET_SIZE = 255;

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

        qDebug() << "In receiveMove: " << command << length;

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

    qDebug() << "In processMessage: " << command << length;

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

        if (!moveInfo.islegal) {
            emit logInGameMsg("Received move is illegal!");

            // Determine the specific error code
            if (!gameInstance->getPieceAt(startCol, startRow)) {
                statusCode = 0x03;  // No piece at start
            } else if (gameInstance->getWhiteTurn() != gameInstance->getPieceAt(startCol, startRow)->checkIfWhite()) {
                statusCode = 0x07;  // Not your turn
            } else {
                statusCode = 0x04;  // Move not allowed
            }

            sendMoveResponse(statusCode);

        } else {
            // Expected consequences
            bool expectedCapture = (moveInfo.consequences & 0x01);
            bool expectedCheckmate = (moveInfo.consequences & 0x02);

            // Simulate the move
            Game* simulatedGame = gameInstance->clone();
            simulatedGame->switchTurn();
            MoveInfo simuInfo = simulatedGame->tryMove(startCol, startRow, endCol, endRow);

            // Determine consequences
            bool actualCapture = (gameInstance->getPieceAt(endCol, endRow) != nullptr);
            bool actualCheckmate = (simuInfo.consequences & 0x02);

            qDebug() << expectedCheckmate << " " << actualCheckmate;

            delete simulatedGame;

            // Validate consequences
            if (expectedCapture != actualCapture) {
                statusCode = 0x06;  // Not OK, expected capture but none
                sendMoveResponse(statusCode);
                return;
            }

            if (expectedCheckmate != actualCheckmate) {
                statusCode = 0x08;  // Not OK, expected checkmate but none
                sendMoveResponse(statusCode);
                return;
            }

            // Determine status code for response
            if (actualCheckmate) {
                statusCode = 0x02;  // OK, checkmate
            } else if (actualCapture) {
                statusCode = 0x01;  // OK, capture
            } else {
                statusCode = 0x00;  // OK
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
                emit moveRejected(); // Connected with undoMove()
                break;
            case 0x04:
                emit logInGameMsg("Move rejected: Move not allowed.");
                emit moveRejected(); // Connected with undoMove()
                break;
            case 0x06:
                emit logInGameMsg("Move rejected: No capture made.");
                emit moveRejected(); // Connected with undoMove()
                break;
            case 0x07:
                emit logInGameMsg("Move rejected: Not your turn.");
                emit moveRejected(); // Connected with undoMove()
                break;
            case 0x08:
                emit logInGameMsg("Move rejected: No checkmate.");
                emit moveRejected(); // Connected with undoMove()
                break;
            default:
                emit logInGameMsg("Unknown move response received.");
                emit logInGameMsg("Disconnecting for safety.");
                _socket->disconnect();
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

    // Chat command
    else if (command == 0x80) {
        if (length > 250) {
            emit logInGameMsg("Received chat message too long.");
            emit logNetzwerkMsg("Received chat message too long.");
            emit logInGameMsg("Disconnecting for safety.");
            emit logNetzwerkMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        QByteArray ChatMessage(length, Qt::Uninitialized);
        int bytesRead = stream.readRawData(ChatMessage.data(), length);

        if (bytesRead != length) {
            emit logInGameMsg("Failed to read complete chat message.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        QString message = QString::fromUtf8(ChatMessage);
        emit ChatMsgReceived(message);
    }

    // Undo move response command
    else if(command == 0x90) {
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

    else if(command == 0x91) {
        if (length > 25) {
            emit logInGameMsg("Received name message too long.");
            emit logNetzwerkMsg("Received name message too long.");
            emit logInGameMsg("Disconnecting for safety.");
            emit logNetzwerkMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        QByteArray NameMsg(length, Qt::Uninitialized);
        int bytesRead = stream.readRawData(NameMsg.data(), length);

        if (bytesRead != length) {
            emit logInGameMsg("Failed to read complete name message.");
            emit logInGameMsg("Disconnecting for safety.");
            _socket->disconnect();
        }

        QString oppName = QString::fromUtf8(NameMsg);
        emit opponentNameReceived(oppName);

    }

    // Unvalid command
    else {
        emit logInGameMsg("Invalid command received.");
        emit logInGameMsg("Disconnecting for safety.");
        emit logNetzwerkMsg("Invalid command received.");
        emit logNetzwerkMsg("Disconnecting for safety.");
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

void Netzwerk::onSocketError(QAbstractSocket::SocketError socketError) {
    QString errorString = _socket->errorString();
    emit logInGameMsg(QString("Socket error: %1").arg(errorString));
    emit logNetzwerkMsg(QString("Socket error: %1").arg(errorString));

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            emit logInGameMsg("Remote host closed the connection.");
            emit logNetzwerkMsg("Remote host closed the connection.");
            break;

        case QAbstractSocket::HostNotFoundError:
            emit logInGameMsg("Host not found. Please check the host address and port.");
            emit logNetzwerkMsg("Host not found. Please check the host address and port.");
            break;

        case QAbstractSocket::ConnectionRefusedError:
            emit logInGameMsg("Connection refused by the server.");
            emit logNetzwerkMsg("Connection refused by the server.");
            break;

        default:
            emit logInGameMsg("An unexpected network error occurred.");
            emit logNetzwerkMsg("An unexpected network error occurred.");
            break;
    }
}
