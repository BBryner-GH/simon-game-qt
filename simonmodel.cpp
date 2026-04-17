/**
 * Authors: Brenden Bryner and Ryan Storm
 * Date:  March 4, 2026
 * Description: Simon Model implementation file
 *
 * All of the game logic for the Simon game. Holds the sequence of button presses inside of a vector and
 * tracks the game state and emits signals
 * to the view.
 */

#include "simonmodel.h"

#include <QRandomGenerator>
#include <QTimer>
#include <algorithm>

SimonModel::SimonModel(){
    // the delay should be one second (1000 ms)
    delay = 1000;
    // the beginning of the button sequence
    currentIndex = 0;
    // idle when the game is not running
    state = "idle";
}

// ----- SLOTS -----

void SimonModel::pressedStartSlot(){
    // Initialize Game Model
    buttonSequence.clear();
    currentIndex = 0;
    delay = 1000;

    // Initialize Game View
    emit gameStartSignal();

    // Run computer turn state
    computersTurn();
}

void SimonModel::pressedButtonSlot(char button){
    // Check state
    if (state != "playersTurn")
        return;

    if (currentIndex >= buttonSequence.size())
        return;

    // flash the button the player presses
    if (button == 'R'){
        emit lightRedButtonSignal();
    } else {
        emit lightBlueButtonSignal();
    }

    // Check button correctness
    if (buttonSequence.at(currentIndex) != button){
        state = "idle";
        emit playSoundSignal("false");
        emit gameEndSignal();
        return;
    }

    // play the correct sound if the player choice was right
    emit playSoundSignal("correct");
    currentIndex ++;

    // Update progress bar
    int progressPercentage = ((currentIndex * 100) / (int)buttonSequence.size()) ;
    emit progressUpdatedSignal(progressPercentage);

    // Check end of sequence
    if (currentIndex == buttonSequence.size()){
        QTimer::singleShot(delay, this, [this](){ computersTurn(); });
    }

}


void SimonModel::playSequence(){
    // Loop through vector and emit each button in order
    int index = 0;

    // make the delay smaller as the button sequence grows. it should have a minimum of 250ms
    delay = std::max(250, delay - (int)buttonSequence.size() * 30);

    //go through the button sequence and flash the buttons in order for the player
    for (char c : buttonSequence){
        QTimer::singleShot(index*delay, this, [this, c]{
            if (c == 'B')
                emit lightBlueButtonSignal();
            else if (c == 'R')
                emit lightRedButtonSignal();

            emit playSoundSignal("computerSound");
        });
        index++;
    }
}


void SimonModel::addMove(){
    // Add one of the buttons to the vector at random (bounded at two so it should only return 0 or 1)
    int randomNum = QRandomGenerator::global()->bounded(2);

    if (randomNum == 0){
        buttonSequence.push_back('B');
    } else if (randomNum == 1){
        buttonSequence.push_back('R');
    }

}

void SimonModel::computersTurn(){
    // lock the inputs while the computer is playing, make the progress bar dissappear
    state = "computersTurn";
    emit progressUpdatedSignal(-1);

    // add a move to the button sequence
    addMove();
    playSequence();

    // Switch to player's turn after sequence is done
    int playerTurnDelay = (int)buttonSequence.size() * delay + 200;
    QTimer::singleShot(playerTurnDelay, this, [this](){
        emit progressUpdatedSignal(0);
        currentIndex = 0;
        state = "playersTurn";
    });
}



