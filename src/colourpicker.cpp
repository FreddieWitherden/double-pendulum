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

#include "colourpicker.h"

#include <QMouseEvent>
#include <QResizeEvent>

#include <QPixmap>
#include <QPainter>
#include <QColorDialog>

ColourPicker::ColourPicker(QWidget *parent)
    : QToolButton(parent)
{
    setColour(Qt::blue);
    connect(this, SIGNAL(clicked()), this, SLOT(selfClicked()));
}

QColor ColourPicker::colour()
{
    return m_colour;
}

void ColourPicker::setColour(const QColor& colour)
{
    m_colour = colour;

    // Create a pixmap to use as our 'icon'
    QPixmap pix(iconSize());
    QPainter painter(&pix);

    // Paint the colour to a rectangle
    painter.setBrush(colour);
    painter.setPen(Qt::gray);
    painter.drawRect(pix.rect().adjusted(0, 0, -1, -1));

    // Set the pixmap as the buttons icon
    setIcon(QIcon(pix));
}

void ColourPicker::resizeEvent(QResizeEvent *)
{
    setColour(m_colour);
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

