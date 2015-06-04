#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>

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
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_Add_2_clicked();

    void on_pushButton_DelNode_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_HPP
