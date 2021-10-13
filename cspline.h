#ifndef CSPLINE_H
#define CSPLINE_H

class dot
{
public:
    double x;
    double y;
    double r;
    double z;
    void setdot(double my_x,double my_y);
};


class cspline
{
private:
    dot* knots;
    dot* Spline;
    double* slopes;
    int grain;
    double tension;

    int n;
    int count;
    double m[16];
    void GetCardinalMatrix();
    double Matrix(double a,double b,double c,double d, double alpha);

public:
    cspline(dot* p, int my_n, int my_grain, double my_tension);
    void CubicSpline();//generate interpolation point
    double* getSlope();
    virtual ~cspline();
    double getX(int i);
    double getY(int i);
    int getnum();

};

#endif // SPLINE_H
