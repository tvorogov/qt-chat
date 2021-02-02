#ifndef CLIENTENCRYPT_H
#define CLIENTENCRYPT_H

#include <QObject>

class QRandomGenerator;
class QAESEncryption;

class ClientEncrypt : public QObject
{
    Q_OBJECT
public:
    explicit ClientEncrypt(QObject *parent = nullptr);

    bool encryptInitiator;

    void generateNum();

signals:

    void shareGeneratedKey(int base,int modules,int publicKey);


public slots:

    void calculateSecretKey(int);


    QString decryptText(QByteArray textByteArray);
    QByteArray encryptText(QByteArray textByteArray);


    void handleRecivedKey(int,int,int);
private:

    int publicBaseNum;
    int publicModulusNum;
    int privateKey;

    int sharedPublicKey;
    int secretKey;

        QByteArray keyByteArray;

    QRandomGenerator *generator;

    QAESEncryption *encryption;


};

#endif // CLIENTENCRYPT_H
