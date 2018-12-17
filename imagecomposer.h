#ifndef IMAGECOMPOSER_H
#define IMAGECOMPOSER_H

#include <QPainter>
#include <QWidget>

class QComboBox;
class QLabel;
class QToolButton;

class ImageComposer : public QWidget
{
    Q_OBJECT

public:
    ImageComposer();

private slots:
    void recalculateResult();

private:
    void addOp(QPainter::CompositionMode mode, const QString &name);
    QPainter::CompositionMode currentMode() const;
    QPoint imagePos(const QImage &image) const;

    QComboBox *operatorComboBox;
    QLabel *equalLabel;
    QLabel *resultLabel;

    QImage sourceImage;
    QImage destinationImage;
    QImage resultImage;
};

#endif // IMAGECOMPOSER_H
