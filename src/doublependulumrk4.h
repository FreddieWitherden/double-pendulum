/*
    This file is part of Double Pendulum.
    Copyright (C) 2009  Freddie Witherden

    Double Pendulum is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Double Pendulum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Double Pendulum; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef DOUBLEPENDULUMRK4_H
#define DOUBLEPENDULUMRK4_H

#include "doublependulum.h"

class DoublePendulumRK4 : public DoublePendulum
{
public:
    DoublePendulumRK4(const Pendulum& upper, const Pendulum& lower,
                      double dt=0.005, double g=9.81);

    const char *solverMethod();

    void solveODEs(const double *yin, double *yout);
};

#endif // DOUBLEPENDULUMRK4_H
