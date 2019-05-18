#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QTime>
#include "QPixmap"
#include "QPalette"
#include "QBrush"
#include <QTextEdit>
#include <QString>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{

    ui->setupUi(this);
    setWindowTitle(tr("果果的控制板"));
    //QPixmap Pixmap("/Users/sunyage/Pictures/back.png");
    //QPalette palette;
    //palette.setBrush(backgroundRole(),QBrush(Pixmap));

    //setPalette(palette);
    //setFixedSize(800, 500);

    //on_hSlider_playSpeed_valueChanged(5);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_openPortBtn_clicked()
{
    if(ui->portNameComboBox->isEnabled())
    {
        ui->openPortBtn->setText("ClosePort");		//按下“OpenPort”后，按键显示为“ClosePort”
        ui->portNameComboBox->setDisabled(true);	//按下“OpenPort”后，禁止再修改COM口
        serial.setPortName(ui->portNameComboBox->currentText());	//设置COM口
        serial.setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
        serial.setDataBits(QSerialPort::Data8);		//数据位为8位
        serial.setFlowControl(QSerialPort::NoFlowControl);//无流控制
        serial.setParity(QSerialPort::NoParity);	//无校验位
        serial.setStopBits(QSerialPort::OneStop);	//一位停止位
        serial.close();					//先关串口，再打开，可以保证串口不被其它函数占用。
        if(serial.open(QIODevice::ReadWrite))		//以可读写的方式打开串口
        {
            connect(&serial,SIGNAL(readyRead()),this,SLOT(read_Com()));	//把串口的readyRead()信号绑定到read_Com()这个槽函数上
        }
        }
    else {
        ui->openPortBtn->setText("OpenPort");		//按下“ClosePort”后，按键显示为“OpenPort”
        ui->portNameComboBox->setEnabled(true);		//按下“ClosePort”后，COM口可被修改
        serial.close();					//关串口
    }
}
void MainWidget::on_SendBtn_clicked()
{
    serial.write(ui->sendTextEdit->toPlainText().toLatin1());//以ASCII码的形式通过串口发送出去。
}


void MainWidget::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}


void MainWidget::on_Conforward_clicked()
{
    QString code="f";
    serial.write(code.toLatin1());
    QString direction="前进";
    ui->lineDirection->setText(direction);
}

void MainWidget::on_Conback_clicked()
{
    QString code="b";
    serial.write(code.toLatin1());
    QString direction="后退";
    ui->lineDirection->setText(direction);
}

void MainWidget::on_Conleft_clicked()
{
    QString code="l";
    serial.write(code.toLatin1());
    QString direction="左转";
    ui->lineDirection->setText(direction);
}

void MainWidget::on_Conright_clicked()
{
    QString code="r";
    serial.write(code.toLatin1());
    QString direction="右转";
    ui->lineDirection->setText(direction);
}

void MainWidget::on_stop_clicked()
{
    QString code="s";
    serial.write(code.toLatin1());
}

void MainWidget::on_speedup_clicked()
{
    QString code="u";
    serial.write(code.toLatin1());

}

void MainWidget::on_speeddown_clicked()
{
    QString code="d";
    serial.write(code.toLatin1());
}
