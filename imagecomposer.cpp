
#include "imagecomposer.h"

#include <QtWidgets>

static const QSize resultSize(200, 200);

ImageComposer::ImageComposer()
{
    operatorComboBox = new QComboBox;
    addOp(QPainter::CompositionMode_SourceOver, tr("SourceOver"));
    addOp(QPainter::CompositionMode_DestinationOver, tr("DestinationOver"));
    addOp(QPainter::CompositionMode_Clear, tr("Clear"));
    addOp(QPainter::CompositionMode_Source, tr("Source"));
    addOp(QPainter::CompositionMode_Destination, tr("Destination"));
    addOp(QPainter::CompositionMode_SourceIn, tr("SourceIn"));
    addOp(QPainter::CompositionMode_DestinationIn, tr("DestinationIn"));
    addOp(QPainter::CompositionMode_SourceOut, tr("SourceOut"));
    addOp(QPainter::CompositionMode_DestinationOut, tr("DestinationOut"));
    addOp(QPainter::CompositionMode_SourceAtop, tr("SourceAtop"));
    addOp(QPainter::CompositionMode_DestinationAtop, tr("DestinationAtop"));
    addOp(QPainter::CompositionMode_Xor, tr("Xor"));
    addOp(QPainter::CompositionMode_Plus, tr("Plus"));
    addOp(QPainter::CompositionMode_Multiply, tr("Multiply"));
    addOp(QPainter::CompositionMode_Screen, tr("Screen"));
    addOp(QPainter::CompositionMode_Overlay, tr("Overlay"));
    addOp(QPainter::CompositionMode_Darken, tr("Darken"));
    addOp(QPainter::CompositionMode_Lighten, tr("Lighten"));
    addOp(QPainter::CompositionMode_ColorDodge, tr("ColorDodge"));
    addOp(QPainter::CompositionMode_ColorBurn, tr("ColorBurn"));
    addOp(QPainter::CompositionMode_HardLight, tr("HardLight"));
    addOp(QPainter::CompositionMode_SoftLight, tr("SoftLight"));
    addOp(QPainter::CompositionMode_Difference, tr("Difference"));
    addOp(QPainter::CompositionMode_Exclusion, tr("Exclusion"));

    equalLabel = new QLabel(tr("="));

    resultLabel = new QLabel;
    resultLabel->setMinimumWidth(resultSize.width());

    connect(operatorComboBox, SIGNAL(activated(int)), this, SLOT(recalculateResult()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(operatorComboBox, 1, 1);
    mainLayout->addWidget(equalLabel, 1, 3);
    mainLayout->addWidget(resultLabel, 0, 4, 3, 1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    // The basic image you're going to draw to
    // This is your basic canvas
    resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    const int width = resultSize.width();
    const int height = resultSize.height();

    // The source image -- this is your map
    // NOTE: the format must be QImage::Format_ARGB32
    // You have to enable the Alpha channel in the image format
    // That channel is the one allowing transparencies!
    sourceImage = QImage(width, height, QImage::Format_ARGB32);
    // The destination image --- this is your background
    destinationImage = QImage(width, height, QImage::Format_ARGB32);

    // source image is just a blue square
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)        
            sourceImage.setPixel(i,j,QColor(17,62,228).rgba());

    // the source image has a transparent square
    for (int i = 50; i < 100; i++)
        for (int j = 50; j < 100; j++)           
            sourceImage.setPixel(i,j,QColor(1,1,1,0).rgba());

    // the destination image is green
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            destinationImage.setPixel(i,j,QColor(0,255,0).rgba());

    setWindowTitle(tr("Image Composition"));

    recalculateResult();
}

void ImageComposer::recalculateResult()
{
    // Here you are drawing the source and destination image on the result image
    // NOTE: the composition mode defines how the two images are composed
    // The SourceOver is the option you need: the source image is over the destination image,
    // and the source image has a transparent hole!
    QPainter::CompositionMode mode = currentMode();

    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, destinationImage);
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, sourceImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    resultLabel->setPixmap(QPixmap::fromImage(resultImage));
}

void ImageComposer::addOp(QPainter::CompositionMode mode, const QString &name)
{
    operatorComboBox->addItem(name, mode);
}

QPainter::CompositionMode ImageComposer::currentMode() const
{
    return (QPainter::CompositionMode)
           operatorComboBox->itemData(operatorComboBox->currentIndex()).toInt();
}

QPoint ImageComposer::imagePos(const QImage &image) const
{
    return QPoint((resultSize.width() - image.width()) / 2,
                  (resultSize.height() - image.height()) / 2);
}
