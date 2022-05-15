#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;
class Text;

class Game : public QObject
{
    Q_OBJECT
public:
    Game(QGraphicsScene &scene,QObject* parent);
    ~Game();

    //游戏事件
    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);
    //游戏操作事件
    void ChangeGameState();
    void SetDiffculty(int diffculty);
    //自身属性
    int Diffculty();

public slots:
    void StopGame();
    void ResumeGame();
    void gameOver();

protected:
     bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);

    //游戏状态变动
    void GameStateChange();
    void ScoreChange();

    //游戏元素添加
    void addText();
    void resetText();
    void addNewFood();
    void addNewFood(int size);

    //属性
    bool run;
    int diffculty;
    int score;
    //元素
    QTimer timer;
    QGraphicsScene &scene;
    Snake *snake;
    Text* text;
};

#endif // GAMECONTROLLER_H
