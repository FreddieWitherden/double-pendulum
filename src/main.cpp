/*
    This file is part of Double Pendulum.
    Copyright (C) 2009  Freddie Witherden

    Double Pendulum is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Double Pendulum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Double Pendulum; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
