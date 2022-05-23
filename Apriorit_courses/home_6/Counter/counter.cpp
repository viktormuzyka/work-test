#include "counter.h"
#include <iostream>
Counter::Counter(int startValue):m_count(startValue)
{
}
 int Counter::getCount() const
 {
     return this->m_count;
 }
int Counter::Decrement()
{
   --(this->m_count);
    emit this->decremented();
    return this->m_count;
}

int Counter::Increment()
{
   ++(this->m_count);
    emit this->incremented();
    return this->m_count;
}

int Counter::acceptDecrement()
{
    this->m_count--;
    return this->m_count ;
}
int Counter::acceptIncrement()
{
    this->m_count++;
    return this->m_count ;

}
