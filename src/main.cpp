#include "Application.hpp"

int WinMain(int argc, char* argv[]) {
    Application app(argc, argv);
    return QApplication::exec();
}
