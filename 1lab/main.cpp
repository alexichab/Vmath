#include <iostream>
using namespace std;

double * gauss(double **elem, double *y, int n)
{
  double *x, max;
  int k, index;
  x = new double[n];
  k = 0;
  while (k < n)
  {
    // Search max element
    max = (elem[k][k]);
    index = k;
    for (int i = k + 1; i < n; i++)
    {
      if ((elem[i][k]) > max)
      {
        max = (elem[i][k]);
        index = i;
      }
    }
    if (max < 0.00001)
    {
      cout << "No solution"; //if only null elements
      return 0;
    }
    for (int j = 0; j < n; j++)
    {
      double temp = elem[k][j];
      elem[k][j] = elem[index][j];
      elem[index][j] = temp;
    }
    double temp = y[k];
    y[k] = y[index];
    y[index] = temp;
      
    for (int i = k; i < n; i++)
    {
      double temp = elem[i][k];
      if ((temp) < 0.00001) continue; // skip if num 0
      for (int j = 0; j < n; j++)
        elem[i][j] = elem[i][j] / temp;
      y[i] = y[i] / temp;
      if (i == k)  continue; // skip if equation the same
      for (int j = 0; j < n; j++)
        elem[i][j] = elem[i][j] - elem[k][j];
      y[i] = y[i] - y[k];
    }
    k++;
  }
  for (k = n - 1; k >= 0; k--)
  {
    x[k] = y[k];
    for (int i = 0; i < k; i++)
      y[i] = y[i] - elem[i][k] * x[k];
  }
  return x;
}

void output(double **a, double *y, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << a[i][j] << "*x" << j;
      if (j < n - 1)
        cout << " + ";
    }
    cout << " = " << y[i] << endl;
  }
  return;
}

int main()
{
  double **a, *y, *x;
  int n;
  cout << "Enter the number of equations: ";
  cin >> n;
  a = new double*[n];
  y = new double[n];
  for (int i = 0; i < n; i++)
  {
    a[i] = new double[n];
    for (int j = 0; j < n; j++)
    {
      cout << "a[" << i << "][" << j << "]= ";
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++)
  {
    cout << "y[" << i << "]= ";
    cin >> y[i];
  }
  output(a, y, n);
  x = gauss(a, y, n);
  for (int i = 0; i < n; i++)
    cout << "x[" << i << "]=" << x[i] << endl;
  cin.get(); cin.get();
  return 0;
}
