#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setPoints->setShortcut(Qt::Key_P);
    ui->voronoi->setShortcut(Qt::Key_V);
    ui->inc->setShortcut(Qt::Key_Right);
    ui->dec->setShortcut(Qt::Key_Left);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setPoints_clicked()
{
    ui->label->setPoints();
}

void MainWindow::on_voronoi_clicked()
{
    ui->label->voronoi();
}

void MainWindow::on_inc_clicked()
{
    int num = ui->label->numInc();
    ui->label_2->setText(QString("num: ").append(QString::number(num)));
}

void MainWindow::on_dec_clicked()
{
    int num = ui->label->numDec();
    ui->label_2->setText(QString("num: ").append(QString::number(num)));
}
