#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "graph.hpp"
#include <QDebug>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->paintWidget->gp = new Graph();

    std::ifstream ifs;
    ifs.open("graph.txt", std::ios::in);

    if (ifs.is_open())
    {
        ui->paintWidget->gp->loadFromStream(ifs);
        ifs.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui->paintWidget->gp;
    delete ui;
}

void MainWindow::resizeEvent (QResizeEvent*)
{
    ui->paintWidget->resize(this->width() - 20, this->height() - 100);
    ui->frame->move(ui->paintWidget->x(), ui->paintWidget->y() + ui->paintWidget->height() + 10);
}

void MainWindow::on_pushButton_Add_clicked()
{
    ui->paintWidget->gp->addRelation(ui->lineEditA->text().toInt(), ui->lineEditB->text().toInt(), 1);
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_Del_clicked()
{
    ui->paintWidget->gp->delRelation(ui->lineEditA->text().toInt(), ui->lineEditB->text().toInt());
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_Save_clicked()
{
    std::ofstream ofs;

    ofs.open("graph.txt", std::ios::out);
    ui->paintWidget->gp->saveToStream(ofs);
    ofs.close();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->paintWidget->gp->clear();
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_Add_2_clicked()
{
    ui->paintWidget->gp->addNode(ui->lineEditNode->text().toInt());
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_DelNode_clicked()
{
    ui->paintWidget->gp->delNode(ui->lineEditNode->text().toInt());
    ui->paintWidget->repaint();
}
