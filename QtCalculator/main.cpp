#include "calculator.hpp"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator window;
    window.resize(300, 190);
    window.setWindowTitle("Calculator");
    window.show();
    return app.exec();
}
