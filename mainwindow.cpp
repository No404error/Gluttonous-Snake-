#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "Game.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new Game(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);

    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(tile, tile);
    QPainter p(&bg);
    QColor color=Qt::gray;
    p.setBrush(QBrush(color.lighter(125)));
    p.drawRect(0, 0, tile, tile);

    view->setBackgroundBrush(QBrush(bg));
}
