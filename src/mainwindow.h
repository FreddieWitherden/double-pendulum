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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

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

    void resetStatusBar();

protected slots:
    void about();
    void webPage();

    void addPendulum();
    void removePendulum();
    void changePendulum(int index);

    void startSim();
    void pauseSim();
    void stopSim();

    void zoomIn();
    void zoomOut();
    void zoomBestFit();

    void updatePendulumIcon();

    void updatePendulum();

    void updateStatusBar();

    void setDefaults();

private:
    Ui::MainWindowClass *ui;

    QLabel *m_statusBarTime;
    QLabel *m_statusBarFps;

    QTimer *m_statusBarTimer;
    int m_pendulumCount;
    bool m_maskUpdates;
};

#endif // MAINWINDOW_H
