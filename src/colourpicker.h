#ifndef COLOURPICKER_H
#define COLOURPICKER_H

#include <QToolButton>

class ColourPicker : public QToolButton
{
    Q_OBJECT

public:
    ColourPicker(QWidget *parent);

    QColor colour();
    void setColour(const QColor& colour);

signals:
    void colourChanged(const QColor& colour);

protected slots:
    void selfClicked();

protected:
    void resizeEvent(QResizeEvent *event);

    QColor m_colour;
};

#endif // COLOURPICKER_H
