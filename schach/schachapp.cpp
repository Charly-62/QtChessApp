#include "schachapp.h"
#include "ui_schachgui.h"

SchachApp::SchachApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SchachApp)
{
    ui->setupUi(this);
}

SchachApp::~SchachApp()
{
    delete ui;
}
