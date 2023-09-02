#include "mainwindowgame.h"
#include "ui_mainwindowgame.h"
#include<QtDebug>



MainWindowGame::MainWindowGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowGame)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->setStyleSheet("background-color: black");
    this->setWindowTitle("Арканоид");
    scene =new SceneStarfall();
    scene->setSceneRect(0,0,ui->mainscene->width(),ui->mainscene->height());
    playGamebtn = new QPushButton();
    playGamebtn->setGeometry(QRect(-50,-50,200,100));
    playGamebtn->setText("Играть");
    scene->addWidget(playGamebtn);
    ui->mainscene->setScene(scene);

}

MainWindowGame::~MainWindowGame()
{
    delete ui;
}



