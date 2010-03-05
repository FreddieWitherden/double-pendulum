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

#include "colourpicker.h"

#include <QMouseEvent>

#include <QPixmap>
#include <QPainter>
#include <QColorDialog>

ColourPicker::ColourPicker(QWidget *parent)
    : QToolButton(parent)
{
    setColour(Qt::blue);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(this, SIGNAL(clicked()), this, SLOT(selfClicked()));
}

QColor ColourPicker::colour()
{
    return m_colour;
}

void ColourPicker::setColour(const QColor& colour)
{
    m_colour = colour;

    // Request a redraw
    update();
}

void ColourPicker::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter p(this);

    // Compute the dimensions of the rectangle to paint to
    const int corr = 5;
    QRect r = rect().adjusted(corr, corr, -corr - 1, -corr - 1);

    p.setBrush(m_colour);
    p.setPen(Qt::lightGray);
    p.drawRect(r);
}

void ColourPicker::selfClicked()
{
    // Ask the user to pick a colour
    QColor c = QColorDialog::getColor(m_colour, this);

    // So long as it is valid, use it
    if (c.isValid())
    {
        setColour(c);
        emit colourChanged(c);
    }
}
