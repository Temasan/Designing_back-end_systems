#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H


class Philosopher : public QObject
{
    Q_OBJECT
public:
    explicit Philosopher(QObject *parent = 0);

signals:

public slots:
};

#endif // PHILOSOPHER_H