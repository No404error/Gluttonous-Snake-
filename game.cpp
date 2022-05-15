#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include"constants.h"
#include "game.h"
#include "food.h"
#include "snake.h"
#include"text.h"

Game::Game(QGraphicsScene &scene,QObject *parent) :
    QObject(parent),
    diffculty(init_diffculty>DiffcultyTop?1:init_diffculty),
    scene(scene),
    snake(new Snake(*this))
{
    score=0;
    //计时器，游戏驱动
    timer.start( 1000/Ehz );

    //创建场景
    addNewFood();
    addText();
    scene.addItem(snake);
    scene.installEventFilter(this);

    ResumeGame();
}

Game::~Game()
{
}

void Game::snakeAteFood(Snake *snake, Food *food)
{
    score+=food->Score();
    ScoreChange();

    scene.removeItem(food);
    delete food;
    addNewFood();
}

void Game::snakeHitWall(Snake *snake, Wall *wall)
{
}

void Game::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void Game::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        snake->setMoveDirection(Left);
        break;
    case Qt::Key_Right:
        snake->setMoveDirection(Right);
        break;
    case Qt::Key_Up:
        snake->setMoveDirection(Up);
        break;
    case Qt::Key_Down:
        snake->setMoveDirection(Down);
        break;
    case Qt::Key_Space:
        ChangeGameState();
        break;
    }
}

void Game::GameStateChange()
{
    resetText();
}

void Game::ScoreChange()
{
    resetText();
}

void Game::addText()
{
    text=new Text(Textpos,run,score,diffculty);
    scene.addItem(text);
}

void Game::resetText()
{
    scene.removeItem(text);
    addText();
}

void Game::ChangeGameState()
{
    if(run)
        StopGame();
    else
        ResumeGame();
}

void Game::StopGame()
{
    run=false;
    disconnect(&timer, SIGNAL(timeout()),&scene, SLOT(advance()));
    GameStateChange();
}

void Game::ResumeGame()
{
    run=true;
    connect(&timer, SIGNAL(timeout()),&scene, SLOT(advance()));
    GameStateChange();
}

void Game::SetDiffculty(int dif)
{
    diffculty=dif;
    snake->setSpeed(diffculty);
}

int Game::Diffculty()
{
    return diffculty;
}
void Game::addNewFood()
{
    addNewFood(1);
}
void Game::addNewFood(int size)
{
    //保存snake的形状
    auto path=snake->shape();
    int x, y;
    bool flag=true;

    do {
        //得到x,y的值
        x = (int(qrand() % (int)Viewer.width())-Viewer.bottomRight().x())/tile;
        y = (int(qrand() % (int)Viewer.height())-Viewer.bottomRight().y())/tile;
        x *= 10;
        y *= 10;
        //判断冲突
        flag=x+tile*size>=Viewer.bottomRight().x()||y+tile*size>=Viewer.bottomRight().y();
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                flag=flag||path.contains(snake->mapFromScene(QPointF(x+tile*i+5,y+tile*j+5)));
    } while (flag);

    Food *food = new Food(x , y,diffculty_value[diffculty-1],size);
    scene.addItem(food);
}

void Game::gameOver()
{
    score=0;
    StopGame();
    //断开键盘连接
    scene.removeEventFilter(this);

    QTimer::singleShot(GameOverTime,this,[this](){
        //恢复场景
        scene.clear();
        snake = new Snake(*this);
        scene.addItem(snake);
        addNewFood();
        addText();

        //恢复游戏状态
        ResumeGame();
        //重连键盘输入
        scene.installEventFilter(this);
    });

}

bool Game::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}

