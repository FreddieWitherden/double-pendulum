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
