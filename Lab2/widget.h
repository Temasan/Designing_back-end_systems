#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <enums.h>
#include <mutex>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QPushButton *startButton() const;
    QPushButton *stopButton() const;
    QSpinBox *spinBox() const;
public slots:
    void onDataChange(QString name_phylosopher, int nowNumber, EatingState state,std::pair<int, int> numbers);
    void onPutStick(int stick, bool status, int numberPhyl);
private:
    Ui::Widget *ui;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QSpinBox *m_spinBox;
    std::mutex m_localMutex;
};

#endif // WIDGET_H
