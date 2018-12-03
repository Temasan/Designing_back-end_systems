#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_startButton = ui->pushButton;
    m_stopButton = ui->pushButton_2;
    m_spinBox = ui->spinBox;
}

Widget::~Widget()
{
    delete ui;
}

QPushButton *Widget::startButton() const
{
    return m_startButton;
}

QPushButton *Widget::stopButton() const
{
    return m_stopButton;
}

QSpinBox *Widget::spinBox() const
{
    return m_spinBox;
}

QString getText(QString name_phylosopher, int nowNumber, EatingState state, std::pair<int, int> numbers){
    return QString(QDateTime::currentDateTime().toString("hh:mm:ss.z") + ": Философ " + name_phylosopher +(state==EatingState::FinishEateing ? " закончил": " кушает " + QString::number(nowNumber)) +
                   " ("+QString::number(numbers.first)+","+QString::number(numbers.second) +")");
}
QString getTextWhenPutStick(int stick, bool status, int numberPhyl){
    return QString(QDateTime::currentDateTime().toString("hh:mm:ss.z") +": Палка " + QString::number(stick) + QString(status?" Захвачена":" Отпущена") + " Философом " + QString::number(numberPhyl));
}
void Widget::onDataChange(QString name_phylosopher, int nowNumber, EatingState state, std::pair<int, int> numbers){
    m_localMutex.lock();
    ui->textEdit->setText(ui->textEdit->toPlainText() + "\n" + getText(name_phylosopher,nowNumber,state,numbers));
    m_localMutex.unlock();
}
void Widget::onPutStick(int stick, bool status, int numberPhyl){
    m_localMutex.lock();
    ui->textEdit->setText(ui->textEdit->toPlainText() + "\n" + getTextWhenPutStick(stick,  status, numberPhyl));
    m_localMutex.unlock();
}
