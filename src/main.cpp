#include <iostream>

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "doublependulumrk4.h"

int main(int argc, char *argv[])
{
    //DoublePendulumRK4 e(0.1, 0, 9.8, 1.0, 0, 0, 9.8, 0.00001);

    //std::cout << "t = " << e.time() << " theta = " << e.theta1() << std::endl;
    //e.update(3.14);
    //std::cout << "t = " << e.time() << " theta = " << e.theta1() << std::endl;

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
