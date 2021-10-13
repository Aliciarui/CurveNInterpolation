#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include"cspline.h"
#include"interpolation.h"
#include<QWidget>
#include<vector>
#include<QtCore/QObject>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<math.h>
#include<QPropertyAnimation>

class QTimer;

class paintWindow:public QWidget
{
public:
    paintWindow(QWidget *parent = 0);
    void setSpline(int grain, double tension);
    int flag=0;
    std::vector<dot>vec;
    void clearwindow();
    int new_count=0;

private:
    cspline* s;
    interpolation in;
    QPropertyAnimation *animation;
    QLabel *object;

    QPixmap *piximg;
    double temp1=0;
    double judgesymbol(double temp);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // PAINTWINDOW_H
