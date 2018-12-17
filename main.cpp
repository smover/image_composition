#include "imagecomposer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageComposer composer;
    composer.show();
    return app.exec();
}
