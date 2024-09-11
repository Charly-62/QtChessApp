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
    , previouslySelectedCol(-1)
    , previouslySelectedRow(-1)
    , chessGame(new Game(this))
    , client(nullptr)
    , server(nullptr)
{
    ui->setupUi(this);
    initializeBoard();
    setupChessBoard();
    setDeviceController();

    on_cbHostClient_currentTextChanged("Client");

    whiteTimer = new QTimer(this);  // Create the white player's timer
    blackTimer = new QTimer(this);  // Create the black player's timer
    whiteTimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)
    blackTimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)
    isWhiteTurn = true;  // Start with white's turn

    // Connect the QTimer signals to the corresponding slot functions
    connect(whiteTimer, &QTimer::timeout, this, &SchachApp::updateWhiteTimer);
    connect(blackTimer, &QTimer::timeout, this, &SchachApp::updateBlackTimer);



    ui->cbPawnPromotion->setCurrentText("Not Selected");
    connect(ui->pbPawnPromotion, &QPushButton::clicked, this, &SchachApp::onPbPawnPromotionClicked);
    ui->pbPawnPromotion->setEnabled(false);
    ui->cbPawnPromotion->setEnabled(false);
    setWelcomeMessage();
    //ui->lblCurrentPlayerName->setText("Welcome to a new game ");
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

void SchachApp::setWelcomeMessage()
{
    QFont font;
        font.setBold(true);
        font.setPointSize(16); // Increase the font size
        font.setFamily("Arial"); // Set a font family, like Arial or any other you prefer

        ui->lblCurrentPlayerName->setFont(font);
        ui->lblCurrentPlayerName->setText("Welcome to a New Game!");

        // Center the text
        ui->lblCurrentPlayerName->setAlignment(Qt::AlignCenter);

        // Set a gradient background and text color
        ui->lblCurrentPlayerName->setStyleSheet(
            "color: #ffffff;" // Text color
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #3a3a3a, stop:1 #000000);" // Gradient background
            "padding: 10px;" // Padding around the text
            "border-radius: 10px;" // Rounded corners
        );


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
    originalButtonStyles.clear(); // Clear the map after resetting
}

void SchachApp::handleSquareClick(int row, int col) {
    // Comment out to play around with the GUI. ERASE COMMENT WHEN SENDING AND RECEIVING MOVES IS IMPLEMENTED
    // if (!isLocalTurn) {
    //     updateNetzwerkConsole("Not your turn!");
    //     return;
    // }

    QPushButton* clickedButton = buttons[row][col];
    std::shared_ptr<Piece> selectedPiece = chessGame->getPieceAt(col, row);
    // if no piece is selected yet
    if (selectedRow == -1 && selectedCol == -1) {
        // select the piece of the actual player
       if (selectedPiece && ((selectedPiece->checkIfWhite() && isWhiteTurn) || (!selectedPiece->checkIfWhite() && !isWhiteTurn))) {
            selectedRow = row;
            selectedCol = col;
            qDebug() << "Selected piece at:" << selectedCol << selectedRow;
            // Highlight possible moves for the selected piece
            std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves(chessGame);
            resetBoardHighlight();  // Clear previous highlights
            for (const auto& move : possibleMoves) {
                if (chessGame->logikInstance.isLegal(chessGame, col, row, move.first, move.second)) {
                    highlightPossibleMove(move);
                }
                // Debug output for possible moves
                for (const auto& move : possibleMoves) {
                    std::cout << move.first << " " << move.second << std::endl;
                }

                previouslySelectedRow = row;
                previouslySelectedCol = col;
            }
         }
      }else{ // if a piece is already selected

              // if another piece of the atual player is selected
            if (selectedPiece && ((selectedPiece->checkIfWhite() && isWhiteTurn) || (!selectedPiece->checkIfWhite() && !isWhiteTurn))) {
                // Clear previous selection highlights if a new piece is selected
                resetBoardHighlight();
                selectedRow = row;
                selectedCol = col;
                qDebug() << "Selected new piece at:" << selectedCol << selectedRow;

                // Highlight possible moves for the newly selected piece
                std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves(chessGame);

                for (const auto& move : possibleMoves) {
                    if (chessGame->logikInstance.isLegal(chessGame, col, row, move.first, move.second)) {
                        highlightPossibleMove(move);
                    }
                }

                // Debug output for possible moves
                for (const auto& move : possibleMoves) {
                    std::cout << move.first << " " << move.second << std::endl;
                }

                previouslySelectedRow = row;
                previouslySelectedCol = col;
                } else { // Si the case is empty or has an oppenent piece, attempt the movement

        qDebug() << "Attempting to move to:" << col << row;

        // Attempt to move and get MoveInfo
        MoveInfo moveInfo = chessGame->tryMove(selectedCol, selectedRow, col, row);
        qDebug() << "isLegal:" << moveInfo.islegal;

        if (moveInfo.islegal) {  // Move is valid
            movePiece(selectedRow, selectedCol, row, col);
            resetBoardHighlight();

            if (client) {
                client->sendMove(moveInfo);
            }
            if (server) {
                server->sendMove(moveInfo);
            }

            // Debug output for the board state
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
            resetBoardHighlight();  // Clear previous highlights
        }

        // Reset selection
        selectedRow = -1;
        selectedCol = -1;
        }
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

// /////////BASIC ONE
//void SchachApp::updatecurrentPlayerLabel() {
//    if (isWhiteTurn) {
//        ui->lblCurrentPlayerName->setText("White's Turn");
//    } else {
//        ui->lblCurrentPlayerName->setText("Black's Turn");
//    }
//}


// /////////IMPROVED ONE
void SchachApp::updatecurrentPlayerLabel() {
    QFont font;
    font.setBold(true); // Make the font bold
    ui->lblCurrentPlayerName->setFont(font);

    QString whitePlayerName = ui->leName1->text(); // Get white player's name
    QString blackPlayerName = ui->leName2->text(); // Get black player's name

    QString labelText;
    QString style;

    if (whitePlayerName != "Enter your name" && blackPlayerName != "Enter your name") {
        if (isWhiteTurn) {
            labelText = "♔ " + whitePlayerName + "'s Turn";
            style = "color: #ffffff; background-color: #000000; padding: 5px; border-radius: 5px;";
        } else {
            labelText = "♚ " + blackPlayerName + "'s Turn";
            style = "color: #000000; background-color: #ffffff; padding: 5px; border-radius: 5px;";
        }
    } else {
        if (isWhiteTurn) {
            labelText = "♔ White's Turn";
            style = "color: #ffffff; background-color: #000000; padding: 5px; border-radius: 5px;";
        } else {
            labelText = "♚ Black's Turn";
            style = "color: #000000; background-color: #ffffff; padding: 5px; border-radius: 5px;";
        }
    }

    ui->lblCurrentPlayerName->setText(labelText);
    ui->lblCurrentPlayerName->setStyleSheet(style);
}


void SchachApp::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    QPushButton* fromButton = buttons[fromRow][fromCol];
    QPushButton* toButton = buttons[toRow][toCol];
    // Move the icon from the selected button to the target button
    toButton->setIcon(fromButton->icon());
    fromButton->setIcon(QIcon());  // Clear the icon from the original button

     // Debugging: Print the move details
     qDebug() << "Moved piece from:" << fromCol << fromRow << "to:" << toCol << toRow;

     // Re-fetch all pieces and update the icons on the board
     for (int row = 0; row < 8; ++row) {
         for (int col = 0; col < 8; ++col) {
             QPushButton* button = buttons[row][col];
             std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);  // Get piece from the game

             if (piece != nullptr) {
                 QString iconName = QString(":/Figuren/") + piece->getType() + (piece->checkIfWhite() ? "W" : "B") + ".png";
                 button->setIcon(QIcon(iconName));  // Set the correct icon for the piece
             } else {
                 button->setIcon(QIcon());  // Clear icon if no piece exists
             }
         }
     }

     // Switch turns
        isWhiteTurn = !isWhiteTurn;  // Toggle between white and black turns
        startTurnTimer();  // Start the timer for the next turn
        updatecurrentPlayerLabel();
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

quint8 SchachApp::PawnPromotion(){
    qWarning()<<"Select a piece for pawn promotion";
    ui->pbPawnPromotion->setEnabled(true);
    ui->cbPawnPromotion->setEnabled(true);
    return promotionType;
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
            connect(client, &Netzwerk::logMessage, this, &SchachApp::updateNetzwerkConsole);
            connect(client, &Netzwerk::gameStarted, this, &SchachApp::gameStarted);
            connect(client, &Netzwerk::moveReceived, this, &SchachApp::moveReceived);
        }
    } else if(mode == "Server") {

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
            ui->lstNetzwerkConsole->addItem("Server initialized");
            connect(server, &MyTCPServer::clientStateChanged, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &Netzwerk::logMessage, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &MyTCPServer::serverStatus, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &Netzwerk::moveReceived, this, &SchachApp::moveReceived);
        }
    }
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

void SchachApp::moveReceived(MoveInfo moveInfo) {

    MoveInfo result = chessGame->tryMove(moveInfo.s_col, moveInfo.s_row, moveInfo.e_col, moveInfo.e_row);

    if(result.islegal) {
        movePiece(moveInfo.s_row, moveInfo.s_col, moveInfo.e_row, moveInfo.e_col);
        updateNetzwerkConsole("Opponent's move applied.");
    } else {
        updateNetzwerkConsole("Invalid move received");
    }

    isLocalTurn = true;
}




// Client version of gameStarted()
void SchachApp::gameStarted(bool ServerStarts, QString groupNumber) {
        startTurnTimer();
        updatecurrentPlayerLabel();
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
    ui->bStart->setEnabled(false);
    bool ServerStarts = (ui->cbStartingPlayer->currentText() == "Server");
    server->sendGameStart(ServerStarts);
    updateNetzwerkConsole("Game start message sent. " + ui->cbStartingPlayer->currentText() + " starts.");
    startTurnTimer();
    updatecurrentPlayerLabel();
}
