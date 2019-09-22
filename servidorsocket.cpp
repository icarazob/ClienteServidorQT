#include "servidorsocket.h"
#include "clientesocket.h"

ServidorSocket::ServidorSocket(QObject *parent) : QTcpServer { parent }
{
    mPuerto = 0;
    mEscuchando = false;
}

ServidorSocket::~ServidorSocket()
{
    qDeleteAll(mClientes);
}

void ServidorSocket::inicia()
{
    if (!mEscuchando)
    {
        mEscuchando = listen(QHostAddress::Any, mPuerto);
    }
}

void ServidorSocket::setPuerto(quint16 puerto)
{
    mPuerto = puerto;
}

QList<ClienteSocket *> ServidorSocket::clientes() const
{
    return mClientes;
}

void ServidorSocket::enviaMensaje(int enumeracion, const QString &mensaje, ClienteSocket *cliente)
{
    cliente->enviaMensaje(enumeracion, mensaje);
}

void ServidorSocket::eliminaCliente(ClienteSocket *socket)
{
    mClientes.removeOne(socket);
    delete socket;
}

void ServidorSocket::desconectaClientes()
{
    const int nClientes = mClientes.size();
    for (int iCliente = 0; iCliente < nClientes; ++iCliente)
    {
        mClientes.at(iCliente)->disconnectFromHost();
    }
}

void ServidorSocket::incomingConnection(qintptr handle)
{
    ClienteSocket *cliente = makeCliente(handle);
    mClientes.append(cliente);
    emit clienteConectado(cliente);
}

ClienteSocket *ServidorSocket::makeCliente(qintptr handle)
{
    ClienteSocket *cliente = new ClienteSocket;
    cliente->setSocketDescriptor(handle);

    connect(cliente, &ClienteSocket::desconectado, this, [&](ClienteSocket *socket)
    {
        emit clienteDesconectado(socket);
    });

    connect(cliente, &ClienteSocket::mensajeRecibido, this,
            [&](int enumeracion, const QString &mensaje, ClienteSocket *socket)
    {
        emit mensajeRecibido(enumeracion, mensaje, socket);
    });

    return cliente;
}
