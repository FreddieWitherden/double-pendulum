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
    QGraphicsView(parent), m_scale(10.0),
    m_isPaused(false)
{
    // Create a scene to store the pendulums
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);

    // Create a timer to update the simulation
    m_simTimer = new QTimer(this);
    connect(m_simTimer, SIGNAL(timeout()), this, SLOT(advanceSimulation()));

    // Init the last update time
    m_lastUpdate.start();
}

DoublePendulumWidget::~DoublePendulumWidget()
{
    delete scene();
    delete m_simTimer;
}

void DoublePendulumWidget::startSim()
{
    // Reset the simulation and actual times
    m_simTime = 0.0;
    m_lastUpdate.restart();

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
    m_simTimer->start();
}

void DoublePendulumWidget::pauseSim()
{
    // If we are not paused, pause ourself
    if (!m_isPaused)
    {
        m_isPaused = true;
    }
    // If we are paused, unpause ourself
    else
    {
        m_isPaused = false;

        // Reset the last update time
        m_lastUpdate.restart();
    }
}

void DoublePendulumWidget::stopSim()
{
    // Stop the timer
    m_simTimer->stop();

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
    return m_pScaleFactor;
}

void DoublePendulumWidget::advanceSimulation()
{
    // Make sure we are not currently paused
    if (m_isPaused)
    {
        return;
    }

    // Advance the simulation forward by the amount of time that has passed
    m_simTime += m_lastUpdate.elapsed();

    // Reset the last update time
    m_lastUpdate.restart();

    // Update the scene
    scene()->advance();
}

void DoublePendulumWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    // Make the scene ever so slightly smaller than the view
    QRectF newSceneRect(-width() / 2.0, -height() / 2.0, width(), height());
    newSceneRect.adjust(0.0, 0.0, -5.0, -5.0);

    // Ensure the range of the smaller axis is between 0..m_scale
    m_pScaleFactor = qMin(newSceneRect.width(), newSceneRect.height()) / m_scale;

    // Update the scene rect
    setSceneRect(newSceneRect);
}
