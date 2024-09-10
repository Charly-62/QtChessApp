#include "schachapp.h"
#include "ui_schachgui.h"
#include "mytcpclient.h"
#include "piece.h"
#include "game.h"
#include <QPushButton>
#include <QComboBox>
#include <QMetaEnum>
#include <QDebug>
#include <iostream>
#include <QEventLoop>
#include <QComboBox>

SchachApp::SchachApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SchachApp)
    , selectedRow(-1)
    , selectedCol(-1)
    , chessGame(new Game(this))
    , client(nullptr)
    , server(nullptr)
{
    ui->setupUi(this);
    initializeBoard();
    setupChessBoard();
    setDeviceController();

    on_cbHostClient_currentTextChanged("Client");

    // Connect the Netzwerk logMessage signal to updateNetzwerkConsole slot
    if(client) {
        connect(client, &Netzwerk::logMessage, this, &SchachApp::updateNetzwerkConsole);
    }
    if(server) {
        connect(server, &Netzwerk::logMessage, this, &SchachApp::updateNetzwerkConsole);
    }

    whiteTimer = new QTimer(this);  // Create the white player's timer
    blackTimer = new QTimer(this);  // Create the black player's timer
    whiteTimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)
    blackTimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)
    isWhiteTurn = true;  // Start with white's turn

    connect(client, &Netzwerk::gameStarted, this, &SchachApp::gameStarted);
    // Connect the QTimer signals to the corresponding slot functions
    connect(whiteTimer, &QTimer::timeout, this, &SchachApp::updateWhiteTimer);
    connect(blackTimer, &QTimer::timeout, this, &SchachApp::updateBlackTimer);

    // Start the timer for the first turn
    //startTurnTimer();

    ui->cbPawnPromotion->setCurrentText("Not Selected");
    connect(ui->pbPawnPromotion, &QPushButton::clicked, this, &SchachApp::onPbPawnPromotionClicked);
    ui->pbPawnPromotion->setEnabled(false);
    ui->cbPawnPromotion->setEnabled(false);

    // Connection to handle the turn switch
    connect(chessGame, &Game::turnSwitched, this, &SchachApp::switchTurn);
}

SchachApp::~SchachApp()
{
    delete ui;
    for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                delete board[row][col];
            }
     }
}

void SchachApp::initializeBoard()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            buttons[row][col] = nullptr;
            board[row][col] = nullptr;
        }
    }

    // Map UI buttons to the grid
    buttons[0][0] = ui->A1; buttons[0][1] = ui->B1; buttons[0][2] = ui->C1; buttons[0][3] = ui->D1;
    buttons[0][4] = ui->E1; buttons[0][5] = ui->F1; buttons[0][6] = ui->G1; buttons[0][7] = ui->H1;
    buttons[1][0] = ui->A2; buttons[1][1] = ui->B2; buttons[1][2] = ui->C2; buttons[1][3] = ui->D2;
    buttons[1][4] = ui->E2; buttons[1][5] = ui->F2; buttons[1][6] = ui->G2; buttons[1][7] = ui->H2;
    buttons[2][0] = ui->A3; buttons[2][1] = ui->B3; buttons[2][2] = ui->C3; buttons[2][3] = ui->D3;
    buttons[2][4] = ui->E3; buttons[2][5] = ui->F3; buttons[2][6] = ui->G3; buttons[2][7] = ui->H3;
    buttons[3][0] = ui->A4; buttons[3][1] = ui->B4; buttons[3][2] = ui->C4; buttons[3][3] = ui->D4;
    buttons[3][4] = ui->E4; buttons[3][5] = ui->F4; buttons[3][6] = ui->G4; buttons[3][7] = ui->H4;
    buttons[4][0] = ui->A5; buttons[4][1] = ui->B5; buttons[4][2] = ui->C5; buttons[4][3] = ui->D5;
    buttons[4][4] = ui->E5; buttons[4][5] = ui->F5; buttons[4][6] = ui->G5; buttons[4][7] = ui->H5;
    buttons[5][0] = ui->A6; buttons[5][1] = ui->B6; buttons[5][2] = ui->C6; buttons[5][3] = ui->D6;
    buttons[5][4] = ui->E6; buttons[5][5] = ui->F6; buttons[5][6] = ui->G6; buttons[5][7] = ui->H6;
    buttons[6][0] = ui->A7; buttons[6][1] = ui->B7; buttons[6][2] = ui->C7; buttons[6][3] = ui->D7;
    buttons[6][4] = ui->E7; buttons[6][5] = ui->F7; buttons[6][6] = ui->G7; buttons[6][7] = ui->H7;
    buttons[7][0] = ui->A8; buttons[7][1] = ui->B8; buttons[7][2] = ui->C8; buttons[7][3] = ui->D8;
    buttons[7][4] = ui->E8; buttons[7][5] = ui->F8; buttons[7][6] = ui->G8; buttons[7][7] = ui->H8;
}


// Setup chessboard in GUI
void SchachApp::setupChessBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);  // Get piece from the game
            if (piece != nullptr) {  // If there is a piece at this position
                QString iconName = QString(":/Figuren/") + piece->getType() + (piece->checkIfWhite() ? "W" : "B") + ".png";
                buttons[row][col]->setIcon(QIcon(iconName));
            }
            // Set the icon size and connect the button click to the handler
            buttons[row][col]->setIconSize(QSize(80, 80));

            if (!originalButtonStyles.contains(buttons[row][col])) {
                            originalButtonStyles[buttons[row][col]] = buttons[row][col]->styleSheet();
                        }
            connect(buttons[row][col], &QPushButton::clicked, [=]() {
                handleSquareClick(row, col);
            });
        }
    }
}
void SchachApp::highlightPossibleMove(const std::pair<int, int>& move) {
    int row = move.second;
    int col = move.first;
    QPushButton* button = buttons[row][col];

    if (button) {
        if (!originalButtonStyles.contains(button)) {
            originalButtonStyles[button] = button->styleSheet(); // Store the current style if not already stored
        }
        button->setStyleSheet("background-color: red;");
    }
}

void SchachApp::resetBoardHighlight() {
    // Reset only the highlighted buttons to their original style
    for (auto it = originalButtonStyles.begin(); it != originalButtonStyles.end(); ++it) {
        QPushButton* button = it.key();
        if (button) {
            button->setStyleSheet(it.value()); // Reset to original style
        }
    }
}

void SchachApp::handleSquareClick(int row, int col) {

    /* Comment out to play around with the gui. ERASE COMMENT WHEN SENDING AND RECEIVING MOVES IS IMPLEMENTED
    if(!isLocalTurn) {
        updateNetzwerkConsole("Not your turn!");
        return;
    }
    */

    QPushButton* clickedButton = buttons[row][col];
    std::shared_ptr<Piece> selectedPiece = chessGame->getPieceAt(col, row);

    if(selectedPiece){
        std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves(chessGame);

        //some "Possible" moves are illegal i.e. pinning and moving while in check
        //Logik logikObjekt;

        // Reset highlighting if a new piece is selected
                if (selectedRow != -1 && selectedCol != -1) {
                    resetBoardHighlight(); // Clear previous highlights
                }

            // Highlight possible moves for the selected piece
            for (const auto& move : possibleMoves) {
            if(chessGame->logikInstance.isLegal(chessGame, col, row, move.first, move.second)){
                    highlightPossibleMove(move);
                }
            }

        for (const auto& move : possibleMoves) {
            std::cout << move.first << " " << move.second << std::endl;
        }
    }

    if (selectedRow == -1 && selectedCol == -1) { // No piece selected yet
        if (!clickedButton->icon().isNull()) { // If there's a piece on the square
            selectedRow = row;
            selectedCol = col;
            qDebug() << "Selected piece at:" << selectedRow << selectedCol;
          //  clickedButton->setStyleSheet("background-color: yellow;"); // Highlight selected square

        }
    } else { // A piece is selected and a move is attempted
        qDebug() << "Attempting to move to:" << row << col;
       // Attempt to move and get MoveInfo
                MoveInfo moveInfo = chessGame->tryMove(selectedCol, selectedRow, col, row);
                qDebug() << "isLegal:" << moveInfo.islegal;

                if (moveInfo.islegal == true) { // Move is valid
                    movePiece(selectedRow, selectedCol, row, col);
                    resetBoardHighlight();
                    if(client)
                        client->sendMove(moveInfo);
                    if(server)
                        server->sendMove(moveInfo);

                    for (int row = 7; row >= 0; --row) {
                        for (int col = 0; col < 8; ++col) {
                            std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);
                            if (piece) {
                                char pieceChar = ' ';
                                if (dynamic_cast<Pawn*>(piece.get())) pieceChar = 'P';
                                else if (dynamic_cast<Rook*>(piece.get())) pieceChar = 'R';
                                else if (dynamic_cast<Knight*>(piece.get())) pieceChar = 'N';
                                else if (dynamic_cast<Bishop*>(piece.get())) pieceChar = 'B';
                                else if (dynamic_cast<Queen*>(piece.get())) pieceChar = 'Q';
                                else if (dynamic_cast<King*>(piece.get())) pieceChar = 'K';
                                std::cout << pieceChar << ' ';
                            } else {
                                std::cout << ". ";
                            }
                        }
                        std::cout << std::endl;
                    }
                    std::cout << std::endl;
                } else {
                    updateNetzwerkConsole("Illegal move!");
                }

                // Reset selection
                selectedRow = -1;
                selectedCol = -1;
}
}

void SchachApp::startTurnTimer() {
    if (isWhiteTurn) {
        whiteTimer->start(1000);  // Start white player's timer with 1 second interval
        blackTimer->stop();  // Stop black player's timer
    } else {
        blackTimer->start(1000);  // Start black player's timer with 1 second interval
        whiteTimer->stop();  // Stop white player's timer
    }
}

void SchachApp::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    QPushButton* fromButton = buttons[fromRow][fromCol];
    QPushButton* toButton = buttons[toRow][toCol];
    // Move the icon from the selected button to the target button
    toButton->setIcon(fromButton->icon());
    fromButton->setIcon(QIcon());  // Clear the icon from the original button

     // Debugging: Print the move details
     qDebug() << "Moved piece from:" << fromRow << fromCol << "to:" << toRow << toCol;

     // Re-fetch the piece and update the icon (ensures any changes are reflected)
     std::shared_ptr<Piece> movedPiece = chessGame->getPieceAt(toCol, toRow);
     if (movedPiece != nullptr) {
        QString iconName = QString(":/Figuren/") + movedPiece->getType() + (movedPiece->checkIfWhite() ? "W" : "B") + ".png";
        toButton->setIcon(QIcon(iconName));  // Set the correct icon for the piece
      } else {
         toButton->setIcon(QIcon());  // Clear icon if no piece exists (for safety)
      }

     // Switch turns
        isWhiteTurn = !isWhiteTurn;  // Toggle between white and black turns
        startTurnTimer();  // Start the timer for the next turn
}

void SchachApp::updateTimerDisplay(int timeRemaining, bool isWhite) {
    int minutes = timeRemaining / 60;  // Calculate minutes
    int seconds = timeRemaining % 60;  // Calculate seconds
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

    if (isWhite) {
        ui->lblWhiteTimer->setText(timeString);  // Update the white player's timer label
    } else {
        ui->lblBlackTimer->setText(timeString);  // Update the black player's timer label
    }
}

void SchachApp::updateWhiteTimer() {
    if (whiteTimeRemaining > 0) {
        whiteTimeRemaining--;  // Decrease the remaining time
        updateTimerDisplay(whiteTimeRemaining, true);  // Update the UI
    } else {
        whiteTimer->stop();  // Stop the timer if time runs out
        //handleTimeOut(true);  // Handle timeout
    }
}

void SchachApp::updateBlackTimer() {
    if (blackTimeRemaining > 0) {
        blackTimeRemaining--;  // Decrease the remaining time
        updateTimerDisplay(blackTimeRemaining, false);  // Update the UI
    } else {
        blackTimer->stop();  // Stop the timer if time runs out
        //handleTimeOut(false);  // Handle timeout
    }
}

void SchachApp::onPbPawnPromotionClicked(){
    QString mode = ui-> cbPawnPromotion->currentText();
    qWarning()<<"Current Selection:"<<mode;
    quint8 promotionType = 0x00;
    if (mode == "Queen"){
        promotionType = 0x40;
    }
    else if (mode == "Rook"){
        promotionType = 0x30;
    }
    else if (mode == "Knight"){
        promotionType = 0x20;
    }
    else if (mode == "Bishop"){
        promotionType = 0x10;
    }
    qWarning()<<"promotion type:"<<promotionType;
    ui->pbPawnPromotion->setEnabled(false);
    ui->cbPawnPromotion->setEnabled(false);
}
quint8 SchachApp:: PawnPromotion(){
    qWarning()<<"Select a piece for pawn promotion";
    ui->pbPawnPromotion->setEnabled(true);
    ui->cbPawnPromotion->setEnabled(true);

}

/**
 * @brief Changes the color of the IPAddress line edit if it is a valid or invalid IPv4 address (maybe add also IPv6 addresses)
 * @param arg1
 */
void SchachApp::on_leIP_textChanged(const QString &arg1)
{
    QString state = "0";

    if(arg1 == "...") {
        state = "";
    } else {
        QHostAddress address(arg1);
        if(QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
        }
    }

    ui->leIP->setProperty("state", state);
    style()->polish(ui->leIP);
}

void SchachApp::on_bConnect_clicked()
{
    if(ui->cbHostClient->currentText() == "Client") {
        if(client->isConnected()) {
            client->disconnect();
        } else {
            auto ip = ui->leIP->text();
            auto port = ui->spnPort->value();
            client->connectToHost(ip, port);
            // Print connection error after some time if disconnected (SocketError gibt Probleme im online builder)
            // Disable bConnect while trying to connect
            ui->bConnect->setEnabled(false);
            QTimer::singleShot(500, this, [this]() {
                if(client->state() == QAbstractSocket::ConnectedState) {
                    ui->bConnect->setEnabled(true);
                } else {
                    QTimer::singleShot(5000, this, [this]() {
                        if(client->state() != QAbstractSocket::ConnectedState) {
                            ui->lstNetzwerkConsole->addItem("Connection error. Check IP Address or Host availability");
                        }
                        ui->bConnect->setEnabled(true);
                        });
            }
            });
        }
    } else if(ui->cbHostClient->currentText() == "Server") {
        if(server->isListening()) {
            // Stop listening if the server is already listening
            server->stopListening();
            ui->bConnect->setText("Start Listening");
            ui->lstNetzwerkConsole->addItem("Server stopped listening.");
        } else {
            // Get the port number from the spnPort widget and start listening
            int port = ui->spnPort->value();
            server->startListening(port);
            ui->bConnect->setText("Stop Listening");
        }
    }
}

void SchachApp::on_cbHostClient_currentTextChanged(const QString &mode) {
    if(mode == "Client") {

        // Update bConnect button for client
        ui->bConnect->setText("Connect");

        ui->bStart->setEnabled(false);
        ui->leIP->setEnabled(true);
        ui->cbStartingPlayer->setEnabled(false);


        // Switch to Client mode
        if(server) {
            server->stopListening();
            delete server;
            server = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Client Mode. Server stopped.");
        }

        if(!client) {
            client = new MyTCPClient(chessGame);
            setDeviceController();
            ui->lstNetzwerkConsole->addItem("Client initialized.");
            connect(client, &Netzwerk::gameStarted, this, &SchachApp::gameStarted);
        }
    } else if (mode == "Server") {

        //Update bConnect button for server
        ui->bConnect->setText("Start Listening");

        ui->bStart->setEnabled(true);
        ui->leIP->setEnabled(false);
        ui->cbStartingPlayer->setEnabled(true);

        // Switch to Server mode
        if(client) {
            client->disconnect();
            delete client;
            client = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Server Mode. Client stopped.");
        }

        if(!server) {
            server = new MyTCPServer(chessGame);
            connect(server, &MyTCPServer::clientStateChanged, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &MyTCPServer::serverStatus, this, &SchachApp::updateNetzwerkConsole);
            ui->lstNetzwerkConsole->addItem("Server initialized");
        }
    }
    moveReceived();
}

void SchachApp::updateNetzwerkConsole(QString message) {
    ui->lstNetzwerkConsole->addItem(message);
}

void SchachApp::setDeviceController() {
    if(client) {
    connect(client, &MyTCPClient::connected, this, &SchachApp::device_connected);
    connect(client, &MyTCPClient::disconnected, this, &SchachApp::device_disconnected);
    connect(client, &MyTCPClient::stateChanged, this, &SchachApp::device_stateChanged);
    }
}

void SchachApp::device_connected() {
    ui->lstNetzwerkConsole->addItem("Connected to device");
    ui->bConnect->setText("Disconnect");
}

void SchachApp::device_disconnected() {
    ui->lstNetzwerkConsole->addItem("Disconnected from device");
    ui->bConnect->setText("Connect");
}

void SchachApp::device_stateChanged(QAbstractSocket::SocketState state) {
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstNetzwerkConsole->addItem(metaEnum.valueToKey(state));
}

void SchachApp::switchTurn() {
    // If the local player is white and it's white's turn, or the local player is black and it's black's turn
    if((isLocalPlayerWhite && chessGame->getWhiteTurn()) || (!isLocalPlayerWhite && !(chessGame->getWhiteTurn()))) {
        isLocalTurn = true;
    } else {
        isLocalTurn = false;
    }
}

void SchachApp::moveReceived() {
    // Connect the Netzwerk logMessage signal to updateNetzwerkConsole slot
    if(client) {
        connect(client, &Netzwerk::moveReceived, this, [=](const MoveInfo& moveInfo) {
            MoveInfo result = chessGame->tryMove(moveInfo.s_col, moveInfo.s_row, moveInfo.e_col, moveInfo.e_row);
            if(result.islegal) {
                movePiece(moveInfo.s_row, moveInfo.s_col, moveInfo.e_row, moveInfo.e_col);
                updateNetzwerkConsole("Opponent's move applied.");
            } else {
                updateNetzwerkConsole("Invalid move received");
            }

            isLocalTurn = true;
        }
        );
    }

    if(server) {
        connect(server, &Netzwerk::moveReceived, this, [=](const MoveInfo& moveInfo) {
            MoveInfo result = chessGame->tryMove(moveInfo.s_col, moveInfo.s_row, moveInfo.e_col, moveInfo.e_row);
            if(result.islegal) {
                movePiece(moveInfo.s_row, moveInfo.s_col, moveInfo.e_row, moveInfo.e_col);
                updateNetzwerkConsole("Opponent's move applied.");
            } else {
                updateNetzwerkConsole("Invalid move received");
            }

            isLocalTurn = true;
        }
        );
    }

}

// Client version of gameStarted()
void SchachApp::gameStarted(bool ServerStarts, QString groupNumber) {
        startTurnTimer();
        if(ServerStarts) {
            updateNetzwerkConsole("Server starts the game.");
            updateNetzwerkConsole("Playing against Group " + groupNumber);
            isLocalTurn = false;
            isLocalPlayerWhite = false;
        } else {
            updateNetzwerkConsole("Client starts the game.");
            updateNetzwerkConsole("Playing against Group " + groupNumber);
            isLocalTurn = true;
            isLocalPlayerWhite = true;
        }

}

// Server version of gameStarted()
void SchachApp::on_cbStartingPlayer_currentTextChanged(const QString &startingPlayer) {

    if(startingPlayer == "Server") {
        isLocalPlayerWhite = true;
        isLocalTurn = true;
    } else if(startingPlayer == "Client") {
        isLocalPlayerWhite = false;
        isLocalTurn = false;
    }

}

void SchachApp::on_bStart_clicked()
{
    bool ServerStarts = (ui->cbStartingPlayer->currentText() == "Server");
    server->sendGameStart(ServerStarts);
    updateNetzwerkConsole("Game start message sent. " + ui->cbStartingPlayer->currentText() + " starts.");
    startTurnTimer();

}
