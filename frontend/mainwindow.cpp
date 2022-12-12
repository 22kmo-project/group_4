#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->NumMenu->hide();
    //ui->Saldo->hide();
    //ui->listTransactions->hide();

    this->setPageNumber(0);

    ui->drawAmount->setValidator( new QIntValidator(0, 1000, this) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool toggle = false;
bool withdraw = false;
double amount;

QString cardId;
QString personId;
QString accountId;

int currentBalance;
int drawAmount;
int changedAmount; // amount changed - used in logging


void MainWindow::on_btnCheckBalance_clicked()
{
//    ui->Saldo->show();
//    ui->lblAmount->setNum(amount);
    this->setPageNumber(3);
    this->getCardAccounts();
}
void MainWindow::on_btnBack2_clicked() // balance back button
{
//    ui->Saldo->hide();
    this->setPageNumber(1);
}

void MainWindow::on_btnWithdraw_clicked() // withdraw button
{
    withdraw = true;
//    toggle = !toggle;
//    if(toggle){
//        ui->NumMenu->show();
//        ui->Options->hide();
//    }   else {
//        ui->NumMenu->hide();
//        ui->Options->show();
//    }

    this->setPageNumber(2);
}


void MainWindow::on_btnDeposit_clicked() // deposit button
{
    withdraw = false;
//    toggle = !toggle;
//    if(toggle){

//        ui->NumMenu->show();
//        ui->Options->hide();
//    } else {

//        ui->NumMenu->hide();
//        ui->Options->show();
//    }

    this->setPageNumber(2);
}

void MainWindow::on_btnBack_clicked() // numpad back button
{
//    toggle = false;
//    ui->NumMenu->hide();
//    ui->Options->show();

    this->setPageNumber(1);
}



void MainWindow::on_draw20_clicked()
{
//    if((withdraw) && (amount >= 20)){
//        amount -= 20;
//        ui->listTransactions->addItem("20€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 20;
//        ui->listTransactions->addItem("20€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("20");
}

void MainWindow::on_draw40_clicked()
{
//    if((withdraw) && (amount >= 40)){
//        amount -= 40;
//        ui->listTransactions->addItem("40€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 40;
//        ui->listTransactions->addItem("40€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("40");
}

void MainWindow::on_draw50_clicked()
{
//    if((withdraw) && (amount >= 50)){
//        amount -= 50;
//        ui->listTransactions->addItem("50€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 50;
//        ui->listTransactions->addItem("50€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("50");
}

void MainWindow::on_draw80_clicked()
{
//    if((withdraw) && (amount >= 80)){
//        amount -= 80;
//        ui->listTransactions->addItem("80€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 80;
//        ui->listTransactions->addItem("80€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("80");
}

void MainWindow::on_draw100_clicked()
{
//    if((withdraw) && (amount >= 100)){
//        amount -= 100;
//        ui->listTransactions->addItem("100€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 100;
//        ui->listTransactions->addItem("100€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("100");
}

void MainWindow::on_draw200_clicked()
{
//    if((withdraw) && (amount >= 200)){
//        amount -= 200;
//        ui->listTransactions->addItem("200€ was withdrawn from your account.");
//    }
//    if(!withdraw){
//        amount += 200;
//        ui->listTransactions->addItem("200€ was deposited to your account.");
//    }
//    ui->NumMenu->hide();
//    ui->Options->show();
//    toggle = false;
    ui->drawAmount->setText("200");
}

void MainWindow::on_btnConfirm_clicked()
{
    drawAmount = ui->drawAmount->text().toInt();

    if(withdraw){
        drawAmount = drawAmount * -1;
    }

    qDebug()<<drawAmount;

    this->getBalance();
}

void MainWindow::getBalance()
{
    QString site_url = "http://localhost:3000/account/card/" + cardId;
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));

    reply = accountManager->get(request);
}

void MainWindow::balanceSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QJsonObject json_obj = json_array[0].toObject();

    int balance = json_obj["balance"].toInt();

    accountId = QString::number(json_obj["accountId"].toInt());


    // tarkistus
    if(drawAmount == 0){
        qDebug()<<"please give an amount";
    } else {
        int updatedBalance = balance + drawAmount;
        if(updatedBalance < 0){
            // fail
            qDebug()<<"Error making a transaction!";
        } else {
            // success
            qDebug()<<"Transaction can be made";
            this->updateBalance(updatedBalance);
        }
    }




    reply->deleteLater();
    accountManager->deleteLater();
}

void MainWindow::updateBalance(int updatedAmount)
{
    changedAmount = updatedAmount;

    QJsonObject jsonObj;
    jsonObj.insert("balance",updatedAmount);

    QString site_url = "http://localhost:3000/account/transaction/" + accountId;
    qDebug()<<site_url;
    QNetworkRequest request((site_url));

    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(updateBalanceSlot(QNetworkReply*)));

    reply = balanceManager->put(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::updateBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"updateBalanceSlot: " + response_data;

    this->addLog();

    reply->deleteLater();
    balanceManager->deleteLater();
}



void MainWindow::on_btnLogOut_clicked()
{
//    ui->Main_Menu->hide();
    this->setPageNumber(0);
    this->setWebToken("false");
    ui->helloText->setText("hello");
}

//void MainWindow::on_lineEdit_editingFinished()
//{
//  int integer_value = ui->lineEdit->text().toInt();
//  if((withdraw) && (amount >= integer_value)){
//      amount -= integer_value;
//      QString c = QString::number(integer_value);
//      QString x = " was withdrawn from your account.";
//      QString y = c + x;
//      ui->listTransactions->addItem(y);

//  }
//  if(!withdraw){
//      amount += integer_value;
//      QString c = QString::number(integer_value);
//      QString x = " was deposited to your account.";
//      QString y = c + x;
//      ui->listTransactions->addItem(y);
//  }

//  ui->lineEdit->clear();
//  ui->NumMenu->hide();
//  ui->Options->show();
//  toggle = false;
//}



void MainWindow::on_btnTransactions_clicked()
{
//    ui->listTransactions->show();
    this->setPageNumber(4);
    this->getLogs();
}


void MainWindow::on_btn_back_transactions_clicked()
{
    this->setPageNumber(1);
}


// login button clicked
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


// login api response
void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    int loginTest = QString::compare(response_data, "false");
    if(loginTest == -1){
        qDebug()<<"Logged in";
        this->setWebToken(response_data);
        this->setPageNumber(1);
        cardId = ui->UsernameInput->text();
        this->getCardDetails();
    } else {
        qDebug()<<"Invalid login details";
    }

    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::setWebToken(const QByteArray &value)
{
    webToken = "Bearer " + value;
    qDebug()<<webToken;

}

QByteArray MainWindow::getWebToken() const
{
    return webToken;
}


void MainWindow::setPageNumber(int value)
{
    pageNumber = value;
    switch(value){

    case 0: //login
        ui->LogIn->setVisible(true);
        ui->Main_Menu->setVisible(false);
        ui->btnLogOut->setVisible(false);

        // clear inputs
        ui->PasswordInput->clear();
        ui->UsernameInput->clear();
    break;

    case 1: //menu
        ui->Main_Menu->setVisible(true);
        ui->Options->setVisible(true);
        ui->btnLogOut->setVisible(true);

        ui->LogIn->setVisible(false);
        ui->NumMenu->setVisible(false);
        ui->Saldo->setVisible(false);
        ui->Transactions->setVisible(false);

    break;

    case 2: //numpad
        ui->Options->setVisible(false);
        ui->NumMenu->setVisible(true);
        ui->btnLogOut->setVisible(false);
        ui->drawAmount->clear();
    break;

    case 3: //balance
        ui->Options->setVisible(false);
        ui->Saldo->setVisible(true);
        ui->btnLogOut->setVisible(false);
    break;

    case 4: //transactions
        ui->Options->setVisible(false);
        ui->Transactions->setVisible(true);
        ui->btnLogOut->setVisible(false);
    break;

    }

}

void MainWindow::getCardDetails(){
    QJsonObject jsonObj;

    QString site_url = "http://localhost:3000/card/" + cardId;
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    cardManager = new QNetworkAccessManager(this);
    connect(cardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardSlot(QNetworkReply*)));

    reply = cardManager->get(request);
}

void MainWindow::cardSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString person;
    //person = json_obj["personId"].toString();
    person=QString::number(json_obj["personId"].toInt());
    personId = QString::number(json_obj["personId"].toInt());
    accountId = QString::number(json_obj["accountId"].toInt());
    qDebug()<<"hello " + person + "!";

    this->getPerson(person);

    reply->deleteLater();
    cardManager->deleteLater();
}

void MainWindow::getPerson(QString personId){
    //QJsonObject jsonObj;

    QString site_url = "http://localhost:3000/person/" + personId;
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    personManager = new QNetworkAccessManager(this);
    connect(personManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(personSlot(QNetworkReply*)));

    reply = personManager->get(request);
}
void MainWindow::personSlot(QNetworkReply *reply){
    response_data = reply->readAll();
    //qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString personName = json_obj["firstname"].toString() + " " + json_obj["lastname"].toString();
    ui->helloText->setText("Hello " + personName + "!");

    reply->deleteLater();
    personManager->deleteLater();
}

void MainWindow::getCardAccounts()
{
    QString site_url = "http://localhost:3000/account/card/" + cardId;
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accountSlot(QNetworkReply*)));

    reply = accountManager->get(request);
}

void MainWindow::accountSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

//    foreach(const QJsonValue &value, json_array){
//        QJsonObject json_obj = value.toObject();
//    }
    QJsonObject json_obj = json_array[0].toObject();

    QString balance = QString::number(json_obj["balance"].toInt());

    qDebug()<<"balance: " + balance;
    ui->lblAmount->setText(balance);

    reply->deleteLater();
    accountManager->deleteLater();
}

// ADDING LOG
void MainWindow::addLog()
{
    QJsonObject jsonObj;
    jsonObj.insert("date","2022-12-10");
    jsonObj.insert("personId", personId);
    jsonObj.insert("accountId", accountId);
    jsonObj.insert("cardId", cardId);
    jsonObj.insert("amount", drawAmount);

    QString site_url = "http://localhost:3000/log";
    QNetworkRequest request((site_url));

    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    addLogManager = new QNetworkAccessManager(this);
    connect(addLogManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addLogSlot(QNetworkReply*)));

    reply = addLogManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::addLogSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    this->setPageNumber(1);
    reply->deleteLater();
    addLogManager->deleteLater();
}

// GETTING LOGS
void MainWindow::getLogs()
{
    ui->listTransactions->clear();

    QString site_url = "http://localhost:3000/log/account/" + accountId;
    QNetworkRequest request((site_url));

    //WEBTOKEN MUIHIN APIKUTSUIHIN
    QByteArray myToken = this->getWebToken();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getLogManager = new QNetworkAccessManager(this);
    connect(getLogManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLogsSlot(QNetworkReply*)));

    reply = getLogManager->get(request);
}

void MainWindow::getLogsSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString log;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();

        log = "Account: " + QString::number(json_obj["accountId"].toInt()) + "\n" + "Card: " + QString::number(json_obj["cardId"].toInt()) + "\n" + "Amount: " + QString::number(json_obj["amount"].toInt()) + "\n";

        ui->listTransactions->addItem(log);
    }
//    was withdrawn from your account.
//    was deposited to your account.
    reply->deleteLater();
    getLogManager->deleteLater();
}




