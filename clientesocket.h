#ifndef CLIENTESOCKET_H
#define CLIENTESOCKET_H

#include <QTcpSocket>

class ClienteSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ClienteSocket(QObject *parent = nullptr);
    void enviaMensaje(int enumeracion, const QString &mensaje);
    void setDireccionDelServidor(const QString &ip);
    void setPuertoDelServidor(quint16 puerto);
    void conectaConElServidor();
    bool setSocketDescriptor(qintptr socketDescriptor, SocketState state = ConnectedState, OpenMode openMode = ReadWrite) override;

    QString id() const
    {
        return mId;
    }
signals:
    void mensajeRecibido(int enumeracion, const QString &mensaje, ClienteSocket *socket);
    void desconectado(ClienteSocket *socket);
private:
    QString mDireccionDelServidor;
    quint16 mPuertoDelServidor;
    bool mConectado;
    QString mId;
};

#endif // CLIENTESOCKET_H
