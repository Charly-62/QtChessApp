#ifndef SCHACHAPP_H
#define SCHACHAPP_H

#include <QWidget>

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

private:
    Ui::SchachApp *ui;  ///< Pointer to the UI elements of the chess application.
};
#endif // SCHACHAPP_H
