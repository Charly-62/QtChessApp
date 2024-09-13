#ifndef SCHACHAPP_H
#define SCHACHAPP_H
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QHostAddress>
#include <QStyle>
#include "mytcpserver.h"
#include "mytcpclient.h"
#include "game.h"
#include "piece.h"
#include <QTimer>
#include <QComboBox>

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
     */
    SchachApp(QWidget *parent = nullptr);

    /**
     * @brief Destructor for SchachApp.
     */
    ~SchachApp();

    Game* getGameInstance() const {
        return chessGame;
    }

    quint8 PawnPromotion(int rowPawnPromotion);
    void checkForCheckmate();

private slots:
    void handleSquareClick(int row, int col);

    void on_leIP_textChanged(const QString &arg1);

    void on_bConnect_clicked();

    void on_cbHostClient_currentTextChanged(const QString &mode);

    void on_cbStartingPlayer_currentTextChanged(const QString &startingPlayer);

    // Server slots
    void updateNetzwerkConsole(QString message); // Update UI when the client/server state changes

    // Client slots
    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);

    void on_bStart_clicked();

    void on_pbClear_clicked();

private:
    Ui::SchachApp *ui;  ///< Pointer to the UI elements of the chess application.
    void initializeBoard();
    void setupChessBoard();
    void setupPieces(int row, int col, QPushButton* button, bool isWhite);
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    void highlightPossibleMove(const std::pair<int, int>& move);
    void resetBoardHighlight();

    QPushButton* buttons[8][8];
    Piece* board[8][8];
    int selectedRow;
    int selectedCol;
    int previouslySelectedCol;
    int previouslySelectedRow;
    Game* chessGame = nullptr;
    MyTCPClient* client = nullptr;
    MyTCPServer* server = nullptr;
    QString NetzwerkMode;
    void setDeviceController();
    void moveReceived(MoveInfo);
    void gameStarted(bool, QString);

    QMap<QPushButton*, QString> originalButtonStyles;

    //bool isLocalTurn;
    bool isLocalPlayerWhite = false;
    bool isLocalGame = false;

    QTimer* player1Timer;
    QTimer* player2Timer;
    int player1TimeRemaining;  // in seconds
    int player2TimeRemaining;  // in seconds

    void updatePlayer1Timer();
    void updatePlayer2Timer();
    void updateTimerDisplay(int timeRemaining);
    void startTurnTimer();
    void setWelcomeMessage();
    void updatecurrentPlayerLabel();

    QComboBox* cbPawnPromotion;
    quint8 promotionType;
    quint8 selectedPromotionType;

    void undoMove();

    QString formatMove(const MoveInfo& moveInfo);
    void addMoveToHistory(const MoveInfo& moveInfo);
    void removeLastMoveFromHistory();



};
#endif // SCHACHAPP_H
