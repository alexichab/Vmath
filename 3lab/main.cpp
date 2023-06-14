#include <stdio.h>
#include <math.h>
#include <iostream> 

#define maxrept 1000  //максимум итераций

using namespace std;

double f(double x){  //функция f(x)
    return (x - exp(-x));
    //(sqrt (x) - pow (x, -1) * log (x) + 4 - 1.5);
}

double df(double x){  //Производная f(x)
    return (1 + exp(-x));
    //((0.5*sqrt(x)) - (1-log(x))/(pow(x,2)));
    //return ((1/2*sqrt(x))+((log(x)-1))/pow(x, 2));
    // return ((log(x)/pow(x,2))-(1/pow(x,2))+0.5*(1/sqrt(x)));
}

double iterate(double x){  //функция Ньютона
    return (x - f(x) / df(x));
}

int main(){
    double x1, d;
    double x0 = 0.5;  //начальное значение итерации x0
    double eps = 0.000001;  //Точность вычислений eps
    int k = 0;  //Число итераций

    do{
        k++;
        x1 = iterate(x0);
        cout << k <<",\t  " << x1 << "\n";
        d = fabs(x1 - x0);
        x0 = x1;
    }while(d >= eps && k < maxrept);
    if(k < maxrept)  cout << "Корень f(x) =0 это : x =" << x1 << ", k =" << k <<"\n";
    else cout << "\n" << "ОШИБКА!\n";

    return 0;
}
