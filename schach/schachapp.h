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

    quint8 PawnPromotion();

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

    void onPbPawnPromotionClicked();

    // Handle turn change
    void switchTurn();

    void on_bStart_clicked();

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
    void moveReceived();
    void gameStarted(bool, QString);

    QMap<QPushButton*, QString> originalButtonStyles;

    bool isLocalTurn;
    bool isLocalPlayerWhite = true;

    QTimer* whiteTimer;
    QTimer* blackTimer;
    int whiteTimeRemaining;  // in seconds
    int blackTimeRemaining;  // in seconds
    bool isWhiteTurn;

    void updateWhiteTimer();
    void updateBlackTimer();
    void updateTimerDisplay(int timeRemaining, bool isWhite);
    void startTurnTimer();

    QComboBox* cbPawnPromotion;
    quint8 promotionType;
    quint8 selectedPromotionType;

};
#endif // SCHACHAPP_H
