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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass),
      m_pendulumCount(0), m_maskUpdates(false)
{
    ui->setupUi(this);

    // Create a timer to update the status bar
    m_statusBarTimer = new QTimer(this);
    connect(m_statusBarTimer, SIGNAL(timeout()), this, SLOT(updateStatusBar()));

    // Status bar widgets
    m_statusBarTime = new QLabel();
    statusBar()->addPermanentWidget(m_statusBarTime);

    m_statusBarFps = new QLabel();
    statusBar()->addPermanentWidget(m_statusBarFps);

    resetStatusBar();

    // Boiler-plate actions
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionWebPage, SIGNAL(triggered()), this, SLOT(webPage()));

    // Showing/hiding the settings dock
    ui->menuView->addAction(ui->dockWidget_model->toggleViewAction());

    // Adding/removing pendulums
    connect(ui->toolButton_addPendulum, SIGNAL(clicked()),
            this, SLOT(addPendulum()));
    connect(ui->toolButton_removePendulum, SIGNAL(clicked()),
            this, SLOT(removePendulum()));
    connect(ui->pendulums, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changePendulum(int)));

    // Starting/stopping/pausing the simulation
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(startSim()));
    connect(ui->actionPause, SIGNAL(triggered()), this, SLOT(pauseSim()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(stopSim()));

    // Zooming the simulation
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionBestFit, SIGNAL(triggered()), this, SLOT(zoomBestFit()));

    // Update ODE solving method
    connect(ui->odeSolver, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePendulum()));

    // Update dt and g
    connect(ui->dt, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->g, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Updating initial starting conditions (upper bob)
    connect(ui->theta1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->omega1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->m1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->l1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Update initial starting conditions (lower bob)
    connect(ui->theta2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->omega2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->m2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->l2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Update pendulum colour and opacity
    connect(ui->upperColour, SIGNAL(colourChanged(QColor)), this, SLOT(updatePendulum()));
    connect(ui->lowerColour, SIGNAL(colourChanged(QColor)), this, SLOT(updatePendulum()));
    connect(ui->opacity, SIGNAL(valueChanged(int)), this, SLOT(updatePendulum()));

    // Update the combo box icon when the pendulum colour changes
    connect(ui->upperColour, SIGNAL(colourChanged(QColor)), this, SLOT(updatePendulumIcon(QColor)));

    // Defaults button
    connect(ui->defaults, SIGNAL(clicked()), this, SLOT(setDefaults()));

    // Add a default pendulum item
    addPendulum();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_statusBarTimer;
}

void MainWindow::about()
{
    QMessageBox::about(this, trUtf8("About Double Pendulum"),
                       tr("Double pendulum simulator, version 0.2\n"
                          "Copyright © 2009 Freddie Witherden\n"
                          "Released under the GNU GPL 3+"));
}

void MainWindow::webPage()
{
    QDesktopServices::openUrl(QUrl("http://freddie.witherden.org/tools/doublependulum/"));
}

DoublePendulumItem *MainWindow::activeItem()
{
    int index = ui->pendulums->currentIndex();
    QVariant v = ui->pendulums->itemData(index);

    return v.value<DoublePendulumItem*>();
}

void MainWindow::resetStatusBar()
{
    // Restore the status bar items to their default values
    m_statusBarTime->setText("Time: 0.00s");
    m_statusBarFps->setText("FPS: 0");
}

void MainWindow::addPendulum()
{
    // Create a new pendulum
    DoublePendulumItem *pendulum = new DoublePendulumItem(ui->pendulumView);
    QVariant v = qVariantFromValue(pendulum);

    // Add the pendulum to the scene
    ui->pendulumView->scene()->addItem(pendulum);
    pendulum->setPos(0.0, 0.0);

    // Add an item in the Pendulum's combo box for the new pendulum
    ui->pendulums->addItem(QString("Pendulum %1").arg(++m_pendulumCount), v);

    // Get the index of the newly added item
    int index = ui->pendulums->findData(v);

    // Make this the selected item
    ui->pendulums->setCurrentIndex(index);

    // Set the values to the defaults
    setDefaults();

    // Enable the remove button if there are >= 2 pendulums present
    if (ui->pendulums->count() >= 2)
    {
        ui->toolButton_removePendulum->setEnabled(true);
    }
}

void MainWindow::removePendulum()
{
    // Remove the item from the scene
    ui->pendulumView->scene()->removeItem(activeItem());

    // Release the memory associated with item
    delete activeItem();

    // Remove the item from the combo box
    ui->pendulums->removeItem(ui->pendulums->currentIndex());

    // If there is only one pendulum left, disable the button
    if (ui->pendulums->count() == 1)
    {
        ui->toolButton_removePendulum->setEnabled(false);
    }
}

void MainWindow::changePendulum(int)
{
    // Mask update events
    m_maskUpdates = true;

    // Update the solver
    ui->odeSolver->setCurrentIndex(ui->odeSolver->findText(activeItem()->solver()));

    // dt & g
    ui->dt->setValue(activeItem()->dt());
    ui->g->setValue(activeItem()->g());

    // Update the spin-box values
    ui->theta1->setValue(activeItem()->upper().theta);
    ui->omega1->setValue(activeItem()->upper().omega);
    ui->m1->setValue(activeItem()->upper().m);
    ui->l1->setValue(activeItem()->upper().l);

    ui->theta2->setValue(activeItem()->lower().theta);
    ui->omega2->setValue(activeItem()->lower().omega);
    ui->m2->setValue(activeItem()->lower().m);
    ui->l2->setValue(activeItem()->lower().l);

    ui->lowerColour->setColour(activeItem()->lowerColour());
    ui->upperColour->setColour(activeItem()->upperColour());
    ui->opacity->setValue(activeItem()->opacity());

    // Unmask updates
    m_maskUpdates = false;
}

void MainWindow::startSim()
{
    // Disable the start action and options dock
    ui->actionStart->setEnabled(false);
    ui->dockWidgetContents_model->setEnabled(false);

    // Enable the stop and pause actions
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);

    // Start updating the status bar
    m_statusBarTimer->start(75);

    ui->pendulumView->startSim();
}

void MainWindow::pauseSim()
{
    ui->pendulumView->pauseSim();
}

void MainWindow::stopSim()
{
    // Enable the options dock and start buttons again
    ui->actionStart->setEnabled(true);
    ui->dockWidgetContents_model->setEnabled(true);

    // Disable the pause and stop actions
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);

    // Stop the status bar timer
    m_statusBarTimer->stop();

    // Reset the status bar (time and FPS to 0)
    resetStatusBar();

    ui->pendulumView->stopSim();
}

void MainWindow::zoomIn()
{
    double newScale = ui->pendulumView->scaleFactor() / 1.25;

    ui->pendulumView->setScaleFactor(newScale);
}

void MainWindow::zoomOut()
{
    double newScale = ui->pendulumView->scaleFactor() * 1.25;

    ui->pendulumView->setScaleFactor(newScale);
}

void MainWindow::zoomBestFit()
{
    // Get the ideal scaling factor the the view
    double idealScale = ui->pendulumView->idealScaleFactor();

    // Set this to be the new scaling factor
    ui->pendulumView->setScaleFactor(idealScale);
}

void MainWindow::updatePendulum()
{
    // Ensure that updates are not masked (such as when changing pendulums)
    if (m_maskUpdates)
    {
        return;
    }

    DoublePendulumItem *item = activeItem();

    // Solver
    item->setSolver(ui->odeSolver->currentText());

    // dt & g
    item->setDt(ui->dt->value());
    item->setG(ui->g->value());

    // Upper bob
    item->upper().theta = ui->theta1->value();
    item->upper().omega = ui->omega1->value();
    item->upper().m = ui->m1->value();
    item->upper().l = ui->l1->value();

    // Lower bob
    item->lower().theta = ui->theta2->value();
    item->lower().omega = ui->omega2->value();
    item->lower().m = ui->m2->value();
    item->lower().l = ui->l2->value();

    // Color
    item->setUpperColour(ui->upperColour->colour());
    item->setLowerColour(ui->lowerColour->colour());
    item->setOpacity(ui->opacity->value());
}

void MainWindow::updatePendulumIcon(const QColor& colour)
{
    int index = ui->pendulums->currentIndex();

    QPixmap pm(ui->pendulums->iconSize());
    QPainter painter(&pm);

    painter.setPen(Qt::gray);
    painter.setBrush(colour);
    painter.drawRect(pm.rect().adjusted(0, 0, -1, -1));

    // Set the icon to be the generated pixmap
    ui->pendulums->setItemIcon(index, QIcon(pm));
}

void MainWindow::updateStatusBar()
{
    QString timeStr;
    timeStr.setNum(ui->pendulumView->time() / 1000.0, 'f', 2);
    int fps = ui->pendulumView->framesPerSecond();

    m_statusBarTime->setText(QString("Time: %1s").arg(timeStr));
    m_statusBarFps->setText(QString("FPS: %1").arg(fps));
}

void MainWindow::setDefaults()
{
    // Mask update events
    m_maskUpdates = true;

    ui->odeSolver->setCurrentIndex(ui->odeSolver->findText("Runge Kutta (RK4)"));
    ui->dt->setValue(0.005);
    ui->g->setValue(9.81);

    ui->theta1->setValue(0.8);
    ui->omega1->setValue(0.0);
    ui->m1->setValue(1.0);
    ui->l1->setValue(1.0);

    ui->theta2->setValue(0.5);
    ui->omega2->setValue(0.0);
    ui->m2->setValue(0.3);
    ui->l2->setValue(0.6);

    ui->upperColour->setColour(Qt::red);
    ui->lowerColour->setColour(Qt::blue);
    ui->opacity->setValue(100);

    // Unmask update events and force an update
    m_maskUpdates = false;
    updatePendulum();

    // Update the pendulum's icon
    updatePendulumIcon(ui->upperColour->colour());
}
