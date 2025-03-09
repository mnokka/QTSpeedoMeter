

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QTimer>

class Speedometer : public QWidget {
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateSpeed();

private:
    int targetSpeed;  // Nopeus (0-240 km/h)
    int currentSpeed;
    QTimer timer;
};

#endif // SPEEDOMETER_H



