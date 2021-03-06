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

#include "doublependulumwidget.h"
#include "doublependulumitem.h"

#include <QGraphicsScene>

DoublePendulumWidget::DoublePendulumWidget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scale(10.0)
    , m_simUpdateFreq(1000 / 100)
    , m_fpsUpdateFreq(1000 / 10)
    , m_framesPerSecond(0)
    , m_isPaused(false)
    , m_info(new DoublePendulumInfoItem)
{
    // Create a scene to store the pendulums
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);

    // Hide the info item and add it to the scene on top of the pendula
    m_info->hide();
    m_info->setZValue(1.0);
    scene->addItem(m_info);

    // Create a timer to update the simulation
    m_simTimer = new QTimer(this);
    connect(m_simTimer, SIGNAL(timeout()), this, SLOT(advanceSimulation()));

    // Create a timer to monitor the frame rate of the simulation
    m_fpsTimer = new QTimer(this);
    connect(m_fpsTimer, SIGNAL(timeout()), this, SLOT(updateFPS()));

    // Init the last update time
    m_lastUpdate.start();
}

DoublePendulumWidget::~DoublePendulumWidget()
{
}

void DoublePendulumWidget::addPendulum(const QString &name, DoublePendulumItem *pendulum)
{
    scene()->addItem(pendulum);
    pendulum->setPos(0.0, 0.0);
    pendulum->updateScale(m_pScaleFactor);

    m_pendula[name] = pendulum;
}

void DoublePendulumWidget::removePendulum(const QString &name)
{
    scene()->removeItem(m_pendula[name]);

    m_pendula.remove(name);
}

QMap<QString, DoublePendulumItem *> DoublePendulumWidget::pendula()
{
    return m_pendula;
}

void DoublePendulumWidget::startSim()
{
    // Reset the simulation and actual times
    m_simTime = 0.0;
    m_lastUpdate.restart();

    // Reset the frame count
    m_numFrames = 0;

    // Start of all of the pendulums
    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        pendulum->start();
    }

    // Update the info box with the current set of pendulums
    m_info->setPendula(m_pendula);
    m_info->show();

    // Start the timers
    m_simTimer->start(m_simUpdateFreq);
    m_fpsTimer->start(m_fpsUpdateFreq);
}

void DoublePendulumWidget::pauseSim()
{
    // If we are not paused, pause ourself
    if (!m_isPaused)
    {
        m_isPaused = true;

        // Stop the timers
        m_simTimer->stop();
        m_fpsTimer->stop();
    }
    // If we are paused, unpause ourself
    else
    {
        m_isPaused = false;

        // Restart the timers
        m_simTimer->start(m_simUpdateFreq);
        m_fpsTimer->start(m_fpsUpdateFreq);

        // Reset the last update time
        m_lastUpdate.restart();
    }
}

void DoublePendulumWidget::stopSim()
{
    // Stop the timers
    m_simTimer->stop();
    m_fpsTimer->stop();

    // Stop all of the pendulums
    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        pendulum->stop();
    }

    // We are not paused
    m_isPaused = false;

    // Hide the info box as it is meaningless when the simulation is stopped
    m_info->hide();

    // Request a repaint to clear ourself
    scene()->update();
}

double DoublePendulumWidget::time()
{
    return m_simTime;
}

int DoublePendulumWidget::framesPerSecond()
{
    return m_framesPerSecond;
}

double DoublePendulumWidget::pendulumScaleFactor()
{
    return m_pScaleFactor;
}

double DoublePendulumWidget::scaleFactor()
{
    return m_scale;
}

void DoublePendulumWidget::setScaleFactor(double sf)
{
    // Update the scale
    m_scale = sf;

    // Compute the new pendulum scale factor
    m_pScaleFactor = qMin(sceneRect().width(), sceneRect().height()) / m_scale;

    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        pendulum->updateScale(m_pScaleFactor);
    }

    // Update the scene to force all of the pendula to redraw themselves
    update();
}

double DoublePendulumWidget::idealScaleFactor()
{
    double largestPendulm = 0;

    // Loop over each pendulum looking for the largest
    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        // Get the bounds of the pendulum
        QRectF bounds = pendulum->boundingRect();

        // Get its unscale size; height() would also work here
        double pendulumSize = bounds.width() / pendulumScaleFactor();

        largestPendulm = qMax(pendulumSize, largestPendulm);
    }

    // Subtract a bit to account for the bob on the end - magic number alert
    largestPendulm -= 0.2;

    return largestPendulm;
}

void DoublePendulumWidget::advanceSimulation()
{
    // Advance the simulation forward by the amount of time that has passed
    m_simTime += m_lastUpdate.elapsed();

    // Reset the last update time
    m_lastUpdate.restart();

    // Increment the frame count
    ++m_numFrames;

    // Update the scene
    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        pendulum->updateTime(m_simTime);
    }

    m_info->update();
}

void DoublePendulumWidget::updateFPS()
{
    // Update the number of frames per second being rendered
    m_framesPerSecond = m_numFrames * 10;

    // Reset the number of frames
    m_numFrames = 0;
}

void DoublePendulumWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    // Make the scene ever so slightly smaller than the view
    QRectF newSceneRect(-width() / 2.0, -height() / 2.0, width(), height());
    newSceneRect.adjust(0.0, 0.0, -5.0, -5.0);

    // Ensure the range of the smaller axis is between 0..m_scale
    m_pScaleFactor = qMin(newSceneRect.width(), newSceneRect.height()) / m_scale;

    foreach (DoublePendulumItem *pendulum, m_pendula)
    {
        pendulum->updateScale(m_pScaleFactor);
    }

    // Update the scene rect
    setSceneRect(newSceneRect);

    // Keep the info box in the top left of the scene
    m_info->setPos(sceneRect().topLeft() + QPointF(20.0, 20.0));
}
