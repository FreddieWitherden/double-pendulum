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

#ifndef DOUBLEPENDULUMITEM_H
#define DOUBLEPENDULUMITEM_H

#include <QColor>
#include <QGraphicsItem>

#include "doublependulum.h"
#include "doublependulumeuler.h"
#include "doublependulumrk4.h"

#include "doublependulumwidget.h"

class DoublePendulumItem : public QGraphicsItem
{
public:
    DoublePendulumItem(DoublePendulumWidget *pendulumWidget);
    ~DoublePendulumItem();

    void start();
    void stop();

    Pendulum& upper();
    Pendulum& lower();

    QString solver();
    void setSolver(const QString& solver);

    double dt();
    void setDt(double dt);

    double g();
    void setG(double g);

    QColor upperColour();
    void setUpperColour(const QColor& colour);

    QColor lowerColour();
    void setLowerColour(const QColor& colour);

    int opacity();
    void setOpacity(int opacity);

    QRectF boundingRect() const;

    int type() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual void advance(int phase);

    enum
    {
        Type = UserType + 1
    };

private:
    DoublePendulumWidget *m_pendulumView;

    DoublePendulum *m_pendulum;

    QString m_solver;
    double m_dt;
    double m_g;

    /**
     * Initial states of the upper and lower pendulums.
     */
    Pendulum m_upper, m_lower;

    QColor m_upperColour;
    QColor m_lowerColour;
    int m_opacity;
};

Q_DECLARE_METATYPE(DoublePendulumItem*);

#endif // DOUBLEPENDULUMITEM_H
