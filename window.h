#ifndef WINDOW_H
#define WINDOW_H

#include "paintwindow.h"
#include<QTimer>
#include<QtCore/QObject>
#include<QPropertyAnimation>
#include<QSpinBox>
#include<QDoubleSpinBox>

class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;

class window : public QWidget
{
    Q_OBJECT
private:
    QWidget* menuWindow;
    QHBoxLayout* hlayout[5];
    QVBoxLayout* vlayout[5];
    QVBoxLayout* mainlayout;
    QHBoxLayout* menulayout;

    paintWindow* w;
    QImage *img;

    QSpinBox* grainLine;
    QDoubleSpinBox* tensionLine;
    QLineEdit* speedLine;
    QLineEdit* acceLine;

    QLabel* lenLabel;
    QLabel* grainLabel;
    QLabel* tensionLabel;
    QLabel* speedLabel;
    QLabel* acceLabel;


    QPushButton* genButton;
    QPushButton* startButton;
    QPushButton* clearButton;
    QPushButton* linearButton;
    QPushButton* vectorButton;
    QPushButton* secondButton;
    QPushButton* firstButton;
    QPushButton* transButton;
    QPushButton* interpolation;

    void layout();
    int mid_time=1;

public:
    window(QWidget* parent = 0);
    QTimer *timer = new QTimer(this);

private slots:
    void updatePaintWindow();
    void clear();
    void start();
    void firstpattern();
    void secondpattern();
    void linear_update();
    void ten_update();
    void vector_update();
    void start_trans();
    void changein();
};

#endif // WINDOW_H
