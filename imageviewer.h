#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>

class ImageViewer : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene *scene;
    QGraphicsPixmapItem *giPixmap;
    double scale;

public:

    explicit ImageViewer(QWidget *parent = nullptr);
    void setImage(const QImage &image);
};

#endif // IMAGEVIEWER_H
