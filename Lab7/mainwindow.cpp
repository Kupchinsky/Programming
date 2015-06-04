#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "graph.hpp"
#include <QDebug>
#include <QInputDialog>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->paintWidget->gp = new Graph();
    this->on_pushButton_Reload_clicked();
}

MainWindow::~MainWindow()
{
    delete ui->paintWidget->gp;
    delete ui;
}

void MainWindow::resizeEvent (QResizeEvent*)
{
    ui->frame->move(ui->paintWidget->x(), this->height() - ui->frame->height() - 10);
    ui->paintWidget->resize(this->width() - 20, this->height() - ui->frame->height() - ui->paintWidget->x() - 40);
}

void MainWindow::on_pushButton_Add_clicked()
{
    int weight = ui->lineEditWeight->text().toInt();

    if (weight <= 0)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Вес должен быть положительным!", QMessageBox::Ok).exec();
        return;
    }

    ui->paintWidget->gp->addRelation(ui->lineEditA->text().toInt(), ui->lineEditB->text().toInt(), weight);
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

void MainWindow::on_pushButton_Clear_clicked()
{
}

void MainWindow::on_pushButton_Reload_clicked()
{
    ui->paintWidget->gp->clear();

    std::ifstream ifs;
    ifs.open("graph.txt", std::ios::in);

    if (ifs.is_open())
    {
        ui->paintWidget->gp->loadFromStream(ifs);
        ifs.close();
    }

    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_clicked()
{
    // Visiting
    bool ok;

    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString startNode = inputDialog->getText(NULL, "", "Введите стартовую вершину:", QLineEdit::Normal, "0", &ok);

    if (!ok)
        return;

    ui->log->append(ui->paintWidget->gp->visit(startNode.toInt()));
}
