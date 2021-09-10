#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

float func(float x) {
    return 3 * exp(x);
}
float func2 (float x) {
    return 0.5*exp(x)*(3*x*x + 2*x + 4);
}
vector<float> calculate(vector<vector<float>> table,vector<float> d, int n){
    vector<float> alfa(n), beta(n);
    alfa[0] = -table[0][1] / table[0][0];
    beta[0] = d[0] / table[0][0];
    for (int i = 1; i < n; i++){
        float t = table[i][i-1] * alfa[i-1] + table[i][i];
        float t2 = d[i] - table[i][i-1] * beta[i - 1];
        alfa[i] = -table[i][i+1] / t;
        beta[i] = t2 / t;
    }
    alfa[n-1] = -1;
    vector<float> x (n);
    x[n-1] = beta[n-1];
    for (int i = n-1; i > 0; i--){
        x[i-1] = alfa[i-1] * x[i] + beta[i-1];
    }
    return x;
}
int main() { 
    int n = 10;
    float y0 = 2.f;
    float p = -2.f, q = 1.f;
    float h = 1.f / n, y1 = func2(1);
    vector<vector<float>> table (n+1);
    vector<float> d (n+1);
    for (int i = 0; i < n + 1; i ++){
        table[i] = vector<float> (n+1);
    }
    for (int i = 1; i < n; i++){
        table[i][i-1] = 1.f - h / 2.f * p;
        table[i][i] = h * h * q - 2.f;
        table[i][i+1] = 1.f + h / 2.f * p;
    }
    table[0][0] = 1.f;
    table[n][n] = 1.f;
    for (int i = 1; i < n; i++){
        float x = i * h;
        d[i] = h * h * func(x);
    }
    d[0] = y0;
    d[n] = y1;
    vector<float> y = calculate(table, d, n + 1);
    for (int i = 0 ; i < y.size(); i++){
        float y2 = func2(i * h);
        cout << "y = " << y2 << " y(x) = " << y[i] << " " << abs(y[i] - y2) << "\n";
    }
    return 0; 
}
