#include "my_counter.h"
#include <QDebug>

MyCounter::MyCounter()
{
   counter = 0;
}
int MyCounter::getValue()
{
   return counter;
}
void MyCounter::increment()
{
   counter++;
   emit valueChanged();
}
void MyCounter::reset()
{
   counter = 0;
   emit valueChanged();
}
void MyCounter::printCounter()
{
   qDebug() << "Counter value: " << counter;
}
