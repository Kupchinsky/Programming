#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include "graph.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent (QResizeEvent*);

private slots:

    void on_pushButton_AddNode_clicked();

    void on_pushButton_DelNode_clicked();

    void on_pushButton_Visit_clicked();

    void on_pushButton_Algorithm_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_AddRelation_clicked();

    void on_pushButton_DelRelation_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Reload_clicked();

    void on_pushButton_ChangeDirection_clicked();

    void on_lineEdit_RelationI_editingFinished();

    void on_lineEdit_RelationJ_editingFinished();

private:
    Ui::MainWindow *ui;
    GraphDirection addDirection;

    QString getDirectionStr(GraphDirection&);
    void reloadFile();
};

#endif // MAINWINDOW_HPP
