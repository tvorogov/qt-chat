#include "serverstuff.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QDir>

ServerStuff::ServerStuff(QObject *parent) : QObject(parent)
{
    
    tcpServer = new QTcpServer();
    
    
    
}

void ServerStuff::newConnection()
{
    
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);

    clientsList<<clientSocket;
    
}



void ServerStuff::readClient()
{


    QTcpSocket *clientSocket = (QTcpSocket*)sender();



    QByteArray buffer;
    
    QDataStream socketStream(clientSocket);
    



    
    socketStream.startTransaction();
    socketStream >>buffer;

    qDebug()<<"buffer"<<buffer;

    QString header = buffer.mid(0,128);
    QString username = header.split(",")[0].split(":")[1];
    QString fileType = header.split(",")[1].split(":")[1];


    if (fileType == "file") {

        QString fileName = header.split(",")[2].split(":")[1];
        QString fileExtension= fileName.split(".")[1];

        QString filePath = QDir::currentPath();
        filePath = filePath+"/"+fileName;

        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(buffer.mid(128));
        }


    } else if (fileType == "message") {

        emit gotNewMesssage(buffer.mid(128));

    }




    sendToClients(clientSocket,buffer);





}


void ServerStuff::sendToClients(QTcpSocket *socket, const QByteArray buffer)
{

    for (int i=0; i<clientsList.count(); i++ ) {

        if (clientsList.at(i) == socket)
            continue;

        QDataStream socketStream(clientsList.at(i));


        socketStream<<buffer;

        qDebug()<<"sended";


    }





    

    
}

