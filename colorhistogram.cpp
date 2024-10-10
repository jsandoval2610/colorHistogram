#include "colorhistogram.h"
#include <QtWidgets>
#include <algorithm>

colorHistogram::colorHistogram(QWidget *parent) : QWidget(parent)
{

    // Initialize the QLabel with an empty 256x256 QPixmap
    histogramLabel = new QLabel();
    histogramLabel->setFixedSize(256, 256);
    QPixmap emptyPixmap(256, 256);
    emptyPixmap.fill(Qt::white);
    histogramLabel->setPixmap(emptyPixmap);

    //Initialize the Opacity Scaler
    opacitySlider = new QSlider(Qt::Vertical);
    opacitySlider->setRange(0, 100);
    opacitySlider->setValue(50);
    connect(opacitySlider, &QSlider::valueChanged, this, &colorHistogram::opacitySlot);

    // Initialize the QSlider
    sliceSlider = new QSlider(Qt::Horizontal);
    sliceSlider->setRange(0, 255);
    sliceSlider->setValue(128);
    connect(sliceSlider, &QSlider::valueChanged, this, &colorHistogram::sliderSlot);

    // Initialize the QComboBox
    colorComboBox = new QComboBox();
    colorComboBox->addItems({"Red", "Green", "Blue"});
    connect(colorComboBox, &QComboBox::currentTextChanged, this, &colorHistogram::boxSlot);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *preLayout = new QHBoxLayout();
    preLayout->addWidget(histogramLabel);
    preLayout->addWidget(opacitySlider);
    layout->addLayout(preLayout);
    layout->addWidget(sliceSlider);
    layout->addWidget(colorComboBox);

    setLayout(layout);

    slices = new QVector<int>(1 << 24, 0);
    sliderValue = 128;
    opacitySliderInput = 50;
    boxColor = "Red";

}

void colorHistogram::setImage(const QImage &image) {

    for(int i = 0; i < image.height(); ++i) {
        for(int j = 0; j < image.width(); ++j) {
            QColor currColor = image.pixelColor(j,i);
            int red = currColor.red();
            int green = currColor.green();
            int blue = currColor.blue();

            int colorIndex = (red << 16) | (green << 8) | blue;
            (*slices)[colorIndex] += 1;

        }
    }
}

void colorHistogram::sliderSlot(int value) {
    sliderValue = value;
    updateRasterImage();
}

void colorHistogram::boxSlot(const QString &color) {
    boxColor = color;
    updateRasterImage();
}

void colorHistogram::opacitySlot(int num) {
    opacitySliderInput = num;
    updateRasterImage();
}

QVector<int> colorHistogram::setDominantColor(int num1, int num2, int num3) {

    int trueMax = std::max({num1, num2, num3});
    return QVector<int>({((255/trueMax)*num1),((255/trueMax)*num2),((255/trueMax)*num3)});
}


void colorHistogram::updateRasterImage() {
    QPixmap rasterPixmap(256, 256);
    rasterPixmap.fill(Qt::white);

    QPainter painter(&rasterPixmap);
    QVector<int> setColors;

    for (int row = 0; row < 256; ++row) {
        for (int col = 0; col < 256; ++col) {
            int colorIndex = -1;

            if (boxColor == "Red") {
                colorIndex = (sliderValue << 16) | (row << 8) | col;
                setColors = setDominantColor(sliderValue, row, col);
            } else if (boxColor == "Green") {
                colorIndex = (row << 16) | (sliderValue << 8) | col;
                setColors = setDominantColor(row, sliderValue, col);
            } else if (boxColor == "Blue") {
                colorIndex = (row << 16) | (col << 8) | sliderValue;
                setColors = setDominantColor(row, col, sliderValue);
            }

            if (colorIndex > -1) {
                int alpha = (opacitySliderInput * ((*slices)[colorIndex])) < 255 ? (opacitySliderInput * ((*slices)[colorIndex])) : 255;
                painter.setPen(QColor(setColors[0], setColors[1], setColors[2], alpha));
                painter.drawPoint(row, col);
            }
        }
    }

    histogramLabel->setPixmap(rasterPixmap);
}
