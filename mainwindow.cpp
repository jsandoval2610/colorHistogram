#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Setup the UI
    QWidget *center = new QWidget(this);
    QHBoxLayout *splitter = new QHBoxLayout(center);

    imageViewer = new ImageViewer();
    histogramWidget = new colorHistogram();

    splitter->addWidget(imageViewer);
    splitter->addWidget(histogramWidget);

    setCentralWidget(center);
    resize(800, 600);

    // Menu and open file action
    QAction *openFileAct = new QAction("&Open image file", this);
    connect(openFileAct, &QAction::triggered, this, &MainWindow::openFileSlot);
    openFileAct->setShortcut(Qt::CTRL | Qt::Key_O);

    QMenu *fileMenu = new QMenu("&File", this);
    fileMenu->addAction(openFileAct);
    menuBar()->addMenu(fileMenu);

    // Load last directory from settings
    QSettings settings("FJS Systems", "Graphics1");
    lastDir = settings.value("lastDir", "").toString();

    // Window properties
    setWindowTitle("Image and Histogram Viewer");
    resize(1000, 600);
}

MainWindow::~MainWindow() {
    // Save last directory to settings
    QSettings settings("FJS Systems", "Graphics1");
    settings.setValue("lastDir", lastDir);
}

void MainWindow::openFileSlot() {
    // Open file dialog to select image
    QString fName = QFileDialog::getOpenFileName(this, "Select image file",  lastDir, "Image files (*.png *.jpeg *.jpg *.bmp)");
    if (fName.isEmpty()) return;

    QImage image(fName);
    if (image.isNull()) return;

    lastDir = QFileInfo(fName).absolutePath();

    imageViewer->setImage(image);
    histogramWidget->setImage(image);
}
