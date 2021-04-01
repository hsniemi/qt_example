#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getAllPersons_clicked()
{
    QString site_url="http://localhost:3000/example/allpersons";
    QString credentials="automat123:pass123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    ptrAllPersonsManager = new QNetworkAccessManager(this);

    connect(ptrAllPersonsManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(allPersonsSlot(QNetworkReply*)));
    ptrAllPersonsReply = ptrAllPersonsManager->get(request);
}

void MainWindow::allPersonsSlot(QNetworkReply*reply)
{
    QByteArray response_data = reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->label_result->setText("Virhe tietokantayhteydessä");
    }
    else{
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString persons;
        foreach(const QJsonValue &value,json_array){
            QJsonObject json_object=value.toObject();
            persons+=QString::number((json_object["id_person"].toInt()))
                    +" "+json_object["fname"].toString()+" "+json_object["lname"].toString()
                    +" "+QString::number(json_object["money"].toDouble())+"\r\n";
        }
        ui->label_result->setText(persons);
    }

    ptrAllPersonsReply->deleteLater();
    reply->deleteLater();
    ptrAllPersonsManager->deleteLater();
}

void MainWindow::on_getOneperson_clicked()
{
    QString id=ui->lineEditId->text();
    QString site_url="http://localhost:3000/example/oneperson/"+id;
    QString credentials="automat123:pass123";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    ptrOnePersonManager = new QNetworkAccessManager(this);

    connect(ptrOnePersonManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(onePersonSlot(QNetworkReply*)));
    ptrOnePersonReply = ptrOnePersonManager->get(request);
}

void MainWindow::onePersonSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->label_result->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("")==0){
        ui->label_result->setText("Tunnuksella ei löydy asiakasta");
    }
    else{
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_object=json_doc.object();
        QString person=QString::number((json_object["id_person"].toInt()))
                +" "+json_object["fname"].toString()+" "+json_object["lname"].toString()
                +" "+QString::number(json_object["money"].toDouble())+"\r\n";
        ui->label_result->setText(person);

    }

    ptrOnePersonReply->deleteLater();
    reply->deleteLater();
    ptrOnePersonManager->deleteLater();
}

void MainWindow::on_getFullName_clicked()
{
    QString id=ui->lineEditId->text();
    QString site_url="http://localhost:3000/example/fullname/"+id;
    QString credentials="automat123:pass123";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    ptrFullNameManager = new QNetworkAccessManager(this);

    connect(ptrFullNameManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(fullNameSlot(QNetworkReply*)));
    ptrFullNameReply = ptrFullNameManager->get(request);
}

void MainWindow::fullNameSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0){
        ui->label_result->setText("Virhe tietokantayhteydessä");
    }
    else if(response_data.compare("")==0){
        ui->label_result->setText("Tunnuksella ei löydy asiakasta");
    }
    else{
//        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
//        QJsonObject json_object=json_doc.object();
//        QString person=json_object["fullname"].toString()+"\r\n";
//        ui->label_result->setText(person);
        ui->label_result->setText(response_data);
    }
    ptrFullNameReply->deleteLater();
    reply->deleteLater();
    ptrFullNameManager->deleteLater();
}
