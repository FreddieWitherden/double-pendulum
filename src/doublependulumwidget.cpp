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

#include "doublependulumwidget.h"
#include "doublependulumitem.h"

#include <QGraphicsScene>

DoublePendulumWidget::DoublePendulumWidget(QWidget *parent) :
    QGraphicsView(parent), m_scale(10.0), m_timerId(0), m_timeStep(1000 / 60),
    m_isPaused(false)
{
    // Create a scene to store the pendulums
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);
}

DoublePendulumWidget::~DoublePendulumWidget()
{
    delete scene();
}

void DoublePendulumWidget::startSim()
{
    // Reset the simulation time
    m_simTime = 0.0;

    // Start of all of the pendulums
    foreach (QGraphicsItem *item, scene()->items())
    {
        // If the item is a pendulum
        if (DoublePendulumItem *pendulum = qgraphicsitem_cast<DoublePendulumItem *>(item))
        {
            pendulum->start();
        }
    }

    // Start the timer
    m_timerId = startTimer(m_timeStep);
}

void DoublePendulumWidget::pauseSim()
{
    // Invert the current pause status
    m_isPaused = !m_isPaused;
}

void DoublePendulumWidget::stopSim()
{
    // Stop/kill the timer
    killTimer(m_timerId);

    // Stop all of the pendulums
    foreach (QGraphicsItem *item, scene()->items())
    {
        // If the item is a pendulum
        if (DoublePendulumItem *pendulum = qgraphicsitem_cast<DoublePendulumItem *>(item))
        {
            pendulum->stop();
        }
    }

    // We are not paused
    m_isPaused = false;

    // Request a repaint to clear ourself
    update();
}

double DoublePendulumWidget::time()
{
    return m_simTime;
}

double DoublePendulumWidget::pendulumScaleFactor()
{
    return m_scaleFactor;
}

void DoublePendulumWidget::timerEvent(QTimerEvent *)
{
    // Make sure we are not currently paused
    if (m_isPaused)
    {
        return;
    }

    // Advance the time forward
    m_simTime += m_timeStep;

    // Update the scene
    scene()->advance();
}

void DoublePendulumWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    if (height() > width())
    {
        m_scaleFactor = width() / 10.0;
    }
    else
    {
        m_scaleFactor = height() / 10.0;
    }

    foreach (QGraphicsItem *item, scene()->items())
    {
        // If the item is a pendulum
        if (DoublePendulumItem *pendulum = qgraphicsitem_cast<DoublePendulumItem *>(item))
        {
            pendulum->resetMatrix();
            pendulum->scale(m_scaleFactor, m_scaleFactor);
        }
    }
}
