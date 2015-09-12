#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->down->setShortcut(Qt::Key_Down);
    ui->points->setShortcut(Qt::Key_P);
    ui->up->setShortcut(Qt::Key_Up);
    ui->pushButton->setShortcut(Qt::Key_Right);
    ui->pushButton_2->setShortcut(Qt::Key_Left);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_points_clicked()
{
    ui->label->setPoints();
}

void MainWindow::on_down_clicked()
{
    ui->label->down();
}

void MainWindow::on_up_clicked()
{
    ui->label->up();
}

void MainWindow::on_pushButton_clicked()
{
    int step = ui->label->stepMore();
    ui->label_2->setText(QString("step: ").append(QString::number(step)));
}

void MainWindow::on_pushButton_2_clicked()
{
    int step = ui->label->stepLess();
    ui->label_2->setText(QString("step: ").append(QString::number(step)));
}
