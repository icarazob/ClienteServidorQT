#include "clientewidget.h"
#include "ui_clientewidget.h"
#include "clientesocket.h"
#include "enumeraciones.h"
#include <QDebug>

ClienteWidget::ClienteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClienteWidget)
{
    ui->setupUi(this);
    mClienteSocket = makeSocket();
    ui->frame2->setDisabled(true);
    ui->frame3->setDisabled(true);
    ui->plaintextedit->setReadOnly(true);
}

ClienteWidget::~ClienteWidget()
{
    delete ui;
}

void ClienteWidget::closeEvent(QCloseEvent *event)
{
    mClienteSocket->disconnectFromHost();
    QWidget::closeEvent(event);
}

void ClienteWidget::on_conectarButton_clicked()
{
    QString ipServidor = ui->ipServidorLineedit->text();
    quint16 puertoServidor = quint16(ui->puertoServidorLineedit->text().toUInt());

    if (ipServidor.isEmpty())
    {
        return;
    }
    if (puertoServidor == 0)
    {
        return;
    }

    mClienteSocket->setDireccionDelServidor(ipServidor);
    mClienteSocket->setPuertoDelServidor(puertoServidor);
    mClienteSocket->conectaConElServidor();
    ui->frame2->setEnabled(true);
    ui->frame3->setEnabled(true);
}

void ClienteWidget::on_enviarButton_clicked()
{
    mClienteSocket->enviaMensaje(InfoQuery, ui->enviarMensajeLineedit->text());
}

ClienteSocket *ClienteWidget::makeSocket()
{
    ClienteSocket *socket = new ClienteSocket(this);

    connect(socket, &ClienteSocket::mensajeRecibido, this,
            [&](int enumeracion, const QString &mensaje, ClienteSocket *socket)
    {
        (void) socket;
        if (enumeracion == InfoResponse)
        {
            ui->plaintextedit->appendPlainText(mensaje);
        }
    });

    return socket;
}
