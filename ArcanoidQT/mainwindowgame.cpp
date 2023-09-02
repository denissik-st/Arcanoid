#include "mainwindowgame.h"
#include "ui_mainwindowgame.h"
#include<QtDebug>


MainWindowGame::MainWindowGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowGame)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black");
    this->setWindowTitle("Арканоид");
    scene =new SceneStarfall();
    ui->mainscene->setScene(scene);




}

MainWindowGame::~MainWindowGame()
{
    delete ui;
}

void MainWindowGame::updatestarfall()
{

}

