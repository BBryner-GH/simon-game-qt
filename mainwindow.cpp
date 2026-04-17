/**
 * Authors: Brenden Bryner and Ryan Storm
 * Date:  March 4, 2026
 * Description: Main window implementation file
 *
 * It should handle all of the UI rendering and how the user interfaces with the game.
 * Communicates with the model for the simon game through QT signals and slots.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simonmodel.h"

#include <QTimer>


MainWindow::MainWindow(SimonModel* model,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(model)
{
    ui->setupUi(this);

    ui->label->setVisible(false);

    // SLOTS CONNECTIONS -----

    connect(ui->blueButton, &QPushButton::clicked, model, [model](){model->pressedButtonSlot('B');});

    connect(ui->redButton, &QPushButton::clicked, model, [model](){model->pressedButtonSlot('R');});

    connect(ui->startButton, &QPushButton::clicked, model, &SimonModel::pressedStartSlot);

    // SIGNAL CONNECTIONS -----

    connect(model, &SimonModel::lightBlueButtonSignal, this, &MainWindow::lightBlue);

    connect(model, &SimonModel::lightRedButtonSignal, this, &MainWindow::lightRed);

    connect(model, &SimonModel::gameEndSignal, this, &MainWindow::gameEnd);

    connect(model, &SimonModel::progressUpdatedSignal, this, &MainWindow::progressUpdated);

    connect(model, &SimonModel::gameStartSignal, this, &MainWindow::gameStart);

    connect(model, &SimonModel::playSoundSignal, this, &MainWindow::playSound);

    // SOUND EFFECTS -----

    // sound when the player hits the right buttons
    correctSound = new QSoundEffect(this);
    correctSound->setSource(QUrl("qrc:/sounds/CorrectSound.wav"));
    correctSound->setVolume(0.8f);

    // sound when the player hit the wrong buttons
    errorSound = new QSoundEffect(this);
    errorSound->setSource(QUrl("qrc:/sounds/ErrorSound.wav"));
    errorSound->setVolume(0.8f);

    // sound during the computer choices
    computerSound = new QSoundEffect(this);
    computerSound->setSource(QUrl("qrc:/sounds/computerClick.wav"));
    computerSound->setVolume(0.8f);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::gameStart(){
    // Initialize Game
    ui->startButton->setVisible(false);
    ui->progressBar->setValue(0);
    ui->label->setVisible(false);
    ui->redButton->setVisible(true);
    ui->blueButton->setVisible(true);
}

void MainWindow::lightBlue(){
    // light up the button colors
    ui->blueButton->setStyleSheet("background-color: white");

    // set button colors back to original value
    QTimer::singleShot(200, this, [this]{
        ui->blueButton->setStyleSheet("background-color: blue");
    });
}

void MainWindow::lightRed(){
    // light up the button colors
    ui->redButton->setStyleSheet("background-color: white");

    // set button colors back to original value
    QTimer::singleShot(200, this, [this]{
        ui->redButton->setStyleSheet("background-color: red");
    });
}

void MainWindow::gameEnd(){
    // set color buttons invisible
    ui->redButton->setVisible(false);
    ui->blueButton->setVisible(false);
    // show the game over label
    ui->label->setVisible(true);
    // restore the start button
    ui->startButton->setVisible(true);
}

void MainWindow::progressUpdated(int percentage){
    // hide the bar during the computers turn
    if (percentage == -1)
        ui->progressBar->setVisible(false);
    else {
        // show the bar and update it to the percentage
        ui->progressBar->setVisible(true);
        ui->progressBar->setValue(percentage);
    }
}

void MainWindow::playSound(QString sound){
    // playing the correct sound when the player picks the right choice
    if (sound == "correct"){
        correctSound->play();
    // playing the error noise when the player loses
    } else if (sound == "false") {
        errorSound->play();
    // plays a noise when the computer hits a button during the sequence
    } else {
        computerSound->play();
    }
}
