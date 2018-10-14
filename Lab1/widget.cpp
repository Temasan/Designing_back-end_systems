#include "widget.h"
#include "ui_widget.h"

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

QString getText(QString name_phylosopher, int nowNumber, EatingState state){
    return QString("Философ " + name_phylosopher + " кушает уже " + QString::number(nowNumber) +
                   (state==EatingState::FinishEateing ? ". Закончил кушать" : ". Продолжает есть"));
}

void Widget::onDataChange(QString name_phylosopher, int nowNumber, EatingState state){
    ui->textEdit->setText(ui->textEdit->toPlainText() + "\n" + getText(name_phylosopher,nowNumber,state));
}
