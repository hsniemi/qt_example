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
                    +" "+json_object["fname"].toString()+"      "+json_object["lname"].toString()+" "+QString::number((json_object["money"].toDouble()))+"\r\n";
        }
        ui->label_result->setText(persons);
    }

    ptrAllPersonsReply->deleteLater();
    reply->deleteLater();
    ptrAllPersonsManager->deleteLater();
}
