#include "clientbackend.h"

#include <clientstuff.h>
#include <clientencrypt.h>

#include <QDataStream>
#include <QByteArray>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>


ClientBackend::ClientBackend(QObject *parent) : QObject(parent)
  ,encryptedClient(NULL)
  ,isEncryptionEnabled(false)
{

//    isEncryptionEnabled = true;

    client = new ClientStuff();


    connect(client, SIGNAL(hasReadSome(QString,QByteArray)), this, SLOT(receivedSomething(QString,QByteArray)));



    encryptedClient = new ClientEncrypt();

    connect(encryptedClient,SIGNAL(shareGeneratedKey(int, int, int)),this,SLOT(sendEncryptKey(int,int,int)));

    connect(client,SIGNAL(reciveEncryptKey(int,int,int)),encryptedClient,SLOT(handleRecivedKey(int,int,int)));

    connect(client,SIGNAL(setEncryptionEnabled(bool)),this,SLOT(setEncryptionEnabled(bool)));

}


void ClientBackend::sendMessageClicked(QString msg)
{    

    QByteArray byteArray;
    byteArray = msg.toUtf8();

    if (isEncryptionEnabled) {
        byteArray = encryptedClient->encryptText(byteArray);

    }

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

void ClientBackend::receivedSomething(QString name,QByteArray textByteArray)
{

    qDebug()<<isEncryptionEnabled;
    QString receivedMSG;
    receivedMSG = textByteArray;

    if (isEncryptionEnabled)
        receivedMSG = encryptedClient->decryptText(textByteArray);


    emit someMessage(name + " : " + receivedMSG);
}

void ClientBackend::startEncrypt(bool encryptInit)
{

        encryptedClient->encryptInitiator = encryptInit;
            encryptedClient->generateNum();
}


void ClientBackend::sendEncryptKey(int num1, int num2, int num3)
{

    QString keyString = QString::number(num1) + ":" + QString::number(num2) + ":" + QString::number(num3);

//    QByteArray byteArray = keyString.toUtf8();

    client->sendSomething("key","null",keyString.toUtf8());


}


void ClientBackend::connectClicked(QString address, QString port)
{

    client->connectToHost(address,port.toInt());

    emit someMessage("trying connect to "+address+":"+port);



}

void ClientBackend::disconnectClicked()
{
    client->closeConnection();
}
