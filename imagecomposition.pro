QT += widgets
requires(qtConfig(combobox))

HEADERS       = imagecomposer.h
SOURCES       = imagecomposer.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/imagecomposition
INSTALLS += target
