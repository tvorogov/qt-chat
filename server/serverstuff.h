#ifndef SERVERSTUFF_H
#define SERVERSTUFF_H

#include <QObject>

class QTcpServer;
class QTcpSocket;


class ServerStuff : public QObject
{
    Q_OBJECT


public:
    explicit ServerStuff(QObject *parent = nullptr);

    QTcpServer *tcpServer;

    QTcpSocket *tcpSocket;


public slots:
    void sendToClients(QTcpSocket *socket, const QByteArray buffer);

    virtual void newConnection();


private slots:

    void readClient();

private:
    QList<QTcpSocket*> clientsList;


signals:

    void gotNewMesssage(QString msg);

};

#endif // SERVERSTUFF_H
