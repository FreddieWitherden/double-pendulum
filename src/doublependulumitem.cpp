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

#include "doublependulumitem.h"

#include <QtDebug>
#include <QPainter>

#include <cmath>

DoublePendulumItem::DoublePendulumItem()
    : m_pendulum(0)
{
}

DoublePendulumItem::~DoublePendulumItem()
{
    if (m_pendulum)
    {
        stop();
    }
}

void DoublePendulumItem::start()
{
    // Create the actual pendulum object
    if (m_solver == "Euler")
    {
        m_pendulum = new DoublePendulumEuler(upper(), lower(), m_dt, m_g);
    }
    else if (m_solver == "Runge Kutta (RK4)")
    {
        m_pendulum = new DoublePendulumRK4(upper(), lower(), m_dt, m_g);
    }
}

void DoublePendulumItem::stop()
{
    delete m_pendulum;
    m_pendulum = 0;
}

Pendulum& DoublePendulumItem::upper()
{
    return m_upper;
}

Pendulum& DoublePendulumItem::lower()
{
    return m_lower;
}

QString DoublePendulumItem::solver()
{
    return m_solver;
}

void DoublePendulumItem::setSolver(const QString& solver)
{
    m_solver = solver;
}

double DoublePendulumItem::dt()
{
    return m_dt;
}

void DoublePendulumItem::setDt(double dt)
{
    m_dt = dt;
}

double DoublePendulumItem::g()
{
    return m_g;
}

void DoublePendulumItem::setG(double g)
{
    m_g = g;
}

QColor DoublePendulumItem::upperColour()
{
    return m_upperColour;
}

void DoublePendulumItem::setUpperColour(const QColor& colour)
{
    m_upperColour = colour;
}

QColor DoublePendulumItem::lowerColour()
{
    return m_lowerColour;
}

void DoublePendulumItem::setLowerColour(const QColor& colour)
{
    m_lowerColour = colour;
}

int DoublePendulumItem::opacity()
{
    return m_opacity;
}

void DoublePendulumItem::setOpacity(int opacity)
{
    m_opacity = opacity;
}

QRectF DoublePendulumItem::boundingRect() const
{
    if (!m_pendulum)
    {
        return QRectF(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
        const double max = (m_pendulum->l1() + m_pendulum->l2() + 0.2)
                          * m_scale;

        return QRectF(QPointF(-max, -max), QPointF(max, max));
    }
}

int DoublePendulumItem::type() const
{
    return Type;
}

void DoublePendulumItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
{
    // Only paint if the pendulum is running
    if (!m_pendulum)
    {
        return;
    }

    painter->scale(m_scale, m_scale);

    // Location of the upper bob
    QPointF upperBob(m_pendulum->l1() * sin(m_pendulum->theta1()),
                     m_pendulum->l1() * cos(m_pendulum->theta1()));

    // Location of the power bob
    QPointF lowerBob(upperBob.x() + m_pendulum->l2() * sin(m_pendulum->theta2()),
                     upperBob.y() + m_pendulum->l2() * cos(m_pendulum->theta2()));

    QPointF linePoints[] =
    {
        QPointF(0.0, 0.0),
        upperBob,
        lowerBob
    };

    // First come the connecting lines
    QColor lineColour = Qt::black;
    lineColour.setAlphaF(opacity() / 100.0);

    painter->setPen(QPen(lineColour, 0.04, Qt::SolidLine, Qt::RoundCap));
    painter->drawPolyline(linePoints, 3);

    painter->setPen(Qt::NoPen);

    // Next comes the upper bob
    QColor actualUpperColour = m_upperColour;
    actualUpperColour.setAlphaF(m_opacity / 100.0);

    painter->setBrush(QBrush(actualUpperColour));
    painter->drawEllipse(upperBob, 0.2, 0.2);

    // Finally the lower bob
    QColor actualLowerColour = m_lowerColour;
    actualLowerColour.setAlphaF(m_opacity / 100.0);

    painter->setBrush(QBrush(actualLowerColour));
    painter->drawEllipse(lowerBob, 0.2, 0.2);
}

void DoublePendulumItem::updateScale(double newScale)
{
    m_scale = newScale;
}

void DoublePendulumItem::updateTime(double newTime)
{
    // Actual time (s as opposed to ms)
    double actualTime = newTime / 1000.0;

    // Update the pendulum
    if (actualTime > m_pendulum->time())
    {
        m_pendulum->update(actualTime);
    }

    prepareGeometryChange();
}
