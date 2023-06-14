#include <bits/stdc++.h>
using namespace std;
 
float dydx(float x, float y) // y(x)'= x+y(x)
{
    return(x + y);
}
  
//Находит значение y для данного x, используя размер шага h и начальное значение y0 в точке x0.
float rungeKutta(float x0, float y0, float x, float h)
{
    int n = (int)((x - x0) / h);// Подсчитываем количество итераций, используя размер шага
                                // или высоту h
    float k1, k2, k3, k4;
    float y = y0;

    cout << "x" << "\t" << "y" << "\n";
    for (int i=1; i<=n; i++)
    {
        //Применяем формулу Рунге Кутты, чтобы найти последующие значения y
        k1 = h*dydx(x0, y);
        k2 = h*dydx(x0 + 0.5*h, y + 0.5*k1);
        k3 = h*dydx(x0 + 0.5*h, y + 0.5*k2);
        k4 = h*dydx(x0 + h, y + k3); 
        y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);;//Обновляем значение y
        x0 = x0 + h;// обновляем значение x
        cout << x0 <<"\t" << y << "\n";// Выводим значение X и Y;
    }
  
    return y;
}
 
int main()
{
    float x0 = 0, y = 1, x = 10, h = 0.2;//y(0)=1; x(0;10);
    cout << "Значение y в точке x равно:     \n" <<
            rungeKutta(x0, y, x, h) << "\n";
 
    return 0;
}
