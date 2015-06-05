#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "graph.hpp"
#include <QDebug>
#include <QInputDialog>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addDirection(None)
{
    ui->setupUi(this);
    this->reloadFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reloadFile()
{
    std::ifstream ifs;
    ifs.open("graph.txt", std::ios::in);

    if (ifs.is_open())
    {
        ui->paintWidget->getGraph()->loadFromStream(ifs);
        ifs.close();
    }
}

void MainWindow::resizeEvent (QResizeEvent*)
{
    ui->frame->move(ui->paintWidget->x(), this->height() - ui->frame->height() - 10);
    ui->paintWidget->resize(this->width() - 20, this->height() - ui->frame->height() - ui->paintWidget->x() - 40);
}

void MainWindow::on_pushButton_AddNode_clicked()
{
    ui->paintWidget->getGraph()->addNode(ui->lineEdit_NodeI->text().toInt());
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_DelNode_clicked()
{
    ui->paintWidget->getGraph()->delNode(ui->lineEdit_NodeI->text().toInt());
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_Visit_clicked()
{
    bool ok;

    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString startNode = inputDialog->getText(NULL, "", "Введите стартовую вершину:", QLineEdit::Normal, "0", &ok);

    if (ok)
        ui->textEdit_Log->append(ui->paintWidget->getGraph()->visit(startNode.toInt()));
}

void MainWindow::on_pushButton_Algorithm_clicked()
{
    //
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->paintWidget->getGraph()->clear();
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_AddRelation_clicked()
{
    int weight = ui->lineEdit_Weight->text().toInt();

    if (weight <= 0)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Вес должен быть положительным!", QMessageBox::Ok).exec();
        return;
    }

    ui->paintWidget->getGraph()->addRelation(ui->lineEdit_RelationI->text().toInt(), ui->lineEdit_RelationJ->text().toInt(), weight, addDirection);
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_DelRelation_clicked()
{
    ui->paintWidget->getGraph()->delRelation(ui->lineEdit_RelationI->text().toInt(), ui->lineEdit_RelationJ->text().toInt());
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_Save_clicked()
{
    std::ofstream ofs;

    ofs.open("graph.txt", std::ios::out);
    ui->paintWidget->getGraph()->saveToStream(ofs);
    ofs.close();
}

void MainWindow::on_pushButton_Reload_clicked()
{
    ui->paintWidget->getGraph()->clear();
    this->reloadFile();
    ui->paintWidget->repaint();
}

void MainWindow::on_pushButton_ChangeDirection_clicked()
{
    switch(this->addDirection)
    {
    case None:
        this->addDirection = jTo_i;
        break;
    case jTo_i:
        this->addDirection = iTo_j;
        break;
    case iTo_j:
        this->addDirection = Both;
        break;
    case Both:
        this->addDirection = None;
        break;

    }

    on_lineEdit_RelationI_editingFinished();
}

void MainWindow::on_lineEdit_RelationI_editingFinished()
{
    ui->pushButton_ChangeDirection->setText(
                QString::number(ui->lineEdit_RelationI->text().toInt()) + " " +
                getDirectionStr(this->addDirection) + " " +
                QString::number(ui->lineEdit_RelationJ->text().toInt()));
}

QString MainWindow::getDirectionStr(GraphDirection& direction)
{
    QString targetText;

    switch(direction)
    {
    case None:
        targetText = "-X-";
        break;
    case jTo_i:
        targetText = "<-";
        break;
    case iTo_j:
        targetText = "->";
        break;
    case Both:
        targetText = "<->";
        break;
    }

    return targetText;
}

void MainWindow::on_lineEdit_RelationJ_editingFinished()
{
    this->on_lineEdit_RelationI_editingFinished();
}
