#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cassert>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>


Model ml;
Control con;

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
    setWindowTitle(tr("Snake Game"));  // 不能调用parent 不然会奔溃

//    QWidget* p = new QWidget();
//    p->setWindowTitle("windows");
//    p->setWindowFlag(Qt::Window);  // 实现嵌套
//    p->show();
    //(6) your code. set window size by the col number and row number in Snake object.
    //every pixmap size is the same : width * height = m_pictureSize * m_pictureSize
    //use setFixedSize()

//    QPixmap pixmap_head;
//    QPixmap pixmap_body;
//    QPixmap pixmap_food;
//    QPixmap pixmap_grass;
//    bool load_snake_head_result = pixmap_head.load(":/snake_head.jpeg");
//    bool load_snake_body_result = pixmap_body.load(":/snake_body.png");
//    bool load_food_result = pixmap_food.load(":/food.png");
//    bool load_grass_result = pixmap_grass.load(":/grass.png");
//    assert(load_snake_body_result);
//    assert(load_snake_head_result);
//    assert(load_food_result);
//    assert(load_grass_result);

//    pixmap_food.size(pixmap_food.width(), pixmap_food.height());
//    pixmap_head.setFixedSize();
//    pixmap_gras
//    painter(this);
//    std::ifstream fin("data.txt");
//    con.LoadPlayDataFromFile(fin);
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
         con.GoAhead('w');
            //(3) your code. the player enter a key
            //, you have to update the game by call member function Play in Snake.
            update();//this will tell Qt to call paintEvent.
            break;
        }
        case Qt::Key_Down :
        {
            //(3) your code.
            con.GoAhead('s');
            update();
            break;
        }
        case Qt::Key_Left :
        {
            //(3) your code.
            con.GoAhead('a');
            update();
            break;
        }
        case Qt::Key_Right :
        {
            //(3) your code.
            con.GoAhead('d');
            update();
            break;
        }
    }
    if(gameover) {
        //(2) your code. use QMessageBox to tell the pla yer the game is over.
        // https://zhuanlan.zhihu.com/p/671461612
            QMessageBox messageBox;
            messageBox.setWindowTitle(tr("Notepad"));
            messageBox.setText(tr("Do you really want to quit?"));
            messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            messageBox.setDefaultButton(QMessageBox::No);
            if (messageBox.exec() == QMessageBox::Yes) qApp->quit();
    }
}


void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    std::ifstream fin("data.txt");
    con.LoadPlayDataFromFile(fin);
    for(int i = 0; i <= width(); i += width() / con.GetCol()) {
        painter.drawLine(i, 0, i, height());  // 从左上角到右下角绘制一条线
    }
    for(int j = 0; j <= height(); j += height() / con.GetRow()) {
        painter.drawLine(0, j, width(), j);
    }
}
