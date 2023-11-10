#ifndef MY_COUNTER_H
#define MY_COUNTER_H
#include <QObject>

class MyCounter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ getValue NOTIFY valueChanged)
private:
    int counter;

public:
    MyCounter();
    int getValue();
    Q_INVOKABLE void increment();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void printCounter();

signals:
    void valueChanged();
};

#endif
