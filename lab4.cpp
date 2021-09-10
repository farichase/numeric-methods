#include <iostream>
#include <vector>
using namespace std;
float f(float x){
    return 2 * x* x * x - 3 * x * x -12 * x - 5;
}
float dF(float x) {
    return 6 * x * x - 6 * x - 12;
}
float sgn(float x)
{
    if (x > 0) return 1;
    else if (x = 0) return 0;
    return -1;
}
int main()
{
    float eps = 0.001;
    float x0 = -1.5;
    for(;;){
        float x1 = x0 - f(x0) / dF(x0);
        if (f(x1) * f(x0 + sgn(x1-x0) * eps) < 0) break;
        x0 = x1;
    }
    cout << x0 << " " << f(x0);
    return 0;
}
