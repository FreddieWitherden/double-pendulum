/*
    This file is part of Double Pendulum.
    Copyright (C) 2009–2010  Freddie Witherden

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

#ifndef DOUBLEPENDULUMWIDGET_H
#define DOUBLEPENDULUMWIDGET_H

#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include <QMap>

#include "doublependulumitem.h"
#include "doublependuluminfoitem.h"

class DoublePendulumWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DoublePendulumWidget(QWidget *parent);
    ~DoublePendulumWidget();

    void addPendulum(const QString &name, DoublePendulumItem *pendulum);
    void removePendulum(const QString &name);
    QMap<QString, DoublePendulumItem *> pendula();

    void startSim();
    void pauseSim();
    void stopSim();

    double time();
    int framesPerSecond();

    double pendulumScaleFactor();

    double scaleFactor();
    void setScaleFactor(double sf);
    double idealScaleFactor();

protected slots:
    void advanceSimulation();
    void updateFPS();
    void resizeEvent(QResizeEvent *event);

private:
    double m_pScaleFactor;
    double m_scale;

    const int m_simUpdateFreq;
    const int m_fpsUpdateFreq;

    QTimer *m_simTimer;
    QTimer *m_fpsTimer;
    double m_simTime;
    QTime m_lastUpdate;

    int m_numFrames;
    int m_framesPerSecond;

    bool m_isPaused;

    QMap<QString, DoublePendulumItem *> m_pendula;

    DoublePendulumInfoItem *m_info;
};

#endif // DOUBLEPENDULUMWIDGET_H
