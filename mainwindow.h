/**
 * Authors: Brenden Bryner and Ryan Storm
 * Date:  March 4, 2026
 * Description: MainWindow header file
 *
 * The view class for the Simon game. It should handle all of the UI rendering and how the user interfaces with the game.
 * Communicates with the model for the simon game through QT signals and slots.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// includes
#include "simonmodel.h"

#include <QMainWindow>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class shouuld be the view of the Simon game
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow - constructs the view and sets up the UI as well as the sound effects of the simon game
     * @param model - The pointer to the simon model
     * @param parent - Qt parent widget
     */
    MainWindow(SimonModel* model, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~MainWindow();

private slots:
    /**
     * @brief lightBlue - light up the blue button then restores it to the normal color
     */
    void lightBlue();

    /**
     * @brief lightRed - lights up the red button then restores it to the normal color
     */
    void lightRed();

    /**
     * @brief gameStart - resets the view for the beginnning of the game
     */
    void gameStart();

    /**
     * @brief gameEnd - shows the game overscreen when the player loses
     *
     * should hide the color buttons and show the game over label, also re-enables the start button
     */
    void gameEnd();

    /**
     * @brief progressUpdated - updates the progress bar
     * @param percentage - percentage to set the progress bar to
     */
    void progressUpdated(int percentage);

    /**
     * @brief playSound - plays a sound effect based on the string that was given
     * @param sound the sound effect that should be played
     */
    void playSound(QString sound);

private:
    // private instance variables
    Ui::MainWindow *ui;
    SimonModel* model;
    QSoundEffect* correctSound;
    QSoundEffect* errorSound;
    QSoundEffect* computerSound;

};
#endif // MAINWINDOW_H
