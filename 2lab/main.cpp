#include <cmath>
#include <iostream>

using namespace std;

double okr(double X, double eps)
{
    int i = 0;
    while (eps != 1)
    {
        i++;
        eps *= 10;
    }
    int okr = pow(double(10), i);
    X = int(X * okr + 0.5) / double(okr);
    return X;
}

double normOfMatrix(double A[3][3], int N)
{ //норма матрицы А
    double sum = 0;
    double sums[3];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            sum += abs(A[i][j]);
        }
        sums[i] = sum;
        sum = 0;
    }
    double norm = sums[0];
    for (int i = 1; i < N; i++)
    {
        if (sums[i] > norm)
        {
            norm = sums[i];
        }
    }
    return norm;
}

double iterat(double A[3][3], double B[3], int N, double eps)
{
    double matrixNorm = normOfMatrix(A, N);
    double coef = (matrixNorm / (1 - matrixNorm));
    double vectorNorm;
    if (matrixNorm < 1)
    {
        cout << "\nНорма матрицы A = " << matrixNorm << " < 1  => сходится в Евклидовой метрике\n"
             << std::endl;

        int k = 0;
        int i, j;
        double X[N];
        double s, g, diff;
        do
        {
            s = 0;
            k++;
            for (i = 0; i < N; i++)
            {
                g = B[i];
                for (j = 0; j < N; j++)
                {
                    g += A[i][j] * X[j];
                }
                cout << "X" << i + 1 << " = " << g << endl;
                diff = X[i] - g; // delta x
                cout << "X" << i + 1 << "(прошлый) - X" << i + 1 << "(новый) = " << diff << "\n"
                     << endl;
                s += diff * diff; // (delta x) ^ 2
                X[i] = g;
            }
            vectorNorm = sqrt(s); // norm of vector = sqrt(sum of X^2)
            cout << "Норма (X" << i + 1 << " - X" << i << ") = " << vectorNorm << endl;

            int iter = (int)(log((log(1 - matrixNorm) * log(eps)) / (log(vectorNorm) * log(matrixNorm))));
            cout << "\nКоличество оставшихся итераций: k = " << iter << "\n"
                 << endl;

        } while ((coef * vectorNorm) >= eps);

        cout << "\nРешение системы:" << endl;
        for (i = 0; i < N; i++)
        {
            cout << "X" << i << " = " << okr(X[i], eps) << endl;
        }
        cout << "\nЧисло итераций: " << k - 1 << "\n"
             << endl;
    }
    else
    {
        cerr << "Условие сходимости не выполняется!\n"
             << endl;
    }
    return 0;
}

int main()
{
    int N = 3, i, j;

    double A[3][3] = {
        {3.1, -1.5, 1},
        {0.8, -3, 1.4},
        {-1, 1.2, 2.7},
    };
    double B[3] = {-1, 0, 2};

    double C[3][4];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            if (j != N)
            {
                C[i][j] = A[i][j];
            }
            else
            {
                C[i][j] = B[i];
            }
        }
    }

    cout.precision(5);     // 5 цифр после запятой
    cout.setf(ios::fixed); // фиксированный формат цифр после запятой
    double eps;
    cout << "Введите точность вычислений: ";
    cin >> eps;
    cout << "\nМатрица A:" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\nСтолбец свободных членов:" << endl;
    for (i = 0; i < N; i++)
    {
        cout << "X" << i + 1 << " = " << B[i] << endl;
    }

    // triangulation
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double ratio = C[i][j] / C[i][i];
            for (int k = j; k < N + 1; k++)
            {
                C[i][k] -= ratio * C[j][k];
            }
        }
    }

    //частичная поворотность, чтобы сделать уравнения диагонально доминирующими
    for (i = 0; i < N; i++)
    {
        for (int k = 0; k < N + 1; k++)
        {
            if (abs(C[i][i]) < abs(C[k][i])) // сравнить абсолютные значения
            {
                for (j = 0; j <= N; j++)
                { // обмен
                    double temp = C[i][j];
                    C[i][j] = C[k][j];
                    C[k][j] = temp;
                }
            }
        }
    }

    // приведение к виду для итераций
    for (int i = 0; i < N; i++)
    {
        double ratio = C[i][i];
        for (int j = 0; j < N + 1; j++)
        {
            C[i][j] /= ratio;
        }
    }

    //разделяем С на А и B
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            if (j != N)
            {
                A[i][j] = C[i][j];
            }
            else
            {
                B[i] = C[i][j];
            }
        }
    }

    cout << "\nМатрица А, приведённая к нормальному виду:" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    // матрица E- A
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = -A[i][j];
            if (i == j)
            {
                A[i][j] = A[i][j] + 1;
            }
        }
    }

    cout << "\nМатрица (E - А):" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    iterat(A, B, N, eps);
    return 0;
}