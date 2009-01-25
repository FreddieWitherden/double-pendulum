#include "doublependulum.h"

#include <cmath>
#include <cassert>

DoublePendulum::DoublePendulum(const Pendulum& upper, const Pendulum& lower,
                               double dt, double g) :
    m_theta1(upper.theta),
    m_omega1(upper.omega),
    m_l1(upper.l), m_m1(upper.m),
    m_theta2(lower.theta),
    m_omega2(lower.omega),
    m_l2(lower.l), m_m2(lower.m),
    m_dt(dt), m_g(g), m_time(0.0)
{
}

DoublePendulum::~DoublePendulum()
{
}

void DoublePendulum::update(double newTime)
{
    assert(newTime >= m_time);

    do
    {
        const double yin[NUM_EQNS] = { m_theta1, m_omega1, m_theta2, m_omega2 };
        double yout[NUM_EQNS];

        solveODEs(yin, yout);

        m_theta1 = yout[THETA_1];
        m_omega1 = yout[OMEGA_1];
        m_theta2 = yout[THETA_2];
        m_omega2 = yout[OMEGA_2];
    } while ((m_time += m_dt) < newTime);
}

void DoublePendulum::derivs(const double *yin, double *dydx)
{
    // Delta is θ2 - θ1
    const double delta = yin[THETA_2] - yin[THETA_1];

    // `Big-M' is the total mass of the system, m1 + m2;
    const double M = m_m1 + m_m2;

    // Denominator expression for ω1
    double den = M*m_l1 - m_m2*m_l1*cos(delta)*cos(delta);

    // dθ/dt = ω, by definition
    dydx[THETA_1] = yin[OMEGA_1];

    // Compute ω1
    dydx[OMEGA_1] = (m_m2*m_l1*yin[OMEGA_1]*yin[OMEGA_1]*sin(delta)*cos(delta)
                  + m_m2*m_g*sin(yin[THETA_2])*cos(delta)
                  + m_m2*m_l2*yin[OMEGA_2]*yin[OMEGA_2]*sin(delta)
                  - M*m_g*sin(yin[THETA_1])) / den;

    // Again, dθ/dt = ω for θ2 as well
    dydx[THETA_2] = yin[OMEGA_2];

    // Multiply den by the length ratio of the two bobs
    den *= m_l2 / m_l1;

    // Compute ω2
    dydx[OMEGA_2] = (-m_m2*m_l2*yin[OMEGA_2]*yin[OMEGA_2]*sin(delta)*cos(delta)
                  + M*m_g*sin(yin[THETA_1])*cos(delta)
                  - M*m_l1*yin[OMEGA_1]*yin[OMEGA_1]*sin(delta)
                  - M*m_g*sin(yin[THETA_2])) / den;
}
