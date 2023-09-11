#ifndef MAINWINDOWGAME_H
#define MAINWINDOWGAME_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include "scenestarfall.h"
#include "sceneplaygame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowGame; }
QT_END_NAMESPACE

class MainWindowGame : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowGame(QWidget *parent = nullptr);
    ~MainWindowGame();
    SceneStarfall *scene;
    QLabel *titlelbn;
    QString *styleCSS;
    scenePlayGame *scenePl;
    QPushButton *playGamebtn;
    QPushButton *exitGamebtn;
    QLabel *version;
    QPushButton *againbtn;
public slots:
    void click_playGamebtn();
    void gameEnd(int resultGame);
private:
    Ui::MainWindowGame *ui;

};
#endif // MAINWINDOWGAME_H
