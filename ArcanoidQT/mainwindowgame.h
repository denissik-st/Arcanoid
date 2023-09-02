#ifndef MAINWINDOWGAME_H
#define MAINWINDOWGAME_H

#include <QMainWindow>
#include <QTimer>
#include "scenestarfall.h"

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
    QTimer *starfallTimer;


private:
    Ui::MainWindowGame *ui;
private slots:
    void updatestarfall();
};
#endif // MAINWINDOWGAME_H
