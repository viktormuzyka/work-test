#ifndef COUNTER_H
#define COUNTER_H
#include <QObject>

class Counter:public QObject {
    Q_OBJECT
public:
    Counter(int startValue);
    int Increment();
    int Decrement();
    int getCount() const;
 public slots:
    int acceptIncrement();
    int acceptDecrement();

signals:
    void incremented();
    void decremented();
public:
    int m_count;
};

#endif // COUNTER_H
