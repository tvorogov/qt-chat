#ifndef CLIENTBACKEND_H
#define CLIENTBACKEND_H

#include <QObject>


class ClientStuff;
class ClientEncrypt;

class ClientBackend : public QObject
{
    Q_OBJECT

public:
    explicit ClientBackend(QObject *parent = nullptr);


signals:
        void clientConnected();
        void someMessage(QString msg);

public slots:

        void connectClicked(QString address, QString port);
        void disconnectClicked();
        void sendMessageClicked(QString username,QString msg);
        void sendFileClicked(QString filePath);
        void receivedSomething(QString name,QByteArray textByteArray);
        void startEncrypt(bool);

        QString defServer();
        void setEncryptionEnabled(bool someBool)
        {
        isEncryptionEnabled = someBool;
        };

private slots:

        void sendEncryptKey(int,int,int);


private:

        ClientStuff *client;
        ClientEncrypt *encryptedClient;


        bool isEncryptionEnabled ;

};

#endif // CLIENTBACKEND_H
