#ifndef SERVIDORWIDGET_H
#define SERVIDORWIDGET_H

#include <QWidget>

namespace Ui {
class ServidorWidget;
}

class ServidorSocket;

class ServidorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ServidorWidget(QWidget *parent = nullptr);
    ~ServidorWidget();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_encenderButton_clicked();
    void on_clientesConectadosListwidget_clicked(const QModelIndex &index);
private:
    Ui::ServidorWidget *ui;
    ServidorSocket *mServidorSocket;
    ServidorSocket *makeServidor();
};

#endif // SERVIDORWIDGET_H
