#include "iostream"
#include "vector"
#include <cmath>
using namespace std;

const float eps = powf(10, -6);

float rectangle(float a, float b, int j){
    float h = (b - a) / j;
    float res = 0;
    for (int i = 0 ; i < j; i++){
        res += exp(a + (h * (float)i + h/2));
    }
    return res * h;
}
float calculateR(float val, float val2){
    return (val2 - val) / (powf(2, 2) - 1);
}
float trapezium(float a, float b, int j){
    float h = (b-a)/j;
    float res = 0;
    for (int i = 0; i < j; i++){
        float x1 = a + i*h;
        float x2 = a + (i+1) * h;
        res += 0.5 * (exp(x1)+exp(x2));
    }
    return res *h;
}
float simpson(float a, float b, int j){
    float h = (b - a) / j;
    float res = 0;
    for (int i = 0; i < j; i++){
        float x1 = a + i*h;
        float x2 = a + (i+1)*h;
        res += (h / 6) * (exp(x1) + 4.0*exp(0.5*(x1+x2)) + exp(x2));
    }
    return res;
}
int main(){
    float a = 0, b = 1, r = 1;
    int j = 1;
    cout << "Rectangle method" << "\n";
    for (int i = 2; ; i *= 2) {
        float resI = rectangle(a, b, i);
        r = calculateR(resI, rectangle(a, b, i*2));
        cout << j << " " 
        << "I*: "<< resI << " " 
        << "I* + r: " << resI + r << " "
        << "r: " << r << "\n";
        j++;
        if (abs(r) <= eps) break;
    }
    j = 1;
    cout << "Trapezium method" << "\n";
    for (int i = 2; ; i *= 2) {
        float resI = trapezium(a, b, i);
        r = calculateR(resI, trapezium(a, b, i*2));
        cout << j << " " 
        << "I*: "<< resI << " " 
        << "I* + r: " << resI + r << " "
        << "r: " << r << "\n";
        j++;
        if (abs(r) <= eps) break;
    }
    j = 1;
    cout << "Simpson method" << "\n";
    for (int i = 2; ; i *= 2) {
        float resI = simpson(a, b, i);
        r = calculateR(resI, simpson(a, b, i*2));
        cout << j << " " 
        << "I*: "<< resI << " " 
        << "I* + r: " << resI + r << " "
        << "r: " << r << "\n";
        j++;
        if (abs(r) <= eps) break;
    }
}