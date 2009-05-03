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

#include "doublependulumeuler.h"

DoublePendulumEuler::DoublePendulumEuler(const Pendulum& upper,
                                         const Pendulum& lower,
                                         double dt, double g):
    DoublePendulum(upper, lower, dt, g)
{
}

const char *DoublePendulumEuler::solverMethod()
{
    return "Euler";
}

void DoublePendulumEuler::solveODEs(const double *yin, double *yout)
{
    double dydx[NUM_EQNS];

    // Calculate the derivatives of the equations at time + dt
    derivs(yin, dydx);

    // Update the values of theta and omega for the two bobs
    yout[THETA_1] = yin[THETA_1] + dydx[THETA_1] * m_dt;
    yout[OMEGA_1] = yin[OMEGA_1] + dydx[OMEGA_1] * m_dt;

    yout[THETA_2] = yin[THETA_2] + dydx[THETA_2] * m_dt;
    yout[OMEGA_2] = yin[OMEGA_2] + dydx[OMEGA_2] * m_dt;
}
