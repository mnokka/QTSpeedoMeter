#include <QApplication>
#include <QMainWindow>
#include "speedometer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    Speedometer *speedometer = new Speedometer(&window);
    window.setCentralWidget(speedometer);
    window.setWindowTitle("Auton Nopeusmittari MPN 2025");
    window.resize(400, 400);
    window.show();

    return app.exec();
}
