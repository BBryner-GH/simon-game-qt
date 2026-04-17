/**
 * Authors: Brenden Bryner and Ryan Storm
 * Date:  March 4, 2026
 * Description: Simon Model header class
 *
 * All of the game logic for the Simon game. Holds the sequence of button presses inside of a vector and tracks the game state and emits signals
 * to the view.
 */

#ifndef SIMONMODEL_H
#define SIMONMODEL_H

// Includes

#include <QObject>

/**
 * @brief The SimonModel class that manages all Simon game logic and states
 *
 * Should communicate with the view with signals and slots
 */
class SimonModel : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief SimonModel constructs the model and initializes all of the game state to the defaults
     */
    SimonModel();

public slots:

    /**
     * @brief pressedStartSlot - The slot used when the player selects the start button
     *
     * Clears the vector that is holding all of the previous computer moves and
     * emits the signals that starts the game and the computer.
     */
    void pressedStartSlot();

    /**
     * @brief pressedButtonSlot - called when the player presses one of the colored buttons
     * @param button - The button that the player presses, should be 'R' for red and 'B' for blue
     *
     * Makes sure whether the player pressed the right button or not, should emit a light and sound.
     * If the player pressed the right button then the progress bar will advance and the game will keep going.
     */
    void pressedButtonSlot(char button);

signals:

    /**
     * @brief lightRedButtonSignal - tells the view to light up the red button
     */
    void lightRedButtonSignal();

    /**
     * @brief lightBlueButtonSignal - tells the view to light up the blue button
     */
    void lightBlueButtonSignal();

    /**
     * @brief progressUpdatedSignal - tells the view to update the progress bar
     * @param percentage - the percentage to update the bar with (is -1 to hide the bar)
     */
    void progressUpdatedSignal(int percentage);

    /**
     * @brief gameEndSignal - emitted when the playe presses the wrong button and the game needs to end
     *
     * The view should show a game over message and also re enable the start button so the player can play again
     */
    void gameEndSignal();

    /**
     * @brief gameStartSignal - emitted at the beginning of a new game
     */
    void gameStartSignal();

    /**
     * @brief playSoundSignal - tells the view to play a sound effect
     * @param sound the type of sound that should play "correct" for the correct noice, "false" for the wrong press, and
     * any other value for the computer noise
     */
    void playSoundSignal(QString sound);

private:

    //private instance variables
    QVector<char> buttonSequence;
    int currentIndex;
    QString state;
    int delay;

    /**
     * @brief playSequence - plays the buttonSequence for the player
     */
    void playSequence();

    /**
     * @brief computersTurn - adds one new move then plays the full sequence
     *
     * should set the state to "computerTurn", which will hide the progress bar and not let the player click the buttons
     */
    void computersTurn();

    /**
     * @brief addMove - appends a random move 'R' or 'B' to the button sequence vector
     */
    void addMove();

};

#endif // SIMONMODEL_H
