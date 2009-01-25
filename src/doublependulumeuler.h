#ifndef DOUBLEPENDULUMEULER_H
#define DOUBLEPENDULUMEULER_H

#include "doublependulum.h"

class DoublePendulumEuler : public DoublePendulum
{
public:
    DoublePendulumEuler(const Pendulum& upper, const Pendulum& lower,
                        double dt=0.05, double g=9.81);

    const char *solverMethod();

    void solveODEs(const double *yin, double *yout);
};

#endif // DOUBLEPENDULUMEULER_H
