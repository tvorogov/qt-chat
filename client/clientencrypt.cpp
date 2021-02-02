#include "clientencrypt.h"
#include "aes/qaesencryption.h"

#include <QDebug>
#include <QTime>
#include <QRandomGenerator>
#include <QtMath>
#include <QCryptographicHash>




ClientEncrypt::ClientEncrypt(QObject *parent) : QObject(parent)
  ,publicBaseNum(0)
  ,publicModulusNum(0)
  ,encryptInitiator(false)

{


    encryption = new QAESEncryption (QAESEncryption::AES_128, QAESEncryption::ECB);


    generator = new QRandomGenerator;
    generator->seed(QTime::currentTime().msec());




}

void ClientEncrypt::generateNum()
{
    publicBaseNum = generator->bounded(1000);
    publicModulusNum = generator->bounded(1000);

    privateKey = generator->bounded(1000);


    sharedPublicKey = (int)qPow(publicBaseNum,privateKey) % publicModulusNum;

    qDebug()<<"publicBaseNum"<<publicBaseNum<<"publicModulusNum"<<publicModulusNum<<"privateKey"<<privateKey<<"sharedPublicKey"<<sharedPublicKey;

    emit shareGeneratedKey(publicBaseNum,publicModulusNum,sharedPublicKey);

}

void ClientEncrypt::handleRecivedKey(int base, int modlus, int key)
{


    if (!encryptInitiator) {

        publicBaseNum = base;
        publicModulusNum = modlus;
        privateKey = generator->bounded(1000);

        sharedPublicKey = (int)qPow(publicBaseNum,privateKey) % publicModulusNum;


        emit shareGeneratedKey(publicBaseNum,publicModulusNum,sharedPublicKey);

    }

    calculateSecretKey(key);
}

void ClientEncrypt::calculateSecretKey(int recivedPublicKey)
{


    secretKey = (int)qPow(recivedPublicKey,privateKey) % publicBaseNum;

    qDebug()<<"recivedPublicKey"<<recivedPublicKey;
    qDebug()<<"secretKey"<<secretKey;

    keyByteArray.fill(0,16);
    keyByteArray.insert(0,secretKey);
    keyByteArray.resize(16);



}

QByteArray ClientEncrypt::encryptText(QByteArray textByteArray)
{
   QByteArray encryptedByteArray;

   encryptedByteArray = encryption->encode(textByteArray,keyByteArray);

   return encryptedByteArray;
}

QString ClientEncrypt::decryptText(QByteArray textByteArray)
{
    QString decryptedText;
    QByteArray decryptedByteArray;


    decryptedByteArray= encryption->decode(textByteArray,keyByteArray);
    decryptedText = encryption->removePadding(decryptedByteArray);

    return decryptedText;


}
