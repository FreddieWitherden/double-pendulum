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

#ifndef DOUBLEPENDULUM_H
#define DOUBLEPENDULUM_H

struct Pendulum
{
    Pendulum()
        : theta(0.0), omega(0.0), l(0.0), m(0.0)
    {
    }

    Pendulum(double _theta, double _omega, double _l, double _m)
        : theta(_theta), omega(_omega), l(_l), m(_m)
    {
    }

    double theta;
    double omega;
    double l;
    double m;
};

class DoublePendulum
{
public:
    DoublePendulum(const Pendulum& upper, const Pendulum& lower,
                   double dt=0.005, double g=9.81);

    virtual ~DoublePendulum();

    /**
     * Advances the equation in steps of m_dt until newTime is reached.
     */
    void update(double newTime);

    double theta1()
    {
        return m_theta1;
    }

    double omega1()
    {
        return m_omega1;
    }

    double m1()
    {
        return m_m1;
    }

    double l1()
    {
        return m_l1;
    }

    double theta2()
    {
        return m_theta2;
    }

    double omega2()
    {
        return m_omega2;
    }

    double m2()
    {
        return m_m2;
    }

    double l2()
    {
        return m_l2;
    }

    double time()
    {
        return m_time;
    }

    double initEnergy() const
    {
        return m_initEnergy;
    }

    double energy() const;

    /**
     * Returns a string representation of the solver method used.
     */
    virtual const char *solverMethod() = 0;

protected:
    /**
     * The list of motion ODE which must be solved in order to numerically
     * evaluate the double pendulum system with respect to time.
     */
    enum
    {
        THETA_1,
        OMEGA_1,
        THETA_2,
        OMEGA_2,
        NUM_EQNS
    };

    /**
     * Given theta and omega for the upper- and lower-bobs this method computes
     * the numeric derivatives of each one.
     */
    void derivs(const double *yin, double *dydx);

    /**
     * Called to solve the equations of motion for the system by advancing
     * theta and omega by one step (this->m_dt).
     *
     * Since there are various ways of doing this the exact implementation is
     * left up to sub-classes.
     */
    virtual void solveODEs(const double *yin, double *yout) = 0;

    /**
     * Angle of the first pendulum from the vertical (in rad).
     */
    double m_theta1;

    /**
     * Angular acceleration of the first pendulum (dθ/dt).
     */
    double m_omega1;

    /**
     * Length of the first pendulum (in m).
     */
    const double m_l1;

    /**
     * Mass of the first pendulum (in kg).
     */
    const double m_m1;

    /**
     * Angle of the second pendulum from the vertical (in rad).
     */
    double m_theta2;

    /**
     * Angular acceleration of the second pendulum (dθ/dt).
     */
    double m_omega2;

    /**
     * Length of the second pendulum (in m).
     */
    const double m_l2;

    /**
     * Mass of the second pendulum (in m).
     */
    const double m_m2;

    /**
     * Step size to take when numerically solving the ODE.
     */
    const double m_dt;

    /**
     * Acceleration due to gravity (usually 9.81 ms^-2).
     */
    const double m_g;

    /**
     * Current time for which omega and theta are evaluated for.
     */
    double m_time;

    /**
     * Initial mechanical energy
     */
    double m_initEnergy;
};

#endif // DOUBLEPENDULUM_H
