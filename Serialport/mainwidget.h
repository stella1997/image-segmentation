#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QStringList>
#include <QString>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


private slots:

    void on_openPortBtn_clicked();	//利用“转到槽”添加的槽函数声明

    void on_SendBtn_clicked();		//利用“转到槽”添加的槽函数声明

    //void on_light_clicked();

    void sleep(unsigned int msec);

    void on_Conforward_clicked();

    void on_Conback_clicked();

    void on_Conleft_clicked();

    void on_Conright_clicked();

    void on_stop_clicked();

    void on_speedup_clicked();

    void on_speeddown_clicked();

private:
    Ui::MainWidget *ui;
    QSerialPort serial;
    int k=0;
    QStringList request;
    QString result;

};

#endif // MAINWIDGET_H
