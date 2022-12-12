#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void setPageNumber(int value);

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

//    void on_lineEdit_editingFinished();

    void on_btnTransactions_clicked();

    void on_loginButton_clicked();

    void loginSlot(QNetworkReply *reply);

    void setWebToken(const QByteArray &value);

    QByteArray getWebToken() const;

    void on_btn_back_transactions_clicked();

    void getCardDetails();
    void cardSlot(QNetworkReply *reply);

    void getPerson(QString personId);
    void personSlot(QNetworkReply *reply);

    void getCardAccounts();
    void accountSlot(QNetworkReply *reply);

    void on_btnConfirm_clicked();

    void getBalance();
    void balanceSlot(QNetworkReply *reply);

    void updateBalance(int updatedAmount);
    void updateBalanceSlot(QNetworkReply *reply);

    void addLog();
    void addLogSlot(QNetworkReply *reply);

    void getLogs();
    void getLogsSlot(QNetworkReply *reply);


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *cardManager;
    QNetworkAccessManager *personManager;
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *balanceManager;

    QNetworkAccessManager *addLogManager;
    QNetworkAccessManager *getLogManager;

    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webToken;
    int pageNumber = 0;
};

#endif // MAINWINDOW_H
