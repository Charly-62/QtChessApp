/**
 * @file main.cpp
 * @brief This file contains the main function for the chess programm.
 */

#include "schachapp.h"
#include "game.h"
#include "netzwerk.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// Create the GUI instance
    SchachApp gui;

    /// Create the Netzwerk instance (pass the Game instance once it's created)
    Netzwerk netzwerk(nullptr);

    /// Create the Game instance and pass it to netzwerk
    Game Game(&gui, &netzwerk);
    netzwerk.setGame(&Game);

    /// Show the GUI
    gui.show();

    /// Start the Qt event loop
    return a.exec();
}
