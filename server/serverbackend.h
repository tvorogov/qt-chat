#ifndef SERVERBACKEND_H
#define SERVERBACKEND_H

#include <QObject>

class ServerStuff;

class ServerBackend : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(bool serverStatus READ getServerStatus WRITE setServerStatus NOTIFY serverStatusChanged)
public:
    explicit ServerBackend(QObject *parent = nullptr);

signals:
    void newMessage(QString msg);
    void clientConnected();
    void clientDisconnected();

public slots:
    QString defServer();
    void startServerClicked(QString address, QString port);
    QString stopServerClicked();
    void gotNewMesssage(QString msg);
    void clientConnectedToServer();
    void clientDisconnectedFromServer();

private:
    ServerStuff *server;

};

#endif // SERVERBACKEND_H
