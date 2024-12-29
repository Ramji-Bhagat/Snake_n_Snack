#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <deque>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pandr_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    int gridOffset = 20;       // Size of one grid square
    int speed = 200;
    int score = 0;             // Score of the game
    bool speedinc = false;
    QPoint food = QPoint(-1,-1);               // Food position
    std::deque<QPoint> obstacles;
    std::deque<QPoint> snakeBody;  // To store snake segments as points
    QPoint direction;          // Current direction of the snake
    bool gameRunning;          // Game state (running or not)


    // Game logic functions
    void startGame();          // Start or restart the game
    void togglePause();
    void gameOver();           // Handle game over
    void placeFood();          // Place food at random position
    void placeObstacles();
    void updateSnake();        // Update snake's position
    void checkCollision();     // Check for collisions
    void increaseScore();      // Update score after eating food
    bool isPaused;



};

#endif // MAINWINDOW_H
