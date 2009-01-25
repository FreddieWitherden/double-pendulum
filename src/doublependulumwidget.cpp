#include "doublependulumwidget.h"
#include "doublependulumitem.h"

#include <QGraphicsScene>

DoublePendulumWidget::DoublePendulumWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0), timeStep(1000 / 60), isPaused(false)
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
    simTime = 0.0;

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
    timerId = startTimer(timeStep);
}

void DoublePendulumWidget::pauseSim()
{
    // Invert the current pause status
    isPaused = !isPaused;
}

void DoublePendulumWidget::stopSim()
{
    // Stop/kill the timer
    killTimer(timerId);

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
    isPaused = false;
    
    // Request a repaint to clear ourself
    update();
}

double DoublePendulumWidget::time()
{
    return simTime;
}

void DoublePendulumWidget::timerEvent(QTimerEvent *)
{
    // Make sure we are not currently paused
    if (isPaused)
    {
        return;
    }

    // Advance the time forward
    simTime += timeStep;

    // Update the scene
    scene()->advance();
}
