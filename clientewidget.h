#ifndef CLIENTEWIDGET_H
#define CLIENTEWIDGET_H

#include <QWidget>

namespace Ui
{
class ClienteWidget;
}

class ClienteSocket;

class ClienteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClienteWidget(QWidget *parent = nullptr);
    ~ClienteWidget() override;
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_conectarButton_clicked();
    void on_enviarButton_clicked();
private:
    Ui::ClienteWidget *ui;
    ClienteSocket *mClienteSocket;
    ClienteSocket *makeSocket();
};

#endif // CLIENTEWIDGET_H
