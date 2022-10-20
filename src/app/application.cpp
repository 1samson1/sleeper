#include "application.h"

#include <QIcon>

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    this->setWindowIcon(QIcon(":/icon"));
}
