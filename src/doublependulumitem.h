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

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual void advance(int phase);

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
