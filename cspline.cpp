#include "cspline.h"
#include<QDebug>

cspline::cspline(dot* p, int my_n, int my_grain, double my_tension)
{
    n = my_n;
    grain = my_grain;
    tension = my_tension;
    slopes=new double[(n-1)*grain+1];

    knots = new dot[n + 2];
    for (int i = 1; i<=n; i++) {
        knots[i].x = p[i-1].x;
        knots[i].y = p[i-1].y;
    }
    knots[0].x = p[0].x;
    knots[0].y = p[0].y;
    knots[n + 1].x = p[n - 1].x;
    knots[n + 1].y = p[n - 1].y;
    Spline = new dot[(n-1)* grain + 1];

    count = 0;
    CubicSpline();
}

void cspline::CubicSpline()
{
    dot *s, *k0, *kml, *k1, *k2;
    int i,j;
    double alpha[50];
    GetCardinalMatrix();
    for(i=0; i<grain; i++)
        alpha[i] =((double)i)/grain;
    s = Spline;
    kml = knots;
    k0=kml+1;
    k1=k0+1;
    k2=k1+1;
    for(i=0; i<n-1; i++) {
        for(j=0; j<grain;j++) {
            s->x = Matrix(kml->x,k0->x,k1->x,k2->x,alpha[j]);
            s->y = Matrix(kml->y,k0->y,k1->y,k2->y,alpha[j]);
            s++;
        }
        k0++; kml++; k1++; k2++;
    }
}

void cspline::GetCardinalMatrix(){
    double a1 = tension;
    m[0] = -a1, m[1] = 2 - a1, m[2] = a1 - 2, m[3] = a1;
    m[4] = 2 * a1, m[5] = a1 - 3, m[6] = 3 - 2 * a1, m[7] = -a1;
    m[8] = -a1, m[9] = 0, m[10] = a1, m[11] = 0;
    m[12] = 0, m[13] = 1, m[14] = 0, m[15] = 0;
}

double cspline::Matrix(double a, double b, double c, double d, double alpha){
    double p0,p1,p2,p3;
    p0=m[0]*a+m[1]*b+m[2]*c+m[3]*d;
    p1=m[4]*a+m[5]*b+m[6]*c+m[7]*d;
    p2=m[8]*a+m[9]*b+m[10]*c+m[11]*d;
    p3=m[12]*a+m[13]*b+m[14]*c+m[15]*d;
    return(p3+alpha*(p2+alpha*(p1+alpha*p0)));
}

cspline::~cspline()
{
    delete[] knots;
    delete[] Spline;
}

double cspline::getX(int i){
    return Spline[i].x;
}

double cspline::getY(int i){
    return Spline[i].y;
}

int cspline::getnum()
{
    return (n-1)*grain + 1;
}

double *cspline::getSlope()
{
    int temp=(n-1)*grain+1;
    for(int i=1;i<temp-1;i++){
        slopes[i]=tension*(double)(Spline[i+1].x-Spline[i-1].x)/(double)(Spline[i+1].y-Spline[i-1].y);
    }

    slopes[temp-1]=tension*(double)(Spline[temp-1].x-Spline[temp-2].x)/(double)(Spline[temp].y-Spline[temp-1].y);
    slopes[0]=tension*(double)(Spline[1].x-Spline[0].x)/(double)(Spline[1].y-Spline[0].y);
    return slopes;
}

void dot::setdot(double my_x,double my_y){
    x=my_x;
    y=my_y;
}
