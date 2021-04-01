#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_getAllPersons_clicked();
    void allPersonsSlot(QNetworkReply *reply);
    void onePersonSlot(QNetworkReply *reply);
    void fullNameSlot(QNetworkReply *reply);
    void RaiseSlot(QNetworkReply *reply);

    void on_getOneperson_clicked();

    void on_getFullName_clicked();

    void on_buttonRaise_clicked();

    void on_lineEditId_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *ptrAllPersonsManager;
    QNetworkReply *ptrAllPersonsReply;

    QNetworkAccessManager *ptrOnePersonManager;
    QNetworkReply *ptrOnePersonReply;

    QNetworkAccessManager *ptrFullNameManager;
    QNetworkReply *ptrFullNameReply;

    QNetworkAccessManager *ptrRaiseManager;
    QNetworkReply *ptrRaiseReply;
};
#endif // MAINWINDOW_H
