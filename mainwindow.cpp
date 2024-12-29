#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include<bits/stdc++.h>
using namespace std;
#define gridSize 20

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), direction(0, -1), isPaused(false)
{
    ui->setupUi(this);

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Initialize the timer for snake movement
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSnake);
    ui->start->setFocusPolicy(Qt::NoFocus);
    ui->pandr->setFocusPolicy(Qt::NoFocus);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_clicked()
{
    qDebug()<<"start";
    startGame();
}

void MainWindow::startGame() {
    snakeBody.clear();
    obstacles.clear();
    speed = 200;
    snakeBody.push_back(QPoint(7, 7));  // Start snake body
    snakeBody.push_back(QPoint(7, 8));
    snakeBody.push_back(QPoint(7, 9));
    direction = QPoint(0, -1);  // Initial direction: moving up
    score = 0;
    ui->score->display(score*10);
    gameRunning = true;

    // Place the first food
    placeFood();

    // Start the game timer
    timer->start(speed);  // Snake moves every 200ms
}

void MainWindow::togglePause() {
    if (gameRunning) {
        if (isPaused) {
            // Resume the game
            timer->start(speed);
            ui->pandr->setText("Pause");
        } else {
            // Pause the game
            timer->stop();
            ui->pandr->setText("Resume");
        }
        isPaused = !isPaused;
    }
    ui->workArea->setFocus();
}

void MainWindow::on_pandr_clicked()
{
    togglePause();
}

void MainWindow::placeFood() {
    int maxWidth = ui->workArea->width() / gridOffset;
    int maxHeight = ui->workArea->height() / gridOffset;
    maxWidth -= 5;
    maxHeight -= 5;

    // Random position within the grid
    int x = rand() % maxWidth;
    int y = rand() % maxHeight;
    if(x<5){
        x += 5;
    }if(y<5){
        y += 5;
    }
    food = QPoint(x, y);
    for(int i =0; i<obstacles.size();i++){ // if bomb and food are placed at same point then change the food position
        if(food == obstacles[i]){
            placeFood();
        }
    }
}

void MainWindow::placeObstacles() {
    int maxWidth = ui->workArea->width() / gridOffset;
    int maxHeight = ui->workArea->height() / gridOffset;
    maxWidth -= 5;
    maxHeight -= 5;
    // Random position within the grid
    int obstaclesCount = rand() % 5;
    for(int i =0; i<obstaclesCount; i++){
        int x = rand() % maxWidth;
        int y = rand() % maxHeight;
        if(x<5){
            x+= 5;
        }if(y<5){
            y+=5;
        }
        obstacles.push_back(QPoint(x,y));
    }
    if(obstacles.size()>3){
        for(int i =0; i<2; i++){
            obstacles.pop_front();
        }
    }

}

void MainWindow::updateSnake() {
    if (!gameRunning) return;

    // Move the snake's head in the current direction
    QPoint newHead = snakeBody.front() + direction;
    snakeBody.push_front(newHead);

    // Check if snake ate the food
    if (newHead == food) {
        increaseScore();
        placeObstacles();
        placeFood();
    } else {
        snakeBody.pop_back();  // Remove the tail if no food is eaten
    }

    checkCollision();

    // increase speed upto certain limit
    if(speedinc == true){
        if(speed > 100)speed -=25;
        qDebug()<<speed;
        speedinc = false;
        timer->start(speed);
    }

    // Trigger a repaint to update the UI
    update();
}



void MainWindow::checkCollision() {
    int maxWidth = ui->workArea->width() / gridOffset;
    int maxHeight = ui->workArea->height() / gridOffset;

    QPoint &head = snakeBody.front();

    if (head.x() == 1 && head.y() == 2) {
        head.setX(maxWidth - 3); // Teleport from left to right
        head.setY(maxHeight -2);
    } else if (head.x() == maxWidth-2 && head.y() == maxHeight - 2) {
        head.setX(2); // Teleport from right to left
        head.setY(2);
    }

    // Check for collision with itself
    for (int i = 1; i < snakeBody.size(); ++i) {
        if (snakeBody[i] == head) {
            gameOver();
        }
    }

    //Check collision with obstacles
    for (int i = 0; i < obstacles.size(); ++i) {
        if (head == obstacles[i]) {
            gameOver();
        }
    }

    // Check for collision with walls
    if (head.x() < 0 || head.x() >= maxWidth || head.y() < 0 || head.y() >= maxHeight) {
        gameOver();
    }
}

void MainWindow::gameOver() {

    gameRunning = false;
    timer->stop();

    // Create a message box with custom buttons
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Snake 'n' Snack" );
    msgBox.setText("!!GAME OVER!!");
    QPushButton *newGameButton = msgBox.addButton("New Game", QMessageBox::AcceptRole);
    QPushButton *quitButton = msgBox.addButton("Quit", QMessageBox::RejectRole);
    msgBox.exec(); // Display the message box

    if (msgBox.clickedButton() == newGameButton) {
        startGame();
    } else if (msgBox.clickedButton() == quitButton) {
        close();
    }
}

void MainWindow::increaseScore() {
    score++;
    if(score%2 == 0){
        speedinc = true;
    }
    ui->score->display(score*10);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPixmap pixmap(ui->workArea->size());
    //pixmap.fill(Qt::white);  // Fill the background with white

    QPainter painter(&pixmap);

    int width = pixmap.width();
    int height = pixmap.height();

    //Set pen for grid lines
    QPen gridPen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(gridPen);

    // Draw vertical grid lines
    // for (int x = 0; x < width; x += gridSize) {
    //     painter.drawLine(x, 0, x, height);
    // }

    // // Draw horizontal grid lines
    // for (int y = 0; y < height; y += gridSize) {
    //     painter.drawLine(0, y, width, y);
    // }

    // Create a linear gradient for the background
    QLinearGradient gradient(0, 0, 0, height);
    gradient.setColorAt(0, QColor(220, 250, 100));
    gradient.setColorAt(1, QColor(131, 255, 25));

    painter.fillRect(ui->workArea->rect(), gradient);


    //Left cave
    QPixmap LeftCornercave("leftcave.png");
    QRect LeftcaveRect(0, 0, gridSize*4, gridSize*4);
    painter.drawPixmap(LeftcaveRect, LeftCornercave.scaled(gridSize*4, gridSize*4));

    //Right cave
    QPixmap RightCornercave("rightcave.png");
    QRect RightcaveRect(460, 420, gridSize*4, gridSize*4);
    painter.drawPixmap(RightcaveRect, RightCornercave.scaled(gridSize*4, gridSize*4));

    QPixmap appleImage("apple.png");
    if (appleImage.isNull()) {
        qDebug() << "Error: Image could not be loaded!";
    }

    QPixmap bombImage("bomb.png");
    if (bombImage.isNull()) {
        qDebug() << "Error: Image could not be loaded!";
    }

    // Draw the snake
    for (int i = 0; i < snakeBody.size(); ++i) {
        const QPoint &segment = snakeBody[i];

        if(i== 0){
            painter.setBrush(QColor(0, 0, 100));
        }
        else if (i%2 == 0 && i>0) {
            // painter.setBrush(QColor(255, 202, 0));
            painter.setBrush(QColor(2, 2, 255));
        }else {
            //painter.setBrush(QColor(255, 53, 153));
            painter.setBrush(QColor(102, 153, 255));
        }
        painter.drawEllipse(segment.x() * gridSize, segment.y() * gridSize, gridSize, gridSize);

    }


    // Draw the food, also aligned to the grid
    QRect appleRect(food.x() * gridSize, food.y() * gridSize, gridSize, gridSize);

    painter.drawPixmap(appleRect, appleImage.scaled(gridSize, gridSize));

    // Draw the obstacle, also aligned to the grid
    for(int i=0; i<obstacles.size();i++){
        QRect rockRect(obstacles[i].x() * gridSize, obstacles[i].y() * gridSize, gridSize, gridSize);

        painter.drawPixmap(rockRect, bombImage.scaled( gridSize, gridSize));
    }

    ui->workArea->setPixmap(pixmap);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!gameRunning) return;

    switch (event->key()) {
    case Qt::Key_Up:
        if (direction != QPoint(0, 1)) direction = QPoint(0, -1);
        break;
    case Qt::Key_Down:
        if (direction != QPoint(0, -1)) direction = QPoint(0, 1);
        break;
    case Qt::Key_Left:
        if (direction != QPoint(1, 0)) direction = QPoint(-1, 0);
        break;
    case Qt::Key_Right:
        if (direction != QPoint(-1, 0)) direction = QPoint(1, 0);
        break;
    case Qt::Key_Space:
        togglePause();
        break;
    }
}

