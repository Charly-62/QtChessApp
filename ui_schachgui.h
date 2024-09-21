/********************************************************************************
** Form generated from reading UI file 'schachgui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHACHGUI_H
#define UI_SCHACHGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SchachApp
{
public:
    QStackedWidget *GAME;
    QWidget *initalpage;
    QGroupBox *grpNetwork;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lblIP;
    QLineEdit *leIP;
    QLabel *lblPort;
    QSpinBox *spnPort;
    QPushButton *bConnect;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *lblHostClient;
    QComboBox *cbHostClient;
    QLabel *lblStartingPlayer;
    QComboBox *cbStartingPlayer;
    QLabel *DisplayGame;
    QGroupBox *groupBox_2;
    QPushButton *pbClear;
    QListWidget *lstNetzwerkConsole;
    QGroupBox *groupBox_4;
    QPushButton *bSendName;
    QLineEdit *lename;
    QGroupBox *groupBox_5;
    QPushButton *bStart;
    QWidget *gamepage;
    QStackedWidget *swpawnpromotion;
    QWidget *pawnpromotionpage;
    QGroupBox *grpPawnPromotion;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *cbPawnPromotion;
    QPushButton *pbPawnPromotion;
    QWidget *defaultpage;
    QGroupBox *ScoregrpBox;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *scorelbl2;
    QLabel *scorelbl1;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayoutPlayer2;
    QLabel *lblPlayer2Timer;
    QLabel *opponentplayername;
    QHBoxLayout *deadplayer2;
    QLabel *lblCurrentPlayerName;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayoutPlayer1;
    QLabel *lblPlayer1Timer;
    QLabel *currentplayername;
    QHBoxLayout *deadplayer1;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *G7;
    QPushButton *B6;
    QPushButton *C8;
    QPushButton *D3;
    QPushButton *F2;
    QPushButton *F7;
    QPushButton *G4;
    QPushButton *H6;
    QPushButton *E4;
    QPushButton *A4;
    QPushButton *A1;
    QPushButton *G8;
    QPushButton *G1;
    QPushButton *H7;
    QPushButton *D6;
    QPushButton *B5;
    QPushButton *F5;
    QPushButton *E6;
    QPushButton *B7;
    QPushButton *D8;
    QPushButton *E5;
    QPushButton *E7;
    QPushButton *F1;
    QPushButton *C4;
    QPushButton *H4;
    QPushButton *B4;
    QPushButton *H1;
    QPushButton *G5;
    QPushButton *G2;
    QPushButton *C1;
    QPushButton *H2;
    QPushButton *A3;
    QPushButton *D7;
    QPushButton *F4;
    QPushButton *B3;
    QPushButton *H3;
    QPushButton *G6;
    QPushButton *B8;
    QPushButton *F3;
    QPushButton *F6;
    QPushButton *C3;
    QPushButton *B1;
    QPushButton *A7;
    QPushButton *H5;
    QPushButton *E2;
    QPushButton *C6;
    QPushButton *C2;
    QPushButton *H8;
    QPushButton *C7;
    QPushButton *E8;
    QPushButton *D2;
    QPushButton *F8;
    QPushButton *A2;
    QPushButton *E1;
    QPushButton *E3;
    QPushButton *D1;
    QPushButton *C5;
    QPushButton *D5;
    QPushButton *A5;
    QPushButton *B2;
    QPushButton *A6;
    QPushButton *D4;
    QPushButton *A8;
    QPushButton *G3;
    QGroupBox *NetworkgrpBox;
    QListWidget *lstMoveHistory;
    QListWidget *lstInGameConsole;
    QPushButton *pbUndo;
    QPushButton *pbUndoDeny;
    QPushButton *pbUndoAccept;
    QWidget *layoutWidget;
    QHBoxLayout *XAxisLayout;
    QLabel *labelX1;
    QLabel *labelX2;
    QLabel *labelX3;
    QLabel *labelX4;
    QLabel *labelX5;
    QLabel *labelX6;
    QLabel *labelX7;
    QLabel *labelX8;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *YAxisLayout;
    QLabel *labelY8;
    QLabel *labelY7;
    QLabel *labelY6;
    QLabel *labelY5;
    QLabel *labelY4;
    QLabel *labelY3;
    QLabel *labelY2;
    QLabel *labelY1;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *ChatLayout;
    QListWidget *lstChat;
    QLineEdit *leSendChat;

    void setupUi(QWidget *SchachApp)
    {
        if (SchachApp->objectName().isEmpty())
            SchachApp->setObjectName(QString::fromUtf8("SchachApp"));
        SchachApp->resize(680, 779);
        SchachApp->setStyleSheet(QString::fromUtf8("#leIP[state = \"0\"]{\n"
"background-color: rgb(255, 106, 113)\n"
"}\n"
"\n"
"#leIP[state = \"1\"]{\n"
"background-color: rgb(134, 255, 142)\n"
"}"));
        GAME = new QStackedWidget(SchachApp);
        GAME->setObjectName(QString::fromUtf8("GAME"));
        GAME->setGeometry(QRect(0, 0, 681, 591));
        GAME->setStyleSheet(QString::fromUtf8(""));
        initalpage = new QWidget();
        initalpage->setObjectName(QString::fromUtf8("initalpage"));
        grpNetwork = new QGroupBox(initalpage);
        grpNetwork->setObjectName(QString::fromUtf8("grpNetwork"));
        grpNetwork->setGeometry(QRect(320, 120, 331, 161));
        grpNetwork->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        formLayoutWidget = new QWidget(grpNetwork);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 30, 291, 71));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lblIP = new QLabel(formLayoutWidget);
        lblIP->setObjectName(QString::fromUtf8("lblIP"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblIP);

        leIP = new QLineEdit(formLayoutWidget);
        leIP->setObjectName(QString::fromUtf8("leIP"));
        leIP->setClearButtonEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, leIP);

        lblPort = new QLabel(formLayoutWidget);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblPort);

        spnPort = new QSpinBox(formLayoutWidget);
        spnPort->setObjectName(QString::fromUtf8("spnPort"));
        spnPort->setMinimum(1024);
        spnPort->setMaximum(65535);
        spnPort->setValue(12345);

        formLayout->setWidget(1, QFormLayout::FieldRole, spnPort);

        bConnect = new QPushButton(grpNetwork);
        bConnect->setObjectName(QString::fromUtf8("bConnect"));
        bConnect->setGeometry(QRect(20, 120, 291, 31));
        bConnect->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}\n"
""));
        groupBox = new QGroupBox(initalpage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 130, 271, 131));
        groupBox->setCursor(QCursor(Qt::UpArrowCursor));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        formLayoutWidget_2 = new QWidget(groupBox);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(30, 30, 221, 79));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        lblHostClient = new QLabel(formLayoutWidget_2);
        lblHostClient->setObjectName(QString::fromUtf8("lblHostClient"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lblHostClient);

        cbHostClient = new QComboBox(formLayoutWidget_2);
        cbHostClient->addItem(QString());
        cbHostClient->addItem(QString());
        cbHostClient->addItem(QString());
        cbHostClient->setObjectName(QString::fromUtf8("cbHostClient"));
        cbHostClient->setCursor(QCursor(Qt::ArrowCursor));
        cbHostClient->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #f2f2f2; /* Lighter grey */\n"
"    color: black;\n"
"    border: 2px solid #76c7b7; /* Border color matches QPushButton */\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #5bb7a5; /* Darker teal on hover */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    \n"
"}\n"
"\n"
""));
        cbHostClient->setMaxVisibleItems(10);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cbHostClient);

        lblStartingPlayer = new QLabel(formLayoutWidget_2);
        lblStartingPlayer->setObjectName(QString::fromUtf8("lblStartingPlayer"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblStartingPlayer);

        cbStartingPlayer = new QComboBox(formLayoutWidget_2);
        cbStartingPlayer->addItem(QString());
        cbStartingPlayer->addItem(QString());
        cbStartingPlayer->setObjectName(QString::fromUtf8("cbStartingPlayer"));
        cbStartingPlayer->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #f2f2f2; /* Lighter grey */\n"
"    color: black;\n"
"    border: 2px solid #76c7b7; /* Border color matches QPushButton */\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #5bb7a5; /* Darker teal on hover */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"  \n"
"}\n"
""));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbStartingPlayer);

        DisplayGame = new QLabel(initalpage);
        DisplayGame->setObjectName(QString::fromUtf8("DisplayGame"));
        DisplayGame->setGeometry(QRect(30, 20, 621, 81));
        groupBox_2 = new QGroupBox(initalpage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(320, 290, 331, 281));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        pbClear = new QPushButton(groupBox_2);
        pbClear->setObjectName(QString::fromUtf8("pbClear"));
        pbClear->setGeometry(QRect(20, 230, 291, 31));
        pbClear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}\n"
""));
        lstNetzwerkConsole = new QListWidget(groupBox_2);
        lstNetzwerkConsole->setObjectName(QString::fromUtf8("lstNetzwerkConsole"));
        lstNetzwerkConsole->setGeometry(QRect(20, 30, 291, 191));
        groupBox_4 = new QGroupBox(initalpage);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(30, 270, 271, 131));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        bSendName = new QPushButton(groupBox_4);
        bSendName->setObjectName(QString::fromUtf8("bSendName"));
        bSendName->setGeometry(QRect(20, 80, 231, 31));
        bSendName->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}\n"
""));
        lename = new QLineEdit(groupBox_4);
        lename->setObjectName(QString::fromUtf8("lename"));
        lename->setGeometry(QRect(20, 30, 231, 31));
        groupBox_5 = new QGroupBox(initalpage);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 410, 271, 161));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        bStart = new QPushButton(groupBox_5);
        bStart->setObjectName(QString::fromUtf8("bStart"));
        bStart->setGeometry(QRect(20, 30, 231, 101));
        bStart->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}\n"
""));
        GAME->addWidget(initalpage);
        gamepage = new QWidget();
        gamepage->setObjectName(QString::fromUtf8("gamepage"));
        swpawnpromotion = new QStackedWidget(gamepage);
        swpawnpromotion->setObjectName(QString::fromUtf8("swpawnpromotion"));
        swpawnpromotion->setEnabled(true);
        swpawnpromotion->setGeometry(QRect(460, 0, 201, 121));
        pawnpromotionpage = new QWidget();
        pawnpromotionpage->setObjectName(QString::fromUtf8("pawnpromotionpage"));
        grpPawnPromotion = new QGroupBox(pawnpromotionpage);
        grpPawnPromotion->setObjectName(QString::fromUtf8("grpPawnPromotion"));
        grpPawnPromotion->setGeometry(QRect(10, 10, 181, 101));
        grpPawnPromotion->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 10px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        verticalLayoutWidget = new QWidget(grpPawnPromotion);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 141, 73));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cbPawnPromotion = new QComboBox(verticalLayoutWidget);
        cbPawnPromotion->addItem(QString());
        cbPawnPromotion->addItem(QString());
        cbPawnPromotion->addItem(QString());
        cbPawnPromotion->addItem(QString());
        cbPawnPromotion->addItem(QString());
        cbPawnPromotion->setObjectName(QString::fromUtf8("cbPawnPromotion"));
        cbPawnPromotion->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: #f2f2f2; /* Lighter grey */\n"
"    color: black;\n"
"    border: 2px solid #76c7b7; /* Border color matches QPushButton */\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border-color: #5bb7a5; /* Darker teal on hover */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    \n"
"}\n"
"\n"
""));

        verticalLayout->addWidget(cbPawnPromotion);

        pbPawnPromotion = new QPushButton(verticalLayoutWidget);
        pbPawnPromotion->setObjectName(QString::fromUtf8("pbPawnPromotion"));
        pbPawnPromotion->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}\n"
""));

        verticalLayout->addWidget(pbPawnPromotion);

        swpawnpromotion->addWidget(pawnpromotionpage);
        defaultpage = new QWidget();
        defaultpage->setObjectName(QString::fromUtf8("defaultpage"));
        ScoregrpBox = new QGroupBox(defaultpage);
        ScoregrpBox->setObjectName(QString::fromUtf8("ScoregrpBox"));
        ScoregrpBox->setGeometry(QRect(10, 10, 181, 101));
        ScoregrpBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 10px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        verticalLayoutWidget_3 = new QWidget(ScoregrpBox);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(20, 20, 141, 61));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scorelbl2 = new QLabel(verticalLayoutWidget_3);
        scorelbl2->setObjectName(QString::fromUtf8("scorelbl2"));
        scorelbl2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(scorelbl2);

        scorelbl1 = new QLabel(verticalLayoutWidget_3);
        scorelbl1->setObjectName(QString::fromUtf8("scorelbl1"));
        scorelbl1->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        scorelbl1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(scorelbl1);

        swpawnpromotion->addWidget(defaultpage);
        horizontalLayoutWidget = new QWidget(gamepage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 80, 421, 33));
        horizontalLayoutPlayer2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayoutPlayer2->setObjectName(QString::fromUtf8("horizontalLayoutPlayer2"));
        horizontalLayoutPlayer2->setContentsMargins(0, 0, 0, 0);
        lblPlayer2Timer = new QLabel(horizontalLayoutWidget);
        lblPlayer2Timer->setObjectName(QString::fromUtf8("lblPlayer2Timer"));

        horizontalLayoutPlayer2->addWidget(lblPlayer2Timer);

        opponentplayername = new QLabel(horizontalLayoutWidget);
        opponentplayername->setObjectName(QString::fromUtf8("opponentplayername"));

        horizontalLayoutPlayer2->addWidget(opponentplayername);

        deadplayer2 = new QHBoxLayout();
        deadplayer2->setObjectName(QString::fromUtf8("deadplayer2"));

        horizontalLayoutPlayer2->addLayout(deadplayer2);

        lblCurrentPlayerName = new QLabel(gamepage);
        lblCurrentPlayerName->setObjectName(QString::fromUtf8("lblCurrentPlayerName"));
        lblCurrentPlayerName->setGeometry(QRect(40, 20, 421, 51));
        horizontalLayoutWidget_2 = new QWidget(gamepage);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 550, 421, 33));
        horizontalLayoutPlayer1 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayoutPlayer1->setObjectName(QString::fromUtf8("horizontalLayoutPlayer1"));
        horizontalLayoutPlayer1->setContentsMargins(0, 0, 0, 0);
        lblPlayer1Timer = new QLabel(horizontalLayoutWidget_2);
        lblPlayer1Timer->setObjectName(QString::fromUtf8("lblPlayer1Timer"));

        horizontalLayoutPlayer1->addWidget(lblPlayer1Timer);

        currentplayername = new QLabel(horizontalLayoutWidget_2);
        currentplayername->setObjectName(QString::fromUtf8("currentplayername"));

        horizontalLayoutPlayer1->addWidget(currentplayername);

        deadplayer1 = new QHBoxLayout();
        deadplayer1->setObjectName(QString::fromUtf8("deadplayer1"));

        horizontalLayoutPlayer1->addLayout(deadplayer1);

        gridLayoutWidget = new QWidget(gamepage);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 120, 418, 407));
        gridLayoutWidget->setMinimumSize(QSize(70, 70));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        G7 = new QPushButton(gridLayoutWidget);
        G7->setObjectName(QString::fromUtf8("G7"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(G7->sizePolicy().hasHeightForWidth());
        G7->setSizePolicy(sizePolicy);
        G7->setMinimumSize(QSize(50, 50));
        G7->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(G7, 1, 6, 1, 1);

        B6 = new QPushButton(gridLayoutWidget);
        B6->setObjectName(QString::fromUtf8("B6"));
        sizePolicy.setHeightForWidth(B6->sizePolicy().hasHeightForWidth());
        B6->setSizePolicy(sizePolicy);
        B6->setMinimumSize(QSize(50, 50));
        B6->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(B6, 2, 1, 1, 1);

        C8 = new QPushButton(gridLayoutWidget);
        C8->setObjectName(QString::fromUtf8("C8"));
        sizePolicy.setHeightForWidth(C8->sizePolicy().hasHeightForWidth());
        C8->setSizePolicy(sizePolicy);
        C8->setMinimumSize(QSize(50, 50));
        C8->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(C8, 0, 2, 1, 1);

        D3 = new QPushButton(gridLayoutWidget);
        D3->setObjectName(QString::fromUtf8("D3"));
        sizePolicy.setHeightForWidth(D3->sizePolicy().hasHeightForWidth());
        D3->setSizePolicy(sizePolicy);
        D3->setMinimumSize(QSize(50, 50));
        D3->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(D3, 5, 3, 1, 1);

        F2 = new QPushButton(gridLayoutWidget);
        F2->setObjectName(QString::fromUtf8("F2"));
        sizePolicy.setHeightForWidth(F2->sizePolicy().hasHeightForWidth());
        F2->setSizePolicy(sizePolicy);
        F2->setMinimumSize(QSize(50, 50));
        F2->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(F2, 6, 5, 1, 1);

        F7 = new QPushButton(gridLayoutWidget);
        F7->setObjectName(QString::fromUtf8("F7"));
        sizePolicy.setHeightForWidth(F7->sizePolicy().hasHeightForWidth());
        F7->setSizePolicy(sizePolicy);
        F7->setMinimumSize(QSize(50, 50));
        F7->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(F7, 1, 5, 1, 1);

        G4 = new QPushButton(gridLayoutWidget);
        G4->setObjectName(QString::fromUtf8("G4"));
        sizePolicy.setHeightForWidth(G4->sizePolicy().hasHeightForWidth());
        G4->setSizePolicy(sizePolicy);
        G4->setMinimumSize(QSize(50, 50));
        G4->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(G4, 4, 6, 1, 1);

        H6 = new QPushButton(gridLayoutWidget);
        H6->setObjectName(QString::fromUtf8("H6"));
        sizePolicy.setHeightForWidth(H6->sizePolicy().hasHeightForWidth());
        H6->setSizePolicy(sizePolicy);
        H6->setMinimumSize(QSize(50, 50));
        H6->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(H6, 2, 7, 1, 1);

        E4 = new QPushButton(gridLayoutWidget);
        E4->setObjectName(QString::fromUtf8("E4"));
        sizePolicy.setHeightForWidth(E4->sizePolicy().hasHeightForWidth());
        E4->setSizePolicy(sizePolicy);
        E4->setMinimumSize(QSize(50, 50));
        E4->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(E4, 4, 4, 1, 1);

        A4 = new QPushButton(gridLayoutWidget);
        A4->setObjectName(QString::fromUtf8("A4"));
        sizePolicy.setHeightForWidth(A4->sizePolicy().hasHeightForWidth());
        A4->setSizePolicy(sizePolicy);
        A4->setMinimumSize(QSize(50, 50));
        A4->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(A4, 4, 0, 1, 1);

        A1 = new QPushButton(gridLayoutWidget);
        A1->setObjectName(QString::fromUtf8("A1"));
        sizePolicy.setHeightForWidth(A1->sizePolicy().hasHeightForWidth());
        A1->setSizePolicy(sizePolicy);
        A1->setMinimumSize(QSize(50, 50));
        A1->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(A1, 7, 0, 1, 1);

        G8 = new QPushButton(gridLayoutWidget);
        G8->setObjectName(QString::fromUtf8("G8"));
        sizePolicy.setHeightForWidth(G8->sizePolicy().hasHeightForWidth());
        G8->setSizePolicy(sizePolicy);
        G8->setMinimumSize(QSize(50, 50));
        G8->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(G8, 0, 6, 1, 1);

        G1 = new QPushButton(gridLayoutWidget);
        G1->setObjectName(QString::fromUtf8("G1"));
        sizePolicy.setHeightForWidth(G1->sizePolicy().hasHeightForWidth());
        G1->setSizePolicy(sizePolicy);
        G1->setMinimumSize(QSize(50, 50));
        G1->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(G1, 7, 6, 1, 1);

        H7 = new QPushButton(gridLayoutWidget);
        H7->setObjectName(QString::fromUtf8("H7"));
        sizePolicy.setHeightForWidth(H7->sizePolicy().hasHeightForWidth());
        H7->setSizePolicy(sizePolicy);
        H7->setMinimumSize(QSize(50, 50));
        H7->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(H7, 1, 7, 1, 1);

        D6 = new QPushButton(gridLayoutWidget);
        D6->setObjectName(QString::fromUtf8("D6"));
        sizePolicy.setHeightForWidth(D6->sizePolicy().hasHeightForWidth());
        D6->setSizePolicy(sizePolicy);
        D6->setMinimumSize(QSize(50, 50));
        D6->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(D6, 2, 3, 1, 1);

        B5 = new QPushButton(gridLayoutWidget);
        B5->setObjectName(QString::fromUtf8("B5"));
        sizePolicy.setHeightForWidth(B5->sizePolicy().hasHeightForWidth());
        B5->setSizePolicy(sizePolicy);
        B5->setMinimumSize(QSize(50, 50));
        B5->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(B5, 3, 1, 1, 1);

        F5 = new QPushButton(gridLayoutWidget);
        F5->setObjectName(QString::fromUtf8("F5"));
        sizePolicy.setHeightForWidth(F5->sizePolicy().hasHeightForWidth());
        F5->setSizePolicy(sizePolicy);
        F5->setMinimumSize(QSize(50, 50));
        F5->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(F5, 3, 5, 1, 1);

        E6 = new QPushButton(gridLayoutWidget);
        E6->setObjectName(QString::fromUtf8("E6"));
        sizePolicy.setHeightForWidth(E6->sizePolicy().hasHeightForWidth());
        E6->setSizePolicy(sizePolicy);
        E6->setMinimumSize(QSize(50, 50));
        E6->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(E6, 2, 4, 1, 1);

        B7 = new QPushButton(gridLayoutWidget);
        B7->setObjectName(QString::fromUtf8("B7"));
        sizePolicy.setHeightForWidth(B7->sizePolicy().hasHeightForWidth());
        B7->setSizePolicy(sizePolicy);
        B7->setMinimumSize(QSize(50, 50));
        B7->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(B7, 1, 1, 1, 1);

        D8 = new QPushButton(gridLayoutWidget);
        D8->setObjectName(QString::fromUtf8("D8"));
        sizePolicy.setHeightForWidth(D8->sizePolicy().hasHeightForWidth());
        D8->setSizePolicy(sizePolicy);
        D8->setMinimumSize(QSize(50, 50));
        D8->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(D8, 0, 3, 1, 1);

        E5 = new QPushButton(gridLayoutWidget);
        E5->setObjectName(QString::fromUtf8("E5"));
        sizePolicy.setHeightForWidth(E5->sizePolicy().hasHeightForWidth());
        E5->setSizePolicy(sizePolicy);
        E5->setMinimumSize(QSize(50, 50));
        E5->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)\n"
""));

        gridLayout->addWidget(E5, 3, 4, 1, 1);

        E7 = new QPushButton(gridLayoutWidget);
        E7->setObjectName(QString::fromUtf8("E7"));
        sizePolicy.setHeightForWidth(E7->sizePolicy().hasHeightForWidth());
        E7->setSizePolicy(sizePolicy);
        E7->setMinimumSize(QSize(50, 50));
        E7->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(E7, 1, 4, 1, 1);

        F1 = new QPushButton(gridLayoutWidget);
        F1->setObjectName(QString::fromUtf8("F1"));
        sizePolicy.setHeightForWidth(F1->sizePolicy().hasHeightForWidth());
        F1->setSizePolicy(sizePolicy);
        F1->setMinimumSize(QSize(50, 50));
        F1->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(F1, 7, 5, 1, 1);

        C4 = new QPushButton(gridLayoutWidget);
        C4->setObjectName(QString::fromUtf8("C4"));
        sizePolicy.setHeightForWidth(C4->sizePolicy().hasHeightForWidth());
        C4->setSizePolicy(sizePolicy);
        C4->setMinimumSize(QSize(50, 50));
        C4->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(C4, 4, 2, 1, 1);

        H4 = new QPushButton(gridLayoutWidget);
        H4->setObjectName(QString::fromUtf8("H4"));
        sizePolicy.setHeightForWidth(H4->sizePolicy().hasHeightForWidth());
        H4->setSizePolicy(sizePolicy);
        H4->setMinimumSize(QSize(50, 50));
        H4->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(H4, 4, 7, 1, 1);

        B4 = new QPushButton(gridLayoutWidget);
        B4->setObjectName(QString::fromUtf8("B4"));
        sizePolicy.setHeightForWidth(B4->sizePolicy().hasHeightForWidth());
        B4->setSizePolicy(sizePolicy);
        B4->setMinimumSize(QSize(50, 50));
        B4->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(B4, 4, 1, 1, 1);

        H1 = new QPushButton(gridLayoutWidget);
        H1->setObjectName(QString::fromUtf8("H1"));
        H1->setEnabled(true);
        sizePolicy.setHeightForWidth(H1->sizePolicy().hasHeightForWidth());
        H1->setSizePolicy(sizePolicy);
        H1->setMinimumSize(QSize(50, 50));
        H1->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));
        H1->setIconSize(QSize(48, 48));

        gridLayout->addWidget(H1, 7, 7, 1, 1);

        G5 = new QPushButton(gridLayoutWidget);
        G5->setObjectName(QString::fromUtf8("G5"));
        sizePolicy.setHeightForWidth(G5->sizePolicy().hasHeightForWidth());
        G5->setSizePolicy(sizePolicy);
        G5->setMinimumSize(QSize(50, 50));
        G5->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(G5, 3, 6, 1, 1);

        G2 = new QPushButton(gridLayoutWidget);
        G2->setObjectName(QString::fromUtf8("G2"));
        sizePolicy.setHeightForWidth(G2->sizePolicy().hasHeightForWidth());
        G2->setSizePolicy(sizePolicy);
        G2->setMinimumSize(QSize(50, 50));
        G2->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(G2, 6, 6, 1, 1);

        C1 = new QPushButton(gridLayoutWidget);
        C1->setObjectName(QString::fromUtf8("C1"));
        sizePolicy.setHeightForWidth(C1->sizePolicy().hasHeightForWidth());
        C1->setSizePolicy(sizePolicy);
        C1->setMinimumSize(QSize(50, 50));
        C1->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(C1, 7, 2, 1, 1);

        H2 = new QPushButton(gridLayoutWidget);
        H2->setObjectName(QString::fromUtf8("H2"));
        sizePolicy.setHeightForWidth(H2->sizePolicy().hasHeightForWidth());
        H2->setSizePolicy(sizePolicy);
        H2->setMinimumSize(QSize(50, 50));
        H2->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(H2, 6, 7, 1, 1);

        A3 = new QPushButton(gridLayoutWidget);
        A3->setObjectName(QString::fromUtf8("A3"));
        sizePolicy.setHeightForWidth(A3->sizePolicy().hasHeightForWidth());
        A3->setSizePolicy(sizePolicy);
        A3->setMinimumSize(QSize(50, 50));
        A3->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(A3, 5, 0, 1, 1);

        D7 = new QPushButton(gridLayoutWidget);
        D7->setObjectName(QString::fromUtf8("D7"));
        sizePolicy.setHeightForWidth(D7->sizePolicy().hasHeightForWidth());
        D7->setSizePolicy(sizePolicy);
        D7->setMinimumSize(QSize(50, 50));
        D7->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(D7, 1, 3, 1, 1);

        F4 = new QPushButton(gridLayoutWidget);
        F4->setObjectName(QString::fromUtf8("F4"));
        sizePolicy.setHeightForWidth(F4->sizePolicy().hasHeightForWidth());
        F4->setSizePolicy(sizePolicy);
        F4->setMinimumSize(QSize(50, 50));
        F4->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(F4, 4, 5, 1, 1);

        B3 = new QPushButton(gridLayoutWidget);
        B3->setObjectName(QString::fromUtf8("B3"));
        sizePolicy.setHeightForWidth(B3->sizePolicy().hasHeightForWidth());
        B3->setSizePolicy(sizePolicy);
        B3->setMinimumSize(QSize(50, 50));
        B3->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(B3, 5, 1, 1, 1);

        H3 = new QPushButton(gridLayoutWidget);
        H3->setObjectName(QString::fromUtf8("H3"));
        sizePolicy.setHeightForWidth(H3->sizePolicy().hasHeightForWidth());
        H3->setSizePolicy(sizePolicy);
        H3->setMinimumSize(QSize(50, 50));
        H3->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(H3, 5, 7, 1, 1);

        G6 = new QPushButton(gridLayoutWidget);
        G6->setObjectName(QString::fromUtf8("G6"));
        sizePolicy.setHeightForWidth(G6->sizePolicy().hasHeightForWidth());
        G6->setSizePolicy(sizePolicy);
        G6->setMinimumSize(QSize(50, 50));
        G6->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(G6, 2, 6, 1, 1);

        B8 = new QPushButton(gridLayoutWidget);
        B8->setObjectName(QString::fromUtf8("B8"));
        sizePolicy.setHeightForWidth(B8->sizePolicy().hasHeightForWidth());
        B8->setSizePolicy(sizePolicy);
        B8->setMinimumSize(QSize(50, 50));
        B8->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(B8, 0, 1, 1, 1);

        F3 = new QPushButton(gridLayoutWidget);
        F3->setObjectName(QString::fromUtf8("F3"));
        sizePolicy.setHeightForWidth(F3->sizePolicy().hasHeightForWidth());
        F3->setSizePolicy(sizePolicy);
        F3->setMinimumSize(QSize(50, 50));
        F3->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(F3, 5, 5, 1, 1);

        F6 = new QPushButton(gridLayoutWidget);
        F6->setObjectName(QString::fromUtf8("F6"));
        sizePolicy.setHeightForWidth(F6->sizePolicy().hasHeightForWidth());
        F6->setSizePolicy(sizePolicy);
        F6->setMinimumSize(QSize(50, 50));
        F6->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(F6, 2, 5, 1, 1);

        C3 = new QPushButton(gridLayoutWidget);
        C3->setObjectName(QString::fromUtf8("C3"));
        sizePolicy.setHeightForWidth(C3->sizePolicy().hasHeightForWidth());
        C3->setSizePolicy(sizePolicy);
        C3->setMinimumSize(QSize(50, 50));
        C3->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(C3, 5, 2, 1, 1);

        B1 = new QPushButton(gridLayoutWidget);
        B1->setObjectName(QString::fromUtf8("B1"));
        sizePolicy.setHeightForWidth(B1->sizePolicy().hasHeightForWidth());
        B1->setSizePolicy(sizePolicy);
        B1->setMinimumSize(QSize(50, 50));
        B1->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));
        B1->setAutoRepeatDelay(301);

        gridLayout->addWidget(B1, 7, 1, 1, 1);

        A7 = new QPushButton(gridLayoutWidget);
        A7->setObjectName(QString::fromUtf8("A7"));
        sizePolicy.setHeightForWidth(A7->sizePolicy().hasHeightForWidth());
        A7->setSizePolicy(sizePolicy);
        A7->setMinimumSize(QSize(50, 50));
        A7->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(A7, 1, 0, 1, 1);

        H5 = new QPushButton(gridLayoutWidget);
        H5->setObjectName(QString::fromUtf8("H5"));
        sizePolicy.setHeightForWidth(H5->sizePolicy().hasHeightForWidth());
        H5->setSizePolicy(sizePolicy);
        H5->setMinimumSize(QSize(50, 50));
        H5->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(H5, 3, 7, 1, 1);

        E2 = new QPushButton(gridLayoutWidget);
        E2->setObjectName(QString::fromUtf8("E2"));
        sizePolicy.setHeightForWidth(E2->sizePolicy().hasHeightForWidth());
        E2->setSizePolicy(sizePolicy);
        E2->setMinimumSize(QSize(50, 50));
        E2->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(E2, 6, 4, 1, 1);

        C6 = new QPushButton(gridLayoutWidget);
        C6->setObjectName(QString::fromUtf8("C6"));
        sizePolicy.setHeightForWidth(C6->sizePolicy().hasHeightForWidth());
        C6->setSizePolicy(sizePolicy);
        C6->setMinimumSize(QSize(50, 50));
        C6->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(C6, 2, 2, 1, 1);

        C2 = new QPushButton(gridLayoutWidget);
        C2->setObjectName(QString::fromUtf8("C2"));
        sizePolicy.setHeightForWidth(C2->sizePolicy().hasHeightForWidth());
        C2->setSizePolicy(sizePolicy);
        C2->setMinimumSize(QSize(50, 50));
        C2->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(C2, 6, 2, 1, 1);

        H8 = new QPushButton(gridLayoutWidget);
        H8->setObjectName(QString::fromUtf8("H8"));
        sizePolicy.setHeightForWidth(H8->sizePolicy().hasHeightForWidth());
        H8->setSizePolicy(sizePolicy);
        H8->setMinimumSize(QSize(50, 50));
        H8->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(H8, 0, 7, 1, 1);

        C7 = new QPushButton(gridLayoutWidget);
        C7->setObjectName(QString::fromUtf8("C7"));
        sizePolicy.setHeightForWidth(C7->sizePolicy().hasHeightForWidth());
        C7->setSizePolicy(sizePolicy);
        C7->setMinimumSize(QSize(50, 50));
        C7->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(C7, 1, 2, 1, 1);

        E8 = new QPushButton(gridLayoutWidget);
        E8->setObjectName(QString::fromUtf8("E8"));
        sizePolicy.setHeightForWidth(E8->sizePolicy().hasHeightForWidth());
        E8->setSizePolicy(sizePolicy);
        E8->setMinimumSize(QSize(50, 50));
        E8->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(E8, 0, 4, 1, 1);

        D2 = new QPushButton(gridLayoutWidget);
        D2->setObjectName(QString::fromUtf8("D2"));
        sizePolicy.setHeightForWidth(D2->sizePolicy().hasHeightForWidth());
        D2->setSizePolicy(sizePolicy);
        D2->setMinimumSize(QSize(50, 50));
        D2->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(D2, 6, 3, 1, 1);

        F8 = new QPushButton(gridLayoutWidget);
        F8->setObjectName(QString::fromUtf8("F8"));
        sizePolicy.setHeightForWidth(F8->sizePolicy().hasHeightForWidth());
        F8->setSizePolicy(sizePolicy);
        F8->setMinimumSize(QSize(50, 50));
        F8->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(F8, 0, 5, 1, 1);

        A2 = new QPushButton(gridLayoutWidget);
        A2->setObjectName(QString::fromUtf8("A2"));
        sizePolicy.setHeightForWidth(A2->sizePolicy().hasHeightForWidth());
        A2->setSizePolicy(sizePolicy);
        A2->setMinimumSize(QSize(50, 50));
        A2->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(A2, 6, 0, 1, 1);

        E1 = new QPushButton(gridLayoutWidget);
        E1->setObjectName(QString::fromUtf8("E1"));
        sizePolicy.setHeightForWidth(E1->sizePolicy().hasHeightForWidth());
        E1->setSizePolicy(sizePolicy);
        E1->setMinimumSize(QSize(50, 50));
        E1->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(E1, 7, 4, 1, 1);

        E3 = new QPushButton(gridLayoutWidget);
        E3->setObjectName(QString::fromUtf8("E3"));
        sizePolicy.setHeightForWidth(E3->sizePolicy().hasHeightForWidth());
        E3->setSizePolicy(sizePolicy);
        E3->setMinimumSize(QSize(50, 50));
        E3->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(E3, 5, 4, 1, 1);

        D1 = new QPushButton(gridLayoutWidget);
        D1->setObjectName(QString::fromUtf8("D1"));
        sizePolicy.setHeightForWidth(D1->sizePolicy().hasHeightForWidth());
        D1->setSizePolicy(sizePolicy);
        D1->setMinimumSize(QSize(50, 50));
        D1->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(D1, 7, 3, 1, 1);

        C5 = new QPushButton(gridLayoutWidget);
        C5->setObjectName(QString::fromUtf8("C5"));
        sizePolicy.setHeightForWidth(C5->sizePolicy().hasHeightForWidth());
        C5->setSizePolicy(sizePolicy);
        C5->setMinimumSize(QSize(50, 50));
        C5->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(C5, 3, 2, 1, 1);

        D5 = new QPushButton(gridLayoutWidget);
        D5->setObjectName(QString::fromUtf8("D5"));
        sizePolicy.setHeightForWidth(D5->sizePolicy().hasHeightForWidth());
        D5->setSizePolicy(sizePolicy);
        D5->setMinimumSize(QSize(50, 50));
        D5->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(D5, 3, 3, 1, 1);

        A5 = new QPushButton(gridLayoutWidget);
        A5->setObjectName(QString::fromUtf8("A5"));
        sizePolicy.setHeightForWidth(A5->sizePolicy().hasHeightForWidth());
        A5->setSizePolicy(sizePolicy);
        A5->setMinimumSize(QSize(50, 50));
        A5->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(A5, 3, 0, 1, 1);

        B2 = new QPushButton(gridLayoutWidget);
        B2->setObjectName(QString::fromUtf8("B2"));
        sizePolicy.setHeightForWidth(B2->sizePolicy().hasHeightForWidth());
        B2->setSizePolicy(sizePolicy);
        B2->setMinimumSize(QSize(50, 50));
        B2->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(B2, 6, 1, 1, 1);

        A6 = new QPushButton(gridLayoutWidget);
        A6->setObjectName(QString::fromUtf8("A6"));
        sizePolicy.setHeightForWidth(A6->sizePolicy().hasHeightForWidth());
        A6->setSizePolicy(sizePolicy);
        A6->setMinimumSize(QSize(50, 50));
        A6->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));

        gridLayout->addWidget(A6, 2, 0, 1, 1);

        D4 = new QPushButton(gridLayoutWidget);
        D4->setObjectName(QString::fromUtf8("D4"));
        sizePolicy.setHeightForWidth(D4->sizePolicy().hasHeightForWidth());
        D4->setSizePolicy(sizePolicy);
        D4->setMinimumSize(QSize(50, 50));
        D4->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(D4, 4, 3, 1, 1);

        A8 = new QPushButton(gridLayoutWidget);
        A8->setObjectName(QString::fromUtf8("A8"));
        sizePolicy.setHeightForWidth(A8->sizePolicy().hasHeightForWidth());
        A8->setSizePolicy(sizePolicy);
        A8->setMinimumSize(QSize(50, 50));
        A8->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 228, 229)"));
        A8->setAutoRepeatDelay(301);

        gridLayout->addWidget(A8, 0, 0, 1, 1);

        G3 = new QPushButton(gridLayoutWidget);
        G3->setObjectName(QString::fromUtf8("G3"));
        sizePolicy.setHeightForWidth(G3->sizePolicy().hasHeightForWidth());
        G3->setSizePolicy(sizePolicy);
        G3->setMinimumSize(QSize(50, 50));
        G3->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 121, 121)"));

        gridLayout->addWidget(G3, 5, 6, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 1);
        gridLayout->setRowStretch(5, 1);
        gridLayout->setRowStretch(6, 1);
        gridLayout->setRowStretch(7, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 1);
        gridLayout->setColumnStretch(5, 1);
        gridLayout->setColumnStretch(6, 1);
        gridLayout->setColumnStretch(7, 1);
        gridLayout->setColumnMinimumWidth(0, 50);
        gridLayout->setColumnMinimumWidth(1, 50);
        gridLayout->setColumnMinimumWidth(2, 50);
        gridLayout->setColumnMinimumWidth(3, 50);
        gridLayout->setColumnMinimumWidth(4, 50);
        gridLayout->setColumnMinimumWidth(5, 50);
        gridLayout->setColumnMinimumWidth(6, 50);
        gridLayout->setColumnMinimumWidth(7, 50);
        gridLayout->setRowMinimumHeight(0, 50);
        gridLayout->setRowMinimumHeight(1, 50);
        gridLayout->setRowMinimumHeight(2, 50);
        gridLayout->setRowMinimumHeight(3, 50);
        gridLayout->setRowMinimumHeight(4, 50);
        gridLayout->setRowMinimumHeight(5, 50);
        gridLayout->setRowMinimumHeight(6, 50);
        gridLayout->setRowMinimumHeight(7, 50);
        NetworkgrpBox = new QGroupBox(gamepage);
        NetworkgrpBox->setObjectName(QString::fromUtf8("NetworkgrpBox"));
        NetworkgrpBox->setGeometry(QRect(470, 120, 181, 461));
        NetworkgrpBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 10px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        lstMoveHistory = new QListWidget(NetworkgrpBox);
        lstMoveHistory->setObjectName(QString::fromUtf8("lstMoveHistory"));
        lstMoveHistory->setGeometry(QRect(10, 10, 161, 261));
        lstInGameConsole = new QListWidget(NetworkgrpBox);
        lstInGameConsole->setObjectName(QString::fromUtf8("lstInGameConsole"));
        lstInGameConsole->setGeometry(QRect(10, 280, 161, 111));
        pbUndo = new QPushButton(NetworkgrpBox);
        pbUndo->setObjectName(QString::fromUtf8("pbUndo"));
        pbUndo->setGeometry(QRect(10, 400, 161, 21));
        pbUndo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}"));
        pbUndoDeny = new QPushButton(NetworkgrpBox);
        pbUndoDeny->setObjectName(QString::fromUtf8("pbUndoDeny"));
        pbUndoDeny->setGeometry(QRect(100, 430, 71, 21));
        pbUndoDeny->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}"));
        pbUndoAccept = new QPushButton(NetworkgrpBox);
        pbUndoAccept->setObjectName(QString::fromUtf8("pbUndoAccept"));
        pbUndoAccept->setGeometry(QRect(10, 430, 81, 21));
        pbUndoAccept->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #76c7b7; /* Light blue-green (teal) */\n"
"    color: black;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    font-size: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5bb7a5; /* Slightly darker teal for hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4fa89a; /* Darker blue-green when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: lightgrey;\n"
"    color: grey;\n"
"}"));
        layoutWidget = new QWidget(gamepage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 530, 421, 22));
        XAxisLayout = new QHBoxLayout(layoutWidget);
        XAxisLayout->setObjectName(QString::fromUtf8("XAxisLayout"));
        XAxisLayout->setContentsMargins(0, 0, 0, 0);
        labelX1 = new QLabel(layoutWidget);
        labelX1->setObjectName(QString::fromUtf8("labelX1"));
        labelX1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX1);

        labelX2 = new QLabel(layoutWidget);
        labelX2->setObjectName(QString::fromUtf8("labelX2"));
        labelX2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX2);

        labelX3 = new QLabel(layoutWidget);
        labelX3->setObjectName(QString::fromUtf8("labelX3"));
        labelX3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX3);

        labelX4 = new QLabel(layoutWidget);
        labelX4->setObjectName(QString::fromUtf8("labelX4"));
        labelX4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX4);

        labelX5 = new QLabel(layoutWidget);
        labelX5->setObjectName(QString::fromUtf8("labelX5"));
        labelX5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX5);

        labelX6 = new QLabel(layoutWidget);
        labelX6->setObjectName(QString::fromUtf8("labelX6"));
        labelX6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX6);

        labelX7 = new QLabel(layoutWidget);
        labelX7->setObjectName(QString::fromUtf8("labelX7"));
        labelX7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX7);

        labelX8 = new QLabel(layoutWidget);
        labelX8->setObjectName(QString::fromUtf8("labelX8"));
        labelX8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        XAxisLayout->addWidget(labelX8);

        verticalLayoutWidget_4 = new QWidget(gamepage);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(20, 120, 16, 411));
        YAxisLayout = new QVBoxLayout(verticalLayoutWidget_4);
        YAxisLayout->setObjectName(QString::fromUtf8("YAxisLayout"));
        YAxisLayout->setContentsMargins(0, 0, 0, 0);
        labelY8 = new QLabel(verticalLayoutWidget_4);
        labelY8->setObjectName(QString::fromUtf8("labelY8"));

        YAxisLayout->addWidget(labelY8);

        labelY7 = new QLabel(verticalLayoutWidget_4);
        labelY7->setObjectName(QString::fromUtf8("labelY7"));

        YAxisLayout->addWidget(labelY7);

        labelY6 = new QLabel(verticalLayoutWidget_4);
        labelY6->setObjectName(QString::fromUtf8("labelY6"));

        YAxisLayout->addWidget(labelY6);

        labelY5 = new QLabel(verticalLayoutWidget_4);
        labelY5->setObjectName(QString::fromUtf8("labelY5"));

        YAxisLayout->addWidget(labelY5);

        labelY4 = new QLabel(verticalLayoutWidget_4);
        labelY4->setObjectName(QString::fromUtf8("labelY4"));

        YAxisLayout->addWidget(labelY4);

        labelY3 = new QLabel(verticalLayoutWidget_4);
        labelY3->setObjectName(QString::fromUtf8("labelY3"));

        YAxisLayout->addWidget(labelY3);

        labelY2 = new QLabel(verticalLayoutWidget_4);
        labelY2->setObjectName(QString::fromUtf8("labelY2"));

        YAxisLayout->addWidget(labelY2);

        labelY1 = new QLabel(verticalLayoutWidget_4);
        labelY1->setObjectName(QString::fromUtf8("labelY1"));

        YAxisLayout->addWidget(labelY1);

        GAME->addWidget(gamepage);
        groupBox_3 = new QGroupBox(SchachApp);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 590, 621, 171));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #f2f2f2; \n"
"    border: 2px solid #76c7b7; \n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; \n"
"    padding: 0 5px; \n"
"    font-size: 30px;\n"
"    font-weight: bold; \n"
"    color: #2c3e50;\n"
"	font-family: 'Comic Sans MS', cursive, sans-serif;\n"
"}"));
        verticalLayoutWidget_2 = new QWidget(groupBox_3);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 20, 591, 131));
        ChatLayout = new QVBoxLayout(verticalLayoutWidget_2);
        ChatLayout->setObjectName(QString::fromUtf8("ChatLayout"));
        ChatLayout->setContentsMargins(0, 0, 0, 0);
        lstChat = new QListWidget(verticalLayoutWidget_2);
        lstChat->setObjectName(QString::fromUtf8("lstChat"));

        ChatLayout->addWidget(lstChat);

        leSendChat = new QLineEdit(verticalLayoutWidget_2);
        leSendChat->setObjectName(QString::fromUtf8("leSendChat"));
        leSendChat->setMaxLength(100);

        ChatLayout->addWidget(leSendChat);


        retranslateUi(SchachApp);

        GAME->setCurrentIndex(1);
        swpawnpromotion->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SchachApp);
    } // setupUi

    void retranslateUi(QWidget *SchachApp)
    {
        SchachApp->setWindowTitle(QCoreApplication::translate("SchachApp", "SchachApp", nullptr));
        grpNetwork->setTitle(QCoreApplication::translate("SchachApp", "Network", nullptr));
        lblIP->setText(QCoreApplication::translate("SchachApp", "IP Address:", nullptr));
        leIP->setInputMask(QCoreApplication::translate("SchachApp", "000.000.000.000;_", nullptr));
        leIP->setText(QCoreApplication::translate("SchachApp", "127.0.0.1", nullptr));
        leIP->setProperty("state", QVariant(QString()));
        lblPort->setText(QCoreApplication::translate("SchachApp", "Port:", nullptr));
        bConnect->setText(QCoreApplication::translate("SchachApp", "Connect", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SchachApp", "Settings", nullptr));
        lblHostClient->setText(QCoreApplication::translate("SchachApp", "Play as:", nullptr));
        cbHostClient->setItemText(0, QCoreApplication::translate("SchachApp", "Local", nullptr));
        cbHostClient->setItemText(1, QCoreApplication::translate("SchachApp", "Client", nullptr));
        cbHostClient->setItemText(2, QCoreApplication::translate("SchachApp", "Server", nullptr));

        lblStartingPlayer->setText(QCoreApplication::translate("SchachApp", "Starting Player: ", nullptr));
        cbStartingPlayer->setItemText(0, QCoreApplication::translate("SchachApp", "Client", nullptr));
        cbStartingPlayer->setItemText(1, QCoreApplication::translate("SchachApp", "Server", nullptr));

        DisplayGame->setText(QCoreApplication::translate("SchachApp", "WelcomeDisplay", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SchachApp", "Network State", nullptr));
        pbClear->setText(QCoreApplication::translate("SchachApp", "Clear", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SchachApp", "Your Name", nullptr));
        bSendName->setText(QCoreApplication::translate("SchachApp", "Send", nullptr));
        groupBox_5->setTitle(QString());
        bStart->setText(QCoreApplication::translate("SchachApp", "Start Game", nullptr));
        grpPawnPromotion->setTitle(QCoreApplication::translate("SchachApp", "Pawn Promotion", nullptr));
        cbPawnPromotion->setItemText(0, QCoreApplication::translate("SchachApp", "Not Selected", nullptr));
        cbPawnPromotion->setItemText(1, QCoreApplication::translate("SchachApp", "Queen", nullptr));
        cbPawnPromotion->setItemText(2, QCoreApplication::translate("SchachApp", "Rook", nullptr));
        cbPawnPromotion->setItemText(3, QCoreApplication::translate("SchachApp", "Knight", nullptr));
        cbPawnPromotion->setItemText(4, QCoreApplication::translate("SchachApp", "Bishop", nullptr));

        pbPawnPromotion->setText(QCoreApplication::translate("SchachApp", "OK", nullptr));
        ScoregrpBox->setTitle(QCoreApplication::translate("SchachApp", "Score", nullptr));
        scorelbl2->setText(QCoreApplication::translate("SchachApp", "ScoreBlack", nullptr));
        scorelbl1->setText(QCoreApplication::translate("SchachApp", "ScoreWhite", nullptr));
        lblPlayer2Timer->setText(QCoreApplication::translate("SchachApp", "10:00", nullptr));
        opponentplayername->setText(QCoreApplication::translate("SchachApp", "Oppenent player", nullptr));
        lblCurrentPlayerName->setText(QCoreApplication::translate("SchachApp", "Display", nullptr));
        lblPlayer1Timer->setText(QCoreApplication::translate("SchachApp", "10:00", nullptr));
        currentplayername->setText(QCoreApplication::translate("SchachApp", "Current player", nullptr));
        G7->setText(QString());
        B6->setText(QString());
        C8->setText(QString());
        D3->setText(QString());
        F2->setText(QString());
        F7->setText(QString());
        G4->setText(QString());
        H6->setText(QString());
        E4->setText(QString());
        A4->setText(QString());
        A1->setText(QString());
        G8->setText(QString());
        G1->setText(QString());
        H7->setText(QString());
        D6->setText(QString());
        B5->setText(QString());
        F5->setText(QString());
        E6->setText(QString());
        B7->setText(QString());
        D8->setText(QString());
        E5->setText(QString());
        E7->setText(QString());
        F1->setText(QString());
        C4->setText(QString());
        H4->setText(QString());
        B4->setText(QString());
        H1->setText(QString());
        G5->setText(QString());
        G2->setText(QString());
        C1->setText(QString());
        H2->setText(QString());
        A3->setText(QString());
        D7->setText(QString());
        F4->setText(QString());
        B3->setText(QString());
        H3->setText(QString());
        G6->setText(QString());
        B8->setText(QString());
        F3->setText(QString());
        F6->setText(QString());
        C3->setText(QString());
        B1->setText(QString());
        A7->setText(QString());
        H5->setText(QString());
        E2->setText(QString());
        C6->setText(QString());
        C2->setText(QString());
        H8->setText(QString());
        C7->setText(QString());
        E8->setText(QString());
        D2->setText(QString());
        F8->setText(QString());
        A2->setText(QString());
        E1->setText(QString());
        E3->setText(QString());
        D1->setText(QString());
        C5->setText(QString());
        D5->setText(QString());
        A5->setText(QString());
        B2->setText(QString());
        A6->setText(QString());
        D4->setText(QString());
        A8->setText(QString());
        G3->setText(QString());
        NetworkgrpBox->setTitle(QString());
        pbUndo->setText(QCoreApplication::translate("SchachApp", "Undo Move", nullptr));
        pbUndoDeny->setText(QCoreApplication::translate("SchachApp", "Deny ", nullptr));
        pbUndoAccept->setText(QCoreApplication::translate("SchachApp", "Accept ", nullptr));
        labelX1->setText(QCoreApplication::translate("SchachApp", "A", nullptr));
        labelX2->setText(QCoreApplication::translate("SchachApp", "B", nullptr));
        labelX3->setText(QCoreApplication::translate("SchachApp", "C", nullptr));
        labelX4->setText(QCoreApplication::translate("SchachApp", "D", nullptr));
        labelX5->setText(QCoreApplication::translate("SchachApp", "E", nullptr));
        labelX6->setText(QCoreApplication::translate("SchachApp", "F", nullptr));
        labelX7->setText(QCoreApplication::translate("SchachApp", "G", nullptr));
        labelX8->setText(QCoreApplication::translate("SchachApp", "H", nullptr));
        labelY8->setText(QCoreApplication::translate("SchachApp", "8", nullptr));
        labelY7->setText(QCoreApplication::translate("SchachApp", "7", nullptr));
        labelY6->setText(QCoreApplication::translate("SchachApp", "6", nullptr));
        labelY5->setText(QCoreApplication::translate("SchachApp", "5", nullptr));
        labelY4->setText(QCoreApplication::translate("SchachApp", "4", nullptr));
        labelY3->setText(QCoreApplication::translate("SchachApp", "3", nullptr));
        labelY2->setText(QCoreApplication::translate("SchachApp", "2", nullptr));
        labelY1->setText(QCoreApplication::translate("SchachApp", "1", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SchachApp", "Chat", nullptr));
        leSendChat->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SchachApp: public Ui_SchachApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHACHGUI_H
