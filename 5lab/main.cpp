#include <stdio.h>
#include <iostream>
#include <math.h>
 
 typedef  double(*pointFinc)(double);

double y(double x)
{
    return (exp(-x*x));
}
 
// Функция для оценки значения интеграла
double trapezoidal(double a, double b, double n)
{
    // шаг сетки
    double h = (b-a)/n;
 
   //Вычисление суммы первого и последнего членов в приведенной формуле
    double s = y(a)+y(b);
 
    // Добавляем средние члены в приведенную выше формулу
    for (int i = 1; i < n; i++)
        s += 2*y(a+i*h);
 
    // h/2 указывает (b-a)/2n. Умножение h/2 на s.
    return (h/2)*s;
}
 
int main()
{   
    double x0,xn;
    int n;
    // Диапазон определенного интеграла
    std::cout << "Введите диапазон по очереди \n";
    std::cin >> x0;
    std::cin >> xn;
    

    // Количество разбиений. Более высокое значение означает больше точности
    std::cout << "Введите количество разбиений\n";
    std::cin >> n;
    
    std::cout << "Значение интеграла " << trapezoidal(x0,xn,n) << "\n";
    return 0;
}
