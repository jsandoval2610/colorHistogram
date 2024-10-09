
#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <QtWidgets>

class colorHistogram : public QWidget
{

    QImage image;
    QVector<int> *slices;

    QSlider *sliceSlider;
    QComboBox *colorComboBox;
    QLabel *histogramLabel;
    QSlider *opacitySlider;

public:
    explicit colorHistogram(QWidget *parent = nullptr);

    int sliderValue;
    QString boxColor;
    int opacitySliderInput;

    void setImage(const QImage &image);
    void updateRasterImage();
    QVector<int> setDominantColor(int num1, int num2, int num3);

public slots:
    void sliderSlot(int value);
    void boxSlot(const QString &color);
    void opacitySlot(int num);
};

#endif // COLORHISTOGRAM_H
