#include "speedometer.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include <QPainterPath>

Speedometer::Speedometer(QWidget *parent) : QWidget(parent), currentSpeed(0), targetSpeed(0) {
    setMinimumSize(300, 300);
    connect(&timer, &QTimer::timeout, this, &Speedometer::updateSpeed);
    timer.start(200);
}

void Speedometer::updateSpeed() {
    if (QRandomGenerator::global()->bounded(4) !=0) { // 75%
        //qDebug() << "no speed change" << targetSpeed;
    } else { // 25%
        targetSpeed = QRandomGenerator::global()->bounded(0, 241);  // Generate new speed between 0 and 240 km/h
        //qDebug() << "targetSpeed:" << targetSpeed;
    }
    // Gradually update the current speed towards the target speed
    if (currentSpeed < targetSpeed) {
        currentSpeed += 1;
    } else if (currentSpeed > targetSpeed) {
        currentSpeed -= 1;
    }
    update();
}

void Speedometer::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    painter.translate(width() / 2, height() / 2);  // Center the speedometer
    painter.scale(side / 300.0, side / 300.0);  // Scale the speedometer

    // Draw the frame
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawEllipse(-100, -100, 201, 201);

    painter.setPen(Qt::NoPen);  // Ei reuna
    painter.setBrush(QColor(200, 200, 200));  // Vaaleanharmaa väri
    painter.drawEllipse(-100, -100, 200, 200);  // Täytetään ympyrä suoraan piirtämällä se


    // Draw the tick marks for the speedometer
    for (int i = 0; i <= 240; i += 20) {
        painter.save();
        double angle = (i - 120) * 1.5;  // 240 km/h distributed over 180 degrees
        painter.rotate(angle);
        painter.setPen(Qt::black);
        painter.drawLine(0, -80, 0, -90);
        painter.restore();
    }

    painter.setPen(Qt::darkYellow);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(-10, -65, "120");
    painter.drawText(-70, 5, "60");
    painter.drawText(45, 5, "180");


    // Draw the needle for the current speed
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.save();
    double angle = (currentSpeed - 120) * 1.5;  // Convert speed to angle
    painter.rotate(angle);
    painter.drawPolygon(QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, -80));
    painter.restore();

    // Display the current speed as text
    painter.setPen(Qt::darkYellow);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(-30, 60, QString("%1 km/h").arg(currentSpeed));
}
