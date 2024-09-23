/**
 * @file schachapp.h
 * @brief This file contains the declaration of the schachapp class, which manages the gui and user interaction.
 */

#ifndef SCHACHAPP_H
#define SCHACHAPP_H

#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QHostAddress>
#include <QStyle>
#include <QTimer>
#include <QComboBox>
#include <QStackedWidget>
#include <QStack>
#include <QMetaEnum>
#include <QDebug>
#include <QEventLoop>
#include <QComboBox>
#include <QFile>

#include "mytcpserver.h"
#include "mytcpclient.h"
#include "game.h"
#include "piece.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SchachApp;
}
QT_END_NAMESPACE

/**
 * @class SchachApp
 * @brief Manages the user interface for the chess game, displaying the board and interacting with the user.
 */
class SchachApp : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for SchachApp.
     * * @param parent The parent widget.
     */
    SchachApp(QWidget *parent = nullptr);

    /**
     * @brief Destructor for SchachApp.
     */
    ~SchachApp();

    /**
     * @brief Getter for the Game instance.
     * @return Pointer to the current Game instance.
     */
    Game* getGameInstance() const {
        return chessGame;
    }

    /**
     * @brief Handles pawn promotion logic.
     * @param rowPawnPromotion The row where the pawn promotion occurs.
     * @return The type of the promoted piece.
     */
    quint8 PawnPromotion(int rowPawnPromotion);

    void addScore(int score, bool whiteScore);

private slots:

    /**
     * @brief Handles the event when a square on the chessboard is clicked.
     * @param row The row of the clicked square.
     * @param col The column of the clicked square.
     */
    void handleSquareClick(int row, int col);

    /**
     * @brief Handles the event when the text in the IP address input field changes.
     * @param arg1 The new text in the IP address field.
     */
    void on_leIP_textChanged(const QString &arg1);

    /**
     * @brief Handles the event when the host/client mode changes.
     * @param mode The new mode (either "Client" or "Server").
     */
    void on_cbHostClient_currentTextChanged(const QString &mode);

    /**
     * @brief Handles the event when the starting player is changed.
     * @param startingPlayer The new starting player ("Server" or "Client").
     */
    void on_cbStartingPlayer_currentTextChanged(const QString &startingPlayer);

    /**
     * @brief Updates the network console with a message.
     * @param message The message to display in the network console.
     */
    void updateNetzwerkConsole(QString message);

    /**
     * @brief Updates the in-game console with a message.
     * @param message The message to display in the in-game console.
     */
    void updateInGameConsole(QString message);

    /**
     * @brief Handles the event when the device connects to the network.
     */
    void device_connected();

    /**
     * @brief Handles the event when the device disconnects from the network.
     */
    void device_disconnected();

    /**
     * @brief Handles changes in the socket state of the device.
     * @param state The new socket state.
     */
    void device_stateChanged(QAbstractSocket::SocketState);

    /**
     * @brief Handles the event when the "Connect" button is clicked.
     */
    void on_bConnect_clicked();

    /**
     * @brief Handles the event when the "Start" button is clicked to begin a new game.
     */
    void on_bStart_clicked();

    /**
     * @brief Handles the event when the "Clear" button is clicked to clear the network console.
     */
    void on_pbClear_clicked();

    /**
     * @brief Handles the event when the "Undo" button is clicked to undo the last move.
     */
    void on_pbUndo_clicked();

    /**
     * @brief Handles the event when the "Send Name" button is clicked to send the player's name.
     */
    void on_bSendName_clicked();

    /**
     * @brief Handles the event when the "Enter" key is pressed in the name input field.
     */
    void on_lename_returnPressed();

    /**
     * @brief Handles the event when the "Enter" key is pressed in the chat input field.
     */
    void on_leSendChat_returnPressed();

private:
    Ui::SchachApp *ui;  ///< Pointer to the UI elements of the chess application.

    /**
      * @brief Displays the welcome message when the game starts.
      */
    void WelcomeDisplay();

    void adjustScoreAndCapturedPiecesDisplay(std::shared_ptr<Piece> capturedPiece);

    void removeLastCapturedPiece(QLayout* layout);

    /**
     * @brief Displays the start message when the game is ready to begin.
     */
    void StartDisplay();

    /**
     * @brief Sets the welcome message for the current player.
     */
    void setWelcomeMessage();

    QPushButton* buttons[8][8]; ///< Buttons representing the chessboard squares.
    Piece* board[8][8]; ///< Chess pieces on the board.
    int selectedRow; ///< Row of the selected piece.
    int selectedCol; ///< Column of the selected piece.
    int previouslySelectedCol; ///< Previously selected column.
    int previouslySelectedRow; ///< Previously selected row.
    Game* chessGame = nullptr; ///< Pointer to the Game instance.
    QMap<QPushButton*, QString> originalButtonStyles; ///< Original styles of the chessboard buttons.

    /**
     * @brief Initializes the chessboard by mapping UI elements and setting up the board pieces.
     */
    void initializeBoard();

    /**
     * @brief Sets up the chessboard with the pieces and connects button signals to handlers.
     */
    void setupChessBoard();

    /**
     * @brief Highlights possible moves on the board for a given piece.
     * @param move A pair representing the row and column of a possible move.
     */
    void highlightPossibleMove(const std::pair<int, int>& move);

    /**
     * @brief Resets all highlighted squares on the board to their original styles.
     */
    void resetBoardHighlight();

    QStackedWidget* GAME ; ///< Stacked widget for managing game pages.
    QWidget* initialpage ; ///< Initial page of the game UI.
    QWidget* gamepage ; ///< Main game page of the UI.

    /**
     * @brief Updates the label for the current player.
     */
    void updatecurrentPlayerLabel();

    /**
     * @brief Moves a chess piece on the board.
     * @param fromRow The row of the starting square.
     * @param fromCol The column of the starting square.
     * @param toRow The row of the destination square.
     * @param toCol The column of the destination square.
     */
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief Processes a received move from the opponent.
     * @param moveInfo Information about the move.
     */
    void moveReceived(MoveInfo);

    /**
     * @brief Undoes the last move.
     */
    void undoMove();

    void onPawnPromoted(int pieceValue, bool isWhite);

    /**
     * @brief Updates the score display after undoing a move.
     */
    void undoScoreUpdate(const MoveInfo& moveInfo);


    MyTCPClient* client = nullptr; ///< Client for network communication.
    MyTCPServer* server = nullptr; ///< Server for network communication.
    QString NetzwerkMode; ///< Mode of network communication (client/server).

    /**
     * @brief Sets up the device controller for handling client-server communication.
     */
    void setDeviceController();

    /**
     * @brief Starts the game from the server-side or client-side.
     * @param ServerStarts A flag to indicate if the server starts the game.
     * @param groupNumber The group number of the players.
     */
    void gameStarted(bool, QString);

    /**
     * @brief Handles client connection events.
     */
    void on_client_connected();

    /**
     * @brief Handles client disconnection events.
     */
    void on_client_disconnected();

    /**
     * @brief Indicates whether the local player is playing as the white pieces.
     * Defaults to false (black pieces).
     */
    bool isLocalPlayerWhite = false;

    /**
     * @brief Indicates whether the game is a local (offline) game.
     * Defaults to false (online/networked game).
     */
    bool isLocalGame = false;


    QTimer* player1Timer; ///< Timer for player 1.
    QTimer* player2Timer; ///< Timer for player 2.
    int player1TimeRemaining;  ///< Time remaining for player 1 (in seconds).
    int player2TimeRemaining;  ///< Time remaining for player 2 (in seconds).

    /**
     * @brief Updates the timer for player 1 .
     */
    void updatePlayer1Timer();

    /**
     * @brief Updates the timer for player 2.
     */
    void updatePlayer2Timer();

    /**
     * @brief Updates the timer display on the UI.
     * @param timeRemaining The remaining time in seconds.
     */
    void updateTimerDisplay(int timeRemaining);

    /**
     * @brief Starts the timer for the player's turn.
     */
    void startTurnTimer();

    int whiteScore ;  ///< Score for the white player.
    int blackScore ; ///< Score for the black player.


    QComboBox* cbPawnPromotion; ///< ComboBox for selecting pawn promotion.
    quint8 promotionType; ///< The selected promotion type.
    QStackedWidget* swpawnpromotion ; ///< Stacked widget for pawn promotion page.
    QWidget* defaultpage ; ///< Default page widget (score page).
    QWidget* pawnpromotionpage ; ///< Pawn promotion page widget.
    QString LocalName = "Player 1"; ///< Name of the local player.
    QString OpponentName = "Player 2";///< Name of the opponent player.

    /**
     * @brief Handles opponent name received from the network.
     * @param oppName The opponent's name.
     */
    void opponentNameReceived(QString oppName);

    /**
     * @brief Handles the event when a chat message is received.
     * @param message The chat message.
     */
    void onChatMsgReceived(QString message);

    /**
     * @brief Censors banned words in the chat message.
     * @param message The original chat message.
     * @return The censored message.
     */
    QString censorMessage(const QString& message) const;

    QStringList bannedWords; ///< List of banned words for censoring chat.
    QString bannedWordsFilePathEn = ":/List_of_banned_words/en.txt"; ///< File path to the list of banned words in English, Credits for the dataset: https://github.com/Hesham-Elbadawi/list-of-banned-words/tree/master
    QString bannedWordsFilePathDe = ":/List_of_banned_words/de.txt"; ///< File path to the list of banned words in German, Credits for the dataset: https://github.com/Hesham-Elbadawi/list-of-banned-words/tree/master

    /**
     * @brief Loads the banned words for chat censorship.
     */
    void loadBannedWords();

    bool blockguitmp = false; ///< to block the board when selecting promotion type

    /**
     * @brief Formats the move notation for the move history.
     * @param moveInfo Information about the move.
     * @return The formatted move string.
     */
    QString formatMove(const MoveInfo& moveInfo);

    /**
     * @brief Adds a move to the move history display.
     * @param moveInfo Information about the move.
     */
    void addMoveToHistory(const MoveInfo& moveInfo);

    /**
     * @brief Removes the last move from the move history display.
     */
    void removeLastMoveFromHistory();

    QHBoxLayout* deadplayer1; ///< Layout for displaying captured pieces of player 1.
    QHBoxLayout* deadplayer2; ///< Layout for displaying captured pieces of player 2.

    /**
     * @brief Updates the score and displays the captured piece.
     * @param capturedPiece The captured piece.
     */
    void pieceCaptured(std::shared_ptr<Piece> capturedPiece);

    /**
     * @brief Struct to store information about captured pieces.
     */
    struct CapturedPieceInfo {
        QString type;
        bool isWhite;
        int value;
    };

};
#endif // SCHACHAPP_H
