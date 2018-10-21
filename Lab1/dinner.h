#ifndef DINNER_H
#define DINNER_H
#include <QMap>
#include <QVariant>
#include <philosopher.h>
#include <stick.h>
#include <thread>
#include <QObject>
#include <atomic>

typedef std::vector<std::thread*> vectorThreads;
//typedef std::vector<QString> vectorNames;
typedef std::vector<std::shared_ptr<Stick>> vectorStics;
typedef std::vector<Philosopher*> vectorPhilosophers;

class Dinner : public QObject
{
    Q_OBJECT

public:
    explicit Dinner(QObject * parent=0);
    ~Dinner();
    uint32_t getNumberPhylosophers() const;

public slots:
    void start(bool status);
    void setNumberPhylosophers(int numberPhylosophers);
signals:
    void getPropertiesToWidget(QString name_phylosopher, int nowNumber, EatingState state);
private:
    void init();
    uint32_t m_numberPhylosophers = 0;
    vectorThreads m_vectorThreads;
    //vectorNames m_names;
    std::vector<Stick> m_vectorStics;
    vectorPhilosophers m_vectorPhilosophers;
    ptrMutex m_ptrMutex;
    QTimer *m_timer;
private slots:
    void onEating(int nowtime, int number, EatingState eatingState);
};

#endif // DINNER_H
