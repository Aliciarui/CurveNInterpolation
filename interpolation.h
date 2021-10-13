#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include"cspline.h"
#include<vector>
#include<math.h>
#include<QDebug>

#define PI 3.1415

class cspline;

class interpolation
{
public:
    interpolation();
    void LinearInterpolation(int t);
    void VectorInterpolation(int t);
    void setnum_dot(int n);
    std::vector<dot>result;
    std::vector<dot>start;
    std::vector<dot>end;

    dot temp;
    int num_dot=0;
private:
    int num=10;
};

#endif // INTERPOLATION_H
