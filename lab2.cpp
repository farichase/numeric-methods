
#include "iostream"
#include "vector"
#include <math.h>
using namespace std;

const float PI = std::atan(1.0)*4;
vector<float> calculateA(vector<float> y, int n){
    vector<float> a(n + 1);
    for (int j = 1; j < n + 1; j++) {
        a[j] = y[j-1];
    }
    return a;
}
vector<float> calculate(vector<float> a, vector<float> b, vector<float> c, vector<float> d, int n){
    vector<float> alfa(n), beta(n);
    alfa[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];
    
    for (int i = 1; i < n; i++){
        float t = b[i] + a[i-1] * alfa[i-1];
        float t2 = d[i] - a[i-1] * beta[i - 1];
        alfa[i] = -c[i] / t;
        beta[i] = t2 / t;
    }
    vector<float> x (n);
    x[n-1] = beta[n-1];
    for (int i = n-2; i > -1; i--){
        x[i] = alfa[i] * x[i+1] + beta[i];
    }
    return x;
}
vector<float> calculateRight(vector<float> y, int n, float h){
    vector<float> d(n-2);
    float coef = 3 / h*h;
    for (int j = 0; j < n-2; j++) {
        d[j] = coef * (y[j+2] - 2*y[j+1] + y[j]);
    }
    return d;
}
float roundElem(float x){
    return round(x * 1000.0) / 1000.0;
}
vector<float> calculateC(vector<float> y, int n, float h){
    vector<float> vert1(n-1), vert(n);
    for (int j = 0; j < n; j++) {
        vert[j] = 4;
    }
    for (int j = 0; j < n-1; j++) {
        vert1[j] = 1;
    } 
    vector<float> d = calculateRight(y, n, h);
    vector<float> c1 = calculate(vert1, vert, vert1, d, n);
    vector<float> c(n+1);
    c[n] = 0;
    c[0] = 0;
    for (int i = 1; i < n + 1; i++){
        c[i] = c1[i - 1] ;
    }
    return c;
}


vector<float> calculateD(vector<float> c, int n, float h){
    vector<float> d(n);
    for (int j = 0; j < n ; j++) {
        d[j] = (c[j+1] - c[j]) / (3*h);
    }
    return d;
}
vector<float> calculateB(vector<float> y, int n, float h, vector<float> c){
    vector<float> b(n+1);
    for (int j = 1; j < n + 1 ; j++) {
        b[j] = (y[j] - y[j-1]) / h - (h/3) * (c[j] + 2*c[j-1]);
    }
    return b;
}
int main(){
    int n = 8;
    vector<float> y(n+1), x(n+1);
    float a = 0, b = 8, h = (b - a) / (float)n;
    for (int j = 0; j < n + 1; j++) {
        x[j] = a + j * h;
        y[j] = sinf(x[j]);
    } 
    vector<float> aa = calculateA(y, n);
    cout << "A array: ";
    for (int i = 1; i < n+1; i++){
        cout << roundElem(aa[i]) << " ";
    }
    cout << "\n";
    vector<float> c = calculateC(y, n, h);
    cout << "C array: ";
    for (int i = 0; i < n; i++){
        cout << roundElem(c[i]) << " ";
    }
    cout << "\n";
    vector<float> bb = calculateB(y, n, h, c);
    cout << "B array: ";
    for (int i = 1; i < n + 1; i++){
        cout << roundElem(bb[i]) << " ";
    }
    cout << "\n";
    vector<float> d = calculateD(c, n, h);
    cout << "D array: ";
    for (int i = 0; i < n; i++){
        cout << roundElem(d[i]) << " ";
    }
    cout << "\n";
    //checking
    for (int i = 0; i < n; i++){
        float xx = a+i*h;
        float res = aa[i+1] + bb[i+1] * (x[i] - xx) +
        c[i] * (x[i] - xx) * (x[i] - xx) +
        d[i] * (x[i] - xx) * (x[i] - xx) * (x[i] - xx);
        cout << "Expected: " << roundElem(y[i])  << " Received: " << roundElem(res) << " Dif: "<<  roundElem(res) - roundElem(y[i]) << "\n";
    }
    for (int i = 0; i < n; i++){
        float xx = a+i*h;
        float ddd = (x[i] + (h / 2) - xx);
        float res = aa[i+1] + bb[i+1] * ddd +
        c[i] * ddd * ddd +
        d[i] * ddd * ddd * ddd;
        float exp = sin (x[i] + (h/2));
        float inaccuracy = exp - res;
        cout << "Expected: " << roundElem(exp) << " Received: " << roundElem(res) << " Dif: "<<  inaccuracy << "\n";
    }
    return 0;
}
