#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "colorhistogram.h"
#include "imageviewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString lastDir;

    ImageViewer *imageViewer;
    colorHistogram *histogramWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFileSlot();
};
#endif // MAINWINDOW_H
