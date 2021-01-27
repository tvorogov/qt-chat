#include "clientbackend.h"
#include <clientstuff.h>
#include <QDataStream>
#include <QByteArray>
#include <QTcpSocket>

#include <QFile>
#include <QFileDialog>


ClientBackend::ClientBackend(QObject *parent) : QObject(parent)
{


    client = new ClientStuff();

        connect(client, &ClientStuff::hasReadSome, this, &ClientBackend::receivedSomething);
//        connect(this,&ClientBackend::logined,&ClientStuff::setAccountUserName);
        connect(this,SIGNAL(logined(QString,QString)),client,SLOT(setAccountUserName(QString,QString)));


}

void ClientBackend::sendMessageClicked(QString msg)
{    

    QByteArray byteArray = msg.toUtf8();

    client->sendSomething("message","null",byteArray);

}

void ClientBackend::sendFileClicked(QString filePath)
{

    QFile file(filePath.remove(0,6));

    if(file.open(QIODevice::ReadOnly)) {

        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());

        QByteArray byteArray = file.readAll();

        client->sendSomething("file",fileName,byteArray);

    } else {
        qDebug()<<"error while write attachment";
    }

}

void ClientBackend::receivedSomething(QString msg)
{
    emit someMessage(msg);
}



void ClientBackend::connectClicked(QString address, QString port)
{

    qDebug()<<address<<port;

        client->connectToHost(address,port.toInt());

        emit someMessage("trying connect to "+address+":"+port);



}

void ClientBackend::disconnectClicked()
{
    client->closeConnection();
}
