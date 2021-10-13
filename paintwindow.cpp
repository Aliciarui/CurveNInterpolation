#include "paintwindow.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<cmath>
#include<QTimer>
#include<qDebug>
#include<QPaintEvent>

paintWindow::paintWindow(QWidget *parent):QWidget(parent)
{
    piximg=new QPixmap;
    piximg->load("D:\\Animation\\newcar\\ball.png");
}

void paintWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    paint.drawPixmap(rect(),QPixmap("D:\\Animation\\newcar\\wallpaper.png"),QRect());

    paint.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    paint.setPen(QColor(255,255,255));

    if(flag==1||flag==6||flag==7)//generate spline
    {
        for(int i=0;i<s->getnum()-2;i++){
            paint.setPen(QColor(255,255,255));
            paint.drawLine(s->getX(i),s->getY(i),s->getX(i+1),s->getY(i+1));
            if(flag==7){//show interpolation points
                paint.setPen(QColor(0,0,255));
                paint.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                paint.drawEllipse(s->getX(i)-1.5,s->getY(i)-1.5,3,3);
            }
        }
    }
    else if(flag==2)//draw first pattern
    {
        for(int i=0;i<(int)in.start.size();i++){
            paint.drawEllipse(in.start[i].x-2,in.start[i].y-2,5,5);
        }
        for(int i=0;i<(int)in.start.size()-1;i++){
            paint.drawLine(in.start[i].x,in.start[i].y,in.start[i+1].x,in.start[i+1].y);
        }
    }
    else if(flag==0){//normal mode
        for(int i=0;i<(int)vec.size();i++){
            paint.drawEllipse(vec[i].x-2,vec[i].y-2,5,5);
        }
        for(int i=0;i<(int)vec.size()-1;i++){
            paint.drawLine(vec[i].x,vec[i].y,vec[i+1].x,vec[i+1].y);
        }
    }
    else if(flag==3)//draw second pattern
    {
        for(int i=0;i<(int)in.end.size();i++){
            paint.drawEllipse(in.end[i].x-2,in.end[i].y-2,5,5);
        }
        for(int i=0;i<(int)in.end.size()-1;i++){
            paint.drawLine(in.end[i].x,in.end[i].y,in.end[i+1].x,in.end[i+1].y);
        }
    }
    else if(flag==4||flag==5)//linear & vector interpolation
    {
        double x[100];
        double y[100];
        if(new_count<10){
            if(flag==4) in.LinearInterpolation(new_count);
            else if(flag==5) in.VectorInterpolation(new_count);
            for(int m=0;m<in.num_dot;m++){
                x[m]=in.result[m].x;
                y[m]=in.result[m].y;
            }
        }
        for(int m=1;m<(int)in.num_dot;m++){
            paint.drawLine(x[m-1],y[m-1],x[m],y[m]);
        }
        in.result.clear();
        new_count++;
    }
    if(flag==6){//draw ball
        if(new_count<(int)s->getnum()-1){
            double temp=atan(s->getSlope()[new_count]);
            temp=judgesymbol(temp);
            temp=temp/(2*PI)*360;
            paint.translate(s->getX(new_count),s->getY(new_count));//set the center
            paint.rotate(temp);
            paint.drawPixmap(-25,-25,50,50,*piximg);
        }
        new_count++;
    }
}

void paintWindow::mousePressEvent(QMouseEvent *e)
{
    float x = e->pos().x();
    float y = e->pos().y();
    dot p;
    p.setdot(x,y);
    if (flag!=2 && flag!=3){
        vec.push_back(p);
    }
    else if(flag==2){
        in.start.push_back(p);
        in.num_dot++;
    }

    else if(flag==3){
        in.end.push_back(p);
    }
    update();
}

void paintWindow::setSpline(int grain, double tension)
{
    if(!s)delete s;
    if(vec.size()==0)return;
    dot* p = new dot[vec.size()];
    for(int i=0;i<(int)vec.size();i++){
        p[i].x = vec[i].x;
        p[i].y = vec[i].y;
    }
    s = new cspline(p,vec.size(),grain,tension);
}

void paintWindow::clearwindow()
{
    vec.clear();
    in.result.clear();
    delete s;
    update();
}

double paintWindow::judgesymbol(double temp){
    if(temp>0 && (temp+temp1)>temp) qDebug("plus");
    else if(temp<0 && (temp+temp1)<temp1) qDebug("minus");
    else temp=-temp;
    temp1=temp;
    return temp;
}
