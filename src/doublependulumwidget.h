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

protected slots:
    void timerEvent(QTimerEvent *event);

private:
    int timerId;
    const int timeStep;
    double simTime;
    bool isPaused;
};

#endif // DOUBLEPENDULUMWIDGET_H
