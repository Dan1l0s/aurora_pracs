#ifndef MY_LIST_H
#define MY_LIST_H
#include <QObject>

class MyList : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString list READ getValue NOTIFY valueChanged)

private:
  QList<QString> list;

public:
  MyList();
  QString getValue();
  Q_INVOKABLE void add_string(QString new_string);
  Q_INVOKABLE void remove_string();

signals:
  void valueChanged();
};

#endif
