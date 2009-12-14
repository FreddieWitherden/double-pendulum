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

#ifndef DOUBLEPENDULUMINFOITEM_H
#define DOUBLEPENDULUMINFOITEM_H

#include <QGraphicsItem>

#include "doublependulumitem.h"

class DoublePendulumInfoItem : public QGraphicsItem
{
public:
    DoublePendulumInfoItem();
    ~DoublePendulumInfoItem();

    void setPendula(const QMap<QString, DoublePendulumItem *> &pendula);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    const double m_iconSize;
    const double m_horizontalPadding;
    const double m_verticalPadding;

    QMap<QString, DoublePendulumItem *> m_pendula;
};

#endif // DOUBLEPENDULUMINFOITEM_H
