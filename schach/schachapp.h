#ifndef SCHACHAPP_H
#define SCHACHAPP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class SchachApp;
}
QT_END_NAMESPACE

class SchachApp : public QWidget
{
    Q_OBJECT

public:
    SchachApp(QWidget *parent = nullptr);
    ~SchachApp();

private:
    Ui::SchachApp *ui;
};
#endif // SCHACHAPP_H
