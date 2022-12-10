#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_btnCheckBalance_clicked();

    void on_btnWithdraw_clicked();

    void on_btnDeposit_clicked();

    void on_btnBack_clicked();

    void on_btnBack2_clicked();

    void on_draw20_clicked();

    void on_draw40_clicked();

    void on_draw50_clicked();

    void on_draw80_clicked();

    void on_draw100_clicked();

    void on_draw200_clicked();

    void on_btnLogOut_clicked();

    void on_lineEdit_editingFinished();

    void on_btnTransactions_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
