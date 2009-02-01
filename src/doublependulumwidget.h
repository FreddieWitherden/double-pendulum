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

#ifndef DOUBLEPENDULUMWIDGET_H
#define DOUBLEPENDULUMWIDGET_H

#include <QGraphicsView>

class DoublePendulumWidget : public QGraphicsView
{
public:
    DoublePendulumWidget(QWidget *parent);
    ~DoublePendulumWidget();

    void startSim();
    void pauseSim();
    void stopSim();

    double time();

    double pendulumScaleFactor();

protected slots:
    void timerEvent(QTimerEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    double m_pScaleFactor;
    double m_scale;

    int m_timerId;
    const int m_timeStep;
    double m_simTime;
    bool m_isPaused;
};

#endif // DOUBLEPENDULUMWIDGET_H
