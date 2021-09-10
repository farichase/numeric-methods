#include "iostream"
#include "vector"
using namespace std;


vector<float> calculate(vector<float> a, vector<float> b, vector<float> c, vector<float> d, int n){
    vector<float> alfa(n), beta(n);
    alfa[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];
    for (int i = 1; i < n; i++){
        float t = b[i] + a[i-1] * alfa[i-1];
        float t2 = d[i] - a[i-1] * beta[i - 1];
        cout << t << " ";
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

int main(){
    int n;
    cin >> n;
    vector<vector<float>> matrix(n, vector<float>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    vector<float> a(n), b(n), c(n), d(n);
    for (int j = 0; j < n; j++) {
        cin >> d[j];
        b[j] = matrix[j][j];
    }
    for (int j = 0; j < n-1; j++) {
        a[j] = matrix[j+1][j];
        c[j] = matrix[j][j+1];
    } 
    vector<float> x = calculate(a, b, c, d, n); 
    for (int j = 0; j < n; j++) {
        cout << x[j] << " ";
    }
    return 0;
}
/*
4
4 1 0 0 
1 4 1 0
0 1 4 1
0 0 1 4
5 6 6 5
g++ lab1.cpp -o lab1
*/