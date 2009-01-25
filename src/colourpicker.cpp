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

    // Create a pixmap slightly smaller than the button to be used as an icon
    QPixmap pix(rect().adjusted(3, 3, -5, -5).size());
    QPainter painter(&pix);

    // Paint the colour to a rectangle
    painter.setBrush(colour);
    painter.setPen(Qt::gray);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

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

