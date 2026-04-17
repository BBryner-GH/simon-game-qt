/**
 * Authors: Brenden Bryner and Ryan Storm
 * GITHUB USERNAMES: Ryan-Storm , BBryner-GH
 * GITHUB URL FOR REPOSITORY: https://github.com/UofU-CS3505/cs3505-assignment6-BBryner-GH.git
 * Date:  March 4, 2026
 * Description: Main file that runs the main window
 * Creative Element:
 *
 * The creative element that was added was multimedia.  There are now different sounds for correct and incorrect button presses, sounds for the button sequence
 * flashes as well.
 */

#include "mainwindow.h"
#include "simonmodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel model;
    MainWindow w(&model);
    w.show();
    return a.exec();

}
