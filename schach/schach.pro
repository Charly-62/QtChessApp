QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    game.cpp \
    king.cpp \
    knight.cpp \
    logik.cpp \
    main.cpp \
    mytcpclient.cpp \
    mytcpserver.cpp \
    netzwerk.cpp \
    pawn.cpp \
    queen.cpp \
    rook.cpp \
    schachapp.cpp

HEADERS += \
    bishop.h \
    game.h \
    king.h \
    knight.h \
    logik.h \
    mytcpclient.h \
    mytcpserver.h \
    netzwerk.h \
    pawn.h \
    piece.h \
    queen.h \
    rook.h \
    schachapp.h

FORMS += \
    schachgui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bannedwords.qrc \
    images.qrc

DISTFILES += \
    List_of_banned_words/de.txt
