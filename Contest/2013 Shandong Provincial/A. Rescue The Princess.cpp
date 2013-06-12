/*********************************
给出等边三角形两个点的坐标，求逆时针方向第三个点坐标
**********************************/

#include <stdio.h>
#include <cmath>

const double pi = acos(-1.0);
struct vector{
    double x;
    double y;
    vector(double _x=0, double _y=0){
        x = _x; y = _y;
    }
};

vector rotate(vector A){
    double x1 = A.x*cos(pi/3)-A.y*sin(pi/3);
    double y1 = A.x*sin(pi/3)+A.y*cos(pi/3);
    return vector(x1, y1);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        vector p(x2-x1, y2-y1);
        p = rotate(p);
        printf("(%.2f,%.2f)\n", p.x+x1, p.y+y1);
    }
    return 0;
}
