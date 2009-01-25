#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "doublependulumitem.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    DoublePendulumItem *activeItem();

protected slots:
    void about();

    void addPendulum();
    void removePendulum();
    void changePendulum(int index);

    void startSim();
    void pauseSim();
    void stopSim();

    void updatePendulumIcon(const QColor& colour);

    void updatePendulum();

    void setDefaults();

private:
    Ui::MainWindowClass *ui;

    int m_pendulumCount;
    bool m_maskUpdates;
};

#endif // MAINWINDOW_H
