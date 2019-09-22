#include "servidorwidget.h"
#include "ui_servidorwidget.h"
#include "servidorsocket.h"
#include "clientesocket.h"
#include "enumeraciones.h"
#include <QInputDialog>

ServidorWidget::ServidorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServidorWidget)
{
    ui->setupUi(this);
    mServidorSocket = makeServidor();
    ui->frame2->setDisabled(true);
    ui->frame3->setDisabled(true);
    ui->plaintextedit->setReadOnly(true);
}

ServidorWidget::~ServidorWidget()
{
    delete ui;
}

void ServidorWidget::closeEvent(QCloseEvent *event)
{
    mServidorSocket->desconectaClientes();
    QWidget::closeEvent(event);
}

void ServidorWidget::on_encenderButton_clicked()
{
    quint16 puerto = quint16(ui->puertoDeEscuchaLineedit->text().toUInt());

    if (puerto == 0)
    {
        return;
    }

    mServidorSocket->setPuerto(puerto);
    mServidorSocket->inicia();
    ui->frame2->setEnabled(true);
    ui->frame3->setEnabled(true);
}

ServidorSocket *ServidorWidget::makeServidor()
{
    ServidorSocket *servidor = new ServidorSocket(this);

    connect(servidor, &ServidorSocket::clienteConectado, this, [&](ClienteSocket *socket)
    {
        ui->clientesConectadosListwidget->addItem(socket->id());
    });

    connect(servidor, &ServidorSocket::clienteDesconectado, this, [&](ClienteSocket *socket)
    {
        const int count = ui->clientesConectadosListwidget->count();
        for (int ix = 0; ix < count; ++ix)
        {
            if (ui->clientesConectadosListwidget->item(ix)->text() == socket->id())
            {
                delete ui->clientesConectadosListwidget->item(ix);
                //mServidorSocket->eliminaCliente(socket);
                return;
            }
        }
    });

    connect(servidor, &ServidorSocket::mensajeRecibido, this,
            [&](int enumeracion, const QString &mensaje, ClienteSocket *socket)
    {
        (void) socket;
        if (enumeracion == InfoQuery)
        {
            ui->plaintextedit->appendPlainText(mensaje);
        }
    });

    return servidor;
}

void ServidorWidget::on_clientesConectadosListwidget_clicked(const QModelIndex &index)
{
    ClienteSocket *cliente = mServidorSocket->clientes().at(index.row());
    QString mensaje = QInputDialog::getText(this, "Mensaje", "Mensaje");
    if (!mensaje.isEmpty())
    {
        cliente->enviaMensaje(InfoResponse, mensaje);
    }
}
