#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "speedometer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile file(QCoreApplication::applicationDirPath() + "/../../darktheme.css");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        app.setStyleSheet(ts.readAll());
    } else {
        qWarning("Tyylitiedoston lataaminen epäonnistui.");
    }


    QMainWindow window;
    Speedometer *speedometer = new Speedometer(&window);
    window.setCentralWidget(speedometer);
    window.setWindowTitle("Auton Nopeusmittari MPN 2025");
    window.resize(400, 400);
    window.show();

    return app.exec();
}
