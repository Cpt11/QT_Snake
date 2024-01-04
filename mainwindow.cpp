#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cassert>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    bool  load_result = false;
    //(4) your code. load data from data.txt file by Snake's member function LoadPlayDataFromFile
    if(m_snake.LoadPlayDataFromFile("data.txt")) {
        load_result = true;
    }
    assert(load_result);
    //(5) your code.  set window title with "Snake Game"
    //https://zhuanlan.zhihu.com/p/669799427
    setWindowTitle(tr("Snake Game"));

    //(6) your code. set window size by the col number and row number in Snake object.
    //every pixmap size is the same : width * height = m_pictureSize * m_pictureSize
    //use setFixedSize()
    setFixedSize(m_pictureSize * m_snake.GetCol(),m_pictureSize * m_snake.GetRow());

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug()<<"user pressed key "<<event->key();
    bool gameover = false;
    switch (event->key()) {
        case Qt::Key_Up :
        {
            if(m_snake.Play('w') ) {
                gameover = true;
            }
            update();
            break;
        }
        case Qt::Key_Down :
        {
            if(m_snake.Play('s') ) {
                gameover = true;
            }
            update();
            break;
        }
        case Qt::Key_Left :
        {
            if(m_snake.Play('a') ) {
                gameover = true;
            }
            update();
            break;
        }
        case Qt::Key_Right :
        {
            if(m_snake.Play('d') ) {
                gameover = true;
            }
            update();
            break;
        }
    }
    if(gameover) {
//        (2) your code. use QMessageBox to tell the pla yer the game is over.
//         https://zhuanlan.zhihu.com/p/671461612
            QMessageBox messageBox;
            messageBox.setWindowTitle(tr("Game Over"));
            messageBox.setText(tr("Do you really want to quit?"));
            messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            messageBox.setDefaultButton(QMessageBox::No);
            if (messageBox.exec() == QMessageBox::Yes) qApp->quit();
    }
}


void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 感觉并不需要划线
    for(int i = 0; i <= width(); i += m_pictureSize) {
        painter.drawLine(i, 0, i, height());
    }
    for(int j = 0; j <= height(); j += m_pictureSize) {
        painter.drawLine(0, j, width(), j);
    }
    m_snake.PrintMatrix(painter, m_pictureSize);
}
