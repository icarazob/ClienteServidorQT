#include <QApplication>
#include "servidorwidget.h"
#include "clientewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    ServidorWidget *servidor = new ServidorWidget;
    ClienteWidget *cliente = new ClienteWidget;
    servidor->show();
    cliente->show();
    return a.exec();
}
