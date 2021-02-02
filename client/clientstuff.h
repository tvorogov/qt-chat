#ifndef CLIENTSTUFF_H
#define CLIENTSTUFF_H

#include <QObject>


class QTcpSocket;

class ClientStuff : public QObject
{
    Q_OBJECT
public:
    explicit ClientStuff(QObject *parent = nullptr);

    QTcpSocket *tcpSocket;

public slots:

    void connectToHost(QString host, int port);
    void closeConnection();
    void sendSomething(QString fileType, QString fileName, const QByteArray data);


private slots:
    void readyRead();

private:



signals:
    void hasReadSome(QString name, QByteArray textByteArray);
    void reciveEncryptKey(int,int,int);
    void setEncryptionEnabled(bool);
};

#endif // CLIENTSTUFF_H
