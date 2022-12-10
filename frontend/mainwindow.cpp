#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->NumMenu->hide();
    ui->Saldo->hide();
    ui->listTransactions->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool toggle = false;
bool withdraw = false;
double amount;

void MainWindow::on_btnCheckBalance_clicked()
{
    ui->Saldo->show();
    ui->lblAmount->setNum(amount);
}
void MainWindow::on_btnBack2_clicked()
{
    ui->Saldo->hide();
}

void MainWindow::on_btnWithdraw_clicked() // withdraw
{
    withdraw = true;
    toggle = !toggle;
    if(toggle){
        ui->NumMenu->show();
        ui->Options->hide();
    }   else {
        ui->NumMenu->hide();
        ui->Options->show();
    }
}


void MainWindow::on_btnDeposit_clicked()
{
    withdraw = false;
    toggle = !toggle;
    if(toggle){

        ui->NumMenu->show();
        ui->Options->hide();
    } else {

        ui->NumMenu->hide();
        ui->Options->show();
    }
}

void MainWindow::on_btnBack_clicked()
{
    toggle = false;
    ui->NumMenu->hide();
    ui->Options->show();
}



void MainWindow::on_draw20_clicked()
{
    if((withdraw) && (amount >= 20)){
        amount -= 20;
        ui->listTransactions->addItem("20€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 20;
        ui->listTransactions->addItem("20€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_draw40_clicked()
{
    if((withdraw) && (amount >= 40)){
        amount -= 40;
        ui->listTransactions->addItem("40€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 40;
        ui->listTransactions->addItem("40€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_draw50_clicked()
{
    if((withdraw) && (amount >= 50)){
        amount -= 50;
        ui->listTransactions->addItem("50€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 50;
        ui->listTransactions->addItem("50€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_draw80_clicked()
{
    if((withdraw) && (amount >= 80)){
        amount -= 80;
        ui->listTransactions->addItem("80€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 80;
        ui->listTransactions->addItem("80€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_draw100_clicked()
{
    if((withdraw) && (amount >= 100)){
        amount -= 100;
        ui->listTransactions->addItem("100€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 100;
        ui->listTransactions->addItem("100€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_draw200_clicked()
{
    if((withdraw) && (amount >= 200)){
        amount -= 200;
        ui->listTransactions->addItem("200€ was withdrawn from your account.");
    }
    if(!withdraw){
        amount += 200;
        ui->listTransactions->addItem("200€ was deposited to your account.");
    }
    ui->NumMenu->hide();
    ui->Options->show();
    toggle = false;
}

void MainWindow::on_btnLogOut_clicked()
{
    ui->Main_Menu->hide();
}

void MainWindow::on_lineEdit_editingFinished()
{
  int integer_value = ui->lineEdit->text().toInt();
  if((withdraw) && (amount >= integer_value)){
      amount -= integer_value;
      QString c = QString::number(integer_value);
      QString x = " was withdrawn from your account.";
      QString y = c + x;
      ui->listTransactions->addItem(y);

  }
  if(!withdraw){
      amount += integer_value;
      QString c = QString::number(integer_value);
      QString x = " was deposited to your account.";
      QString y = c + x;
      ui->listTransactions->addItem(y);
  }

  ui->lineEdit->clear();
  ui->NumMenu->hide();
  ui->Options->show();
  toggle = false;
}



void MainWindow::on_btnTransactions_clicked()
{
    ui->listTransactions->show();

}

void MainWindow::on_loginButton_clicked()
{
    QString cardId = ui->UsernameInput->text();
    QString pin = ui->PasswordInput->text();

    //qDebug()<<cardId + " " + pin;

    QJsonObject jsonObj;
    jsonObj.insert("cardId", cardId);
    jsonObj.insert("pin", pin);

    QString site_url = "http://localhost:3000/login";
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    //QByteArray myToken = "Bearer " + webToken
    //request.setRawHeader(QByteArray("Authorization"),(myToken));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    int loginTest = QString::compare(response_data, "false");
    if(loginTest == -1){
        qDebug()<<"Logged in";
        this->setWebToken(response_data);
    } else {
        qDebug()<<"Invalid login details";
    }

}

void MainWindow::setWebToken(const QByteArray &value)
{
    webToken = "Bearer " + value;
    qDebug()<<webToken;

}
