#include "doublependulumrk4.h"

DoublePendulumRK4::DoublePendulumRK4(const Pendulum& upper,
                                     const Pendulum& lower,
                                     double dt, double g) :
    DoublePendulum(upper, lower, dt, g)
{
}

const char *DoublePendulumRK4::solverMethod()
{
    return "Runge Kutta (RK4)";
}

void DoublePendulumRK4::solveODEs(const double *yin, double *yout)
{
    double dydx[NUM_EQNS], dydxt[NUM_EQNS], yt[NUM_EQNS];
    double k1[NUM_EQNS], k2[NUM_EQNS], k3[NUM_EQNS], k4[NUM_EQNS];

    // First step
    derivs(yin, dydx);
    for (int i = 0; i < NUM_EQNS; ++i)
    {
        k1[i] = m_dt * dydx[i];
        yt[i] = yin[i] + 0.5 * k1[i];
    }

    // Second step
    derivs(yt, dydxt);
    for (int i = 0; i < NUM_EQNS; ++i)
    {
        k2[i] = m_dt * dydxt[i];
        yt[i] = yin[i] + 0.5 * k2[i];
    }

    // Third step
    derivs(yt, dydxt);
    for (int i = 0; i < NUM_EQNS; ++i)
    {
        k3[i] = m_dt * dydxt[i];
        yt[i] = yin[i] + k3[i];
    }

    // Fourth step
    derivs(yt, dydxt);
    for (int i = 0; i < NUM_EQNS; ++i)
    {
        k4[i] = m_dt * dydxt[i];
        yout[i] = yin[i] + k1[i] / 6.0 + k2[i] / 3.0 + k3[i] / 3.0 + k4[i] / 6.0;
    }
}
