#include "titlescreen.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TitleScreen window;
    window.show();
    return app.exec();
}
