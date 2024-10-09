#include "imageviewer.h"

#include <QtWidgets>

ImageViewer::ImageViewer(QWidget *parent) : QGraphicsView(parent) {

    scene = new QGraphicsScene(this);
    setScene(scene);

    giPixmap = new QGraphicsPixmapItem();
    scene->addItem(giPixmap);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setBackgroundBrush(Qt::lightGray);

}

void ImageViewer::setImage(const QImage &image) {
    giPixmap->setPixmap(QPixmap::fromImage(image));
    setSceneRect(QRectF(QPointF(0, 0), image.size()));
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
