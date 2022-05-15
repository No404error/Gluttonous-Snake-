#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;

class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();

private:
    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;

    Game *game;
};

#endif // MAINWINDOW_H
