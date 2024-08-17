#include <iostream>
using namespace std;
const int N = 2;
const double h = 0.1, eps = pow(10, -6), e = 2.7182818284;

double f(double x, double y, double y1)
{
    //return ((pow(e, x) + y1 + y) / 3);
    return ((x + 2) * pow(e, x));
}

double rk2vr(double x[N], double y[N], int o)
{
    int i = 1, j, k;
    double Yh[N], Yh2[N], Ysr[N], H = h, X, Xh2, a;
    do
    {
        a = 0;
        if (o == 1)
        {
            cout << " Шаг " << i << ": h = " << H << endl;
            cout << " X\t\t\tY\t\t\tY'\n";
        }
        for (j = 0; j < N; j++)
        {
            Yh[j] = y[j];
            Yh2[j] = y[j];
        }
        if (o == 1)
            printf(" %.9f\t\t%.9f\t\t%.9f\n", x[0], Yh[0], Yh[1]);
        for (X = x[0]; X < x[1] - H + 0.0000001; X += H)
        {
            for (j = 0; j < N; j++)
            {
                if (j != N - 1)
                    Ysr[j] = Yh[j] + H / 2 * Yh[j + 1];
                else
                    Ysr[j] = Yh[j] + H / 2 * f(X, Yh[0], Yh[1]);
            }
            for (j = 0; j < N; j++)
            {
                if (j != N - 1)
                    Yh[j] += H * Ysr[j + 1];
                else
                    Yh[j] += H * f(X + H / 2, Ysr[0], Ysr[1]);
            }

            for (Xh2 = X, k = 0; k < 2; k++, Xh2 += H / 2)
            {
                for (j = 0; j < N; j++)
                {
                    if (j != N - 1)
                        Ysr[j] = Yh2[j] + H / 4 * Yh2[j + 1];
                    else
                        Ysr[j] = Yh2[j] + H / 4 * f(Xh2, Yh2[0], Yh2[1]);
                }
                for (j = 0; j < N; j++)
                {
                    if (j != N - 1)
                        Yh2[j] += H / 2 * Ysr[j + 1];
                    else
                        Yh2[j] += H / 2 * f(Xh2 + H / 4, Ysr[0], Ysr[1]);
                }
            }
            if ((abs(Yh[N - 1] - Yh2[N - 1]) < 3 * eps))
                a++;
            if (o == 1)
                printf(" %.9f\t\t%.9f\t\t%.9f\n", X + H, Yh2[0], Yh2[1]);
        }
        H /= 2;
        i++;
        if (o == 1)
            cout << endl << "___________________________" << endl;
    } while (a != (x[1] - x[0]) / (2 * H));
    return Yh[0];
}

void strlb(double x[N], double y[N], double y2)
{
    int i = 1;
    double a = -10, b = 10;
    do
    {
        cout << " Шаг " << i << ":";
        y[N - 1] = (b + a) / 2;
        printf(" [%.9f; %.9f] y' = %.9f\n", a, b, y[N - 1]);
        if (rk2vr(x, y, 0) > y2)
            b = y[N - 1];
        else
            a = y[N - 1];
        i++;
    } while (!(abs(rk2vr(x, y, 0) - y2) < eps));
    cout << " Конец стрельб" << endl;
    rk2vr(x, y, 1);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double x[N] = { 0,1 }, y[N] = { 0 }, y2 = e;
    //double x[N] = { 0,1 }, y[N] = { 1 }, y2 = e;
    strlb(x, y, y2);
    return 0;
}