#ifndef DINNER_H
#define DINNER_H
#include <QMap>
#include <QVariant>
#include <philosopher.h>
#include <stick.h>
#include <thread>
#include <QObject>

typedef std::vector<Philosopher*> vectorPhilosophers;

/*!
 * \brief The Dinner class класс инициализации данных и запуска потоков философов.
 */
class Dinner : public QObject
{
    Q_OBJECT

public:
    explicit Dinner(QObject * parent=0);
    ~Dinner();

public slots:
    void start(bool status); //!< старт работы
    void setNumberPhylosophers(int numberPhylosophers); //!< задать номер философа
signals:
    /*!
     * \brief getPropertiesToWidget сигнал такта времени питания философа
     * \param name_phylosopher имя философа (его номер)
     * \param nowNumber текущий такт времени
     * \param state статус
     * \param sticks номера палок, которыми он кушает
     */
    void getPropertiesToWidget(QString name_phylosopher, int nowNumber, EatingState state, std::pair<int, int> sticks);
    void putStick(int stick, bool status, int numberPhyl); //!< факт взятия или отпускания палки
private:
    void init();                            //!< инициализация данных
    uint32_t m_numberPhylosophers = 0;      //!< номер философов
    vectorPhilosophers m_vectorPhilosophers;//!< вектор философов
private slots:
    /*!
     * \brief onEating философ сообщил, что так времени его питания пройден
     * \param nowtime текущий такт времени
     * \param number номер философа
     * \param eatingState статус
     * \param sticks пара палок, которыми он питается
     */
    void onEating(int nowtime, int number, EatingState eatingState, std::pair<int,int> sticks);
    /*!
     * \brief onPutStick факт взятия или отпускания палки философом
     */
    void onPutStick(int stick, bool status, int numberPhyl);
};

#endif // DINNER_H
