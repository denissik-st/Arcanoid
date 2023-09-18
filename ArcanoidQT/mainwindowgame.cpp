#include "mainwindowgame.h"
#include "ui_mainwindowgame.h"
#include<QFile>
#include<QDebug>

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
    //Чтение файла для стилей
    QFile fileStyle(":/Style.css");
    fileStyle.open(QFile::ReadOnly);
    styleCSS=new QString;
    *styleCSS =fileStyle.readAll();
    fileStyle.close();
    //Заголовок
    titlelbn = new QLabel;
    titlelbn->setGeometry(QRect(-150,-300,400,200));
    titlelbn->setText("Типичный Арканойд");
    titlelbn->setObjectName("titlelbn");
    titlelbn->setStyleSheet(*styleCSS);
    scene->addWidget(titlelbn);
    //Кнопка "Играть"
    playGamebtn = new QPushButton();
    playGamebtn->setGeometry(QRect(-50,-50,200,100));
    playGamebtn->setText("Играть");
    playGamebtn->setObjectName("btn");
    playGamebtn->setStyleSheet(*styleCSS);
    scene->addWidget(playGamebtn);
    //Кнопка "Выход"
    exitGamebtn = new QPushButton;
    exitGamebtn->setGeometry(QRect(-50,100,200,100));
    exitGamebtn->setText("Выход");
    exitGamebtn->setObjectName("btn");
    exitGamebtn->setStyleSheet(*styleCSS);
    scene->addWidget(exitGamebtn);
    //Надпись "Версия"
    version = new QLabel;
    version->setGeometry(QRect(450,340,80,30));
    version->setText("Версия:1.03");
    version->setObjectName("ver");
    version->setStyleSheet(*styleCSS);
    scene->addWidget(version);

    ui->mainscene->setScene(scene);

    //Действия кнопок

    connect(exitGamebtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(playGamebtn,SIGNAL(clicked()),this,SLOT(click_playGamebtn()));



}

MainWindowGame::~MainWindowGame()
{
    delete ui;
}


void MainWindowGame::click_playGamebtn()
{
    scenePl=new scenePlayGame;
    scenePl->setSceneRect(0,0,ui->mainscene->width(),ui->mainscene->height());
    ui->mainscene->setScene(scenePl);
    //Окончание игры
    connect(scenePl,SIGNAL(endGame(int)),this,SLOT(gameEnd(int)));
}

void MainWindowGame::gameEnd(int resultGame)
{
    QLabel *titleEndGame = new QLabel;
    titleEndGame->setText("Ваш счет: "+QString::number(resultGame));
    titleEndGame->setGeometry(QRect(996/2-200,730/2-130,400,100));
    titleEndGame->setAlignment(Qt::AlignCenter);
    titleEndGame->setObjectName("titleEndlbn");
    titleEndGame->setStyleSheet(*styleCSS);
    titleEndGame->raise();
    scenePl->addWidget(titleEndGame);
    againbtn = new QPushButton;
    againbtn->setText("Ещё раз?");
    againbtn->setGeometry(300,360,200,100);
    againbtn->setObjectName("btn");
    againbtn->setStyleSheet(*styleCSS);
    againbtn->raise();
    scenePl->addWidget(againbtn);
    //Кнопка "Выход"
    exitGamebtn = new QPushButton;
    exitGamebtn->setGeometry(QRect(550,360,200,100));
    exitGamebtn->setText("Выход");
    exitGamebtn->setObjectName("btn");
    exitGamebtn->setStyleSheet(*styleCSS);
    scenePl->addWidget(exitGamebtn);
    //Действия кнопок при окончании игры
    connect(exitGamebtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(againbtn,SIGNAL(clicked()),this,SLOT(click_playGamebtn()));

}





