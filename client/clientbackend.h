#ifndef CLIENTBACKEND_H
#define CLIENTBACKEND_H

#include <QObject>


class ClientStuff;

class ClientBackend : public QObject
{
    Q_OBJECT
public:
    explicit ClientBackend(QObject *parent = nullptr);

signals:
        void someMessage(QString msg);
        void logined(const QString name,const QString pass);


public slots:
    void connectClicked(QString address, QString port);
    void disconnectClicked();
    void sendMessageClicked(QString msg);
    void sendFileClicked(QString filePath);
    void receivedSomething(QString msg);




private slots:


private:

    ClientStuff * client;

    QString username;
    QString password;

};

#endif // CLIENTBACKEND_H
