#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cassert>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QtWidgets>
Snake sn;
Control con;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool  load_result = false;

    //(4) your code. load data from data.txt file by Snake's member function LoadPlayDataFromFile
    if(sn.LoadPlayDataFromFile("C:\\Users\\27285\\Desktop\\learn-qt-with-code\\QSnake\\data.txt")) {
        load_result = true;
    }
    assert(load_result);
    //(5) your code.  set window title with "Snake Game"
    //https://zhuanlan.zhihu.com/p/669799427



    //(6) your code. set window size by the col number and row number in Snake object.
    //every pixmap size is the same : width * height = m_pictureSize * m_pictureSize
    //use setFixedSize()
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
//            QTextEdit *textEdit;
//            textEdit = new QTextEdit;
//            quitButton = new QPushButton(tr("Quit"));
//            connect(quitButton, SIGNAL(clicked()), this, SL   OT(quit()));
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    std::ifstream fin("data.txt");
    con.LoadPlayDataFromFile(fin);
//    qDebug() << con.() << " " << con.GetRow();
    for(int i = 0; i <= width(); i += width() / con.GetCol()) {
        painter.drawLine(i, 0, i, height());  // 从左上角到右下角绘制一条线
    }
    for(int j = 0; j <= height(); j += height() / con.GetRow()) {
        painter.drawLine(0, j, width(), j);
    }
}
