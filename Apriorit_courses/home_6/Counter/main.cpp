#include <QCoreApplication>
#include <counter.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Counter test1(100);
    Counter test2(120);
    QObject::connect(&test1, &Counter::incremented,&test2, &Counter::acceptIncrement);
    QObject::connect(&test1, &Counter::decremented,&test2, &Counter::acceptDecrement);
    QObject::connect(&test2, &Counter::incremented,&test1, &Counter::acceptIncrement);
    QObject::connect(&test2, &Counter::decremented,&test1, &Counter::acceptDecrement);

    test1.Increment();
    std::cout << test1.m_count << std::endl;
    std::cout << test2.m_count << std::endl;
    test2.Increment();
    std::cout << test1.m_count << std::endl;
    std::cout << test2.m_count << std::endl;
    test1.Decrement();
    std::cout << test1.m_count << std::endl;
    std::cout << test2.m_count << std::endl;
    test2.Decrement();
    std::cout << test1.m_count << std::endl;
    std::cout << test2.m_count << std::endl;

    return a.exec();
}
