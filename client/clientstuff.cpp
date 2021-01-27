#include "clientstuff.h"
#include  <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QTime>


ClientStuff::ClientStuff(QObject *parent) : QObject(parent)

{
     tcpSocket = new QTcpSocket();


     qDebug()<<"q";

}

void ClientStuff::setAccountUserName(const QString name, const QString pass)
{
    qDebug()<<name<<pass;


    username = name;
    password = pass;


}

void ClientStuff::connectToHost(QString host, int port)
{

    tcpSocket->connectToHost(host,port);

    connect(tcpSocket,&QTcpSocket::connected,this,[](){ qDebug()<<"connected";});
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);

}

void ClientStuff::closeConnection()
{
    tcpSocket->abort();
}

void ClientStuff::sendSomething(QString fileType, QString fileName, const QByteArray data)
{

    QDataStream socketStream(tcpSocket);






    username = QTime::currentTime().toString("ss");



        QByteArray header;
        header.prepend(QString("username:%1,fileType:%2,fileName:%3;").arg("username").arg(fileType).arg(fileName).toUtf8());
        header.resize(128);
        qDebug()<<header;

        QByteArray dataByteArray;

        dataByteArray = data;

        dataByteArray.prepend(header);

        socketStream << dataByteArray;




}



void ClientStuff::readyRead()
{

    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    QDataStream socketStream(clientSocket);

    QByteArray buffer;

//    if (!socketStream.commitTransaction())
//        return;
        socketStream.startTransaction();

    socketStream>>buffer;


        if (!socketStream.commitTransaction())
            qDebug()<<"some errer while transaction";

    QString header = buffer.mid(0,128);
    QString username = header.split(",")[0].split(":")[1];
    QString fileType = header.split(",")[1].split(":")[1];

    if (fileType == "file") {

        QString fileName = header.split(",")[2].split(":")[1];
        QString fileExtension= fileName.split(".")[1];
        QString fileSize = header.split(",")[3].split(":")[1].split(";")[0];

        QString filePath = QDir::currentPath();
        filePath = filePath+"/"+fileName;

        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(buffer.mid(128));
        }



    } else if (fileType == "message") {

       emit hasReadSome(username+" : "+buffer.mid(128));
    }



}
