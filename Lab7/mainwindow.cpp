#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "graph.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    Graph *tt = new Graph();

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            tt->setRelation(i, j, 1);
    }

    ui->paintWidget->gp = tt;
    //
}

MainWindow::~MainWindow()
{
    delete ui->paintWidget->gp;
    delete ui;
}

void MainWindow::resizeEvent (QResizeEvent*)
{
    ui->paintWidget->resize(this->width() - 20, this->height() - 40);
}
