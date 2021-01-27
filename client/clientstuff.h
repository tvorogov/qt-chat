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
    void setAccountUserName(const QString name, const QString pass);
    void connectToHost(QString host, int port);
    void closeConnection();
    void sendSomething(QString fileType, QString fileName, const QByteArray data);


private slots:
    void readyRead();

private:

    QString username;
    QString password;

signals:
    void hasReadSome(QString msg);

};

#endif // CLIENTSTUFF_H
