#include "interpolation.h"

interpolation::interpolation()
{

}

void interpolation::LinearInterpolation(int t){
    for(int i=0;i<num_dot;i++){
           double tdm=(double)t/10;
           temp.x = (1-tdm)*start[i].x + tdm*end[i].x;
           temp.y = (1-tdm)*start[i].y + tdm*end[i].y;
           result.push_back(temp);
       }
}

void interpolation::setnum_dot(int n){
    num_dot=n;
}

void interpolation::VectorInterpolation(int t){
    std::vector<dot> tempstart;
    std::vector<dot> tempend;
    double tdm=(double)t/9;

    for(int i=1;i<num_dot;i++){
        temp.x=start[i].x-start[i-1].x;
        temp.y=start[i].y-start[i-1].y;
        temp.r=sqrt(pow(temp.x,2)+pow(temp.y,2));
        temp.z=temp.y/abs(temp.y)*acos(temp.x/temp.r);
        tempstart.push_back(temp);

        temp.x=end[i].x-end[i-1].x;
        temp.y=end[i].y-end[i-1].y;
        temp.r=sqrt(pow(temp.x,2)+pow(temp.y,2));
        temp.z=temp.y/abs(temp.y)*acos(temp.x/temp.r);
        tempend.push_back(temp);
    }

    for(int i=0;i<num_dot;i++){
        if(tempend[i].z<=tempstart[i].z){
            temp.z=(1-tdm)*tempstart[i].z+tdm*tempend[i].z;
            temp.r=(1-tdm)*tempstart[i].r+tdm*tempend[i].r;
        }
        else{
            temp.z=(1-tdm)*tempstart[i].z+tdm*(tempend[i].z+360/(2*PI));
            temp.r=(1-tdm)*tempstart[i].r+tdm*tempend[i].r;
        }

        if(i==0){
            temp.x=(1-tdm)*start[0].x+tdm*end[0].x;
            temp.y=(1-tdm)*start[0].y+tdm*end[0].y;
            result.push_back(temp);
        }
        temp.x=temp.x+cos(temp.z)*temp.r;
        temp.y=temp.y+sin(temp.z)*temp.r;
        result.push_back(temp);
    }
}
