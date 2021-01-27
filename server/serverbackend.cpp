#include "serverbackend.h"
#include <QtDebug>
#include "serverstuff.h"
#include <QTcpServer>
#include <QTcpSocket>

#include <QNetworkInterface>

ServerBackend::ServerBackend(QObject *parent) : QObject(parent)
{
        server = new ServerStuff();

         connect(server, &ServerStuff::gotNewMesssage, this, &ServerBackend::gotNewMesssage);

}

QString ServerBackend::defServer()
{
    QList<QHostAddress> myIpAddresses = QNetworkInterface::allAddresses();

    for ( int i = 0; i < myIpAddresses.size(); i++ ) {
        if ( myIpAddresses.at( i ).protocol() == QAbstractSocket::IPv4Protocol )
        {

            if (myIpAddresses.at( i ).toString() != "127.0.0.1")
                return myIpAddresses.at(i).toString();
        }
    }
}

void ServerBackend::startServerClicked(QString address, QString port)
{

    qDebug()<<address<<port;

    connect(server->tcpServer,&QTcpServer::newConnection,this,&ServerBackend::clientConnectedToServer);
    connect(server->tcpServer,&QTcpServer::newConnection,server,&ServerStuff::newConnection);







    if(!server->tcpServer->listen(QHostAddress(address),port.toInt()))
    {

           emit newMessage(QString("Unable to start the server: %1.").arg(server->tcpServer->errorString()));
//        return QString("Unable to start the server: %1.").arg(server->tcpServer->errorString());

    } else {

        emit newMessage("Server started");
//        return "Server started";
    }




}

QString ServerBackend::stopServerClicked()
{

}

void ServerBackend::gotNewMesssage(QString msg)
{
    qDebug()<<msg;
    emit newMessage(msg);

}

void ServerBackend::clientConnectedToServer()
{
    emit clientConnected();
}

void ServerBackend::clientDisconnectedFromServer()
{
    emit clientDisconnected();
}
