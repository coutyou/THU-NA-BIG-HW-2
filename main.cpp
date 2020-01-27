#include <stdio.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

const double PI = 3.14159265358979;

double mySqrt(double x)
{
	double res = x;
    double e = 1e-15;
	while(res*res-x > e || x-res*res > e)
    {
		res = 0.5*(res + x/res);
    }
	return res;
}

double myPow(double base, int index)
{
    double res = 1;
    if (index >= 0)
    {
        for (int i = 0; i < index; i++)
        {
            res *= base;
        }
    }
    else
    {
        for (int i = 0; i < -index; i++)
        {
            res /= base;
        }
    }
    return res;
}

double normalizeX(double x)
{
    if (x > PI)
    {
        do
        {
            x = x - 2*PI;
        } while (x > PI);
    }
    else if (x < -PI)
    {
        do
        {
            x = x + 2*PI;
        } while (x < -PI);
    }
    return x;
}

bool checkOK(double curTerm, double x, int index, int m)
{
    if (curTerm * x / (index+1) > 0.5 * myPow(10,-m))
    {
        return false;
    }
    else
    {
        return true;
    }
}

double getNewTerm(double oldTerm, double x, int index)
{
    return oldTerm * x * x / (index+1) / (index+2);
}

double f(double y)
{   
    return mySqrt(1-y*y);
}

double calError(double h)
{
    return mySqrt(2)/3*h*h;
}

double getN(double x, int m)
{
    int n = 1;
    double h = x/n;
    while (calError(h) > 0.5*myPow(10,-m))
    { 
        n *= 2;
        h = x/n;   
    }
    return n;
}

double mySin(int opt, double x, int m)
{
    //Taylor
    if (opt == 1)
    {
        int index = 1;
        double curTerm = x;
        double res = x;
        int flag = 1;
        while (!checkOK(curTerm, x, index, m))
        {
            flag = -flag;
            curTerm = getNewTerm(curTerm, x, index);
            res += flag * curTerm;
            index += 2;
        }
        return res;
    }
    //Euler
    else
    {
        int n;
        double h;
        double res = 0;
        if (x < PI/4)
        {
            n = getN(x, m);
            h = x/n;
            for (int i = 0; i < n; i++)
            {
                res += h/2 * (f(res) + f(res + h*f(res)));
            }
        }
        else
        {
            x = PI/2-x;
            n = getN(x, m);
            h = x/n;
            for (int i = 0; i < n; i++)
            {
                res += h/2 * (f(res) + f(res + h*f(res)));
            }
            res = mySqrt(1 - res*res);
        }
        return res;
    }   
}

int main()
{
    double x;
    double inputX;
    double res_1;
    double res_2;
    int m;
    char ch = 0;
    while (ch!='q' && ch!='Q')
    {
        //Input x
        cout << "\nPls input x" << endl;
        cin.clear();
        cin.sync();
        cin >> inputX;
        if (inputX >= 10 || inputX <= -10)
        {
            cout << "\nInvalid input, pls input again !" << endl;
            continue;
        }

        //Normalize x
        x = normalizeX(inputX);

        //Input m
        cout << "\nPls input m in [1, 12], which is the least accuracy digit number after the decimal point" << endl;
        cin >> m;
        if (m <= 0 || m > 12)
        {
            cout << "\nInvalid input, pls input again !" << endl;
            continue;
        }

        // Transform
        if (x < -PI/2)
        {
            res_1 = -mySin(1, PI+x, m);
            res_2 = -mySin(2, PI+x, m);
        }
        else if (x < 0)
        {
            res_1 = -mySin(1, -x, m);
            res_2 = -mySin(2, -x, m);
        }
        else if (x == 0)
        {
            res_1 = 0;
            res_2 = 0;
        }
        else if (x < PI/2)
        {
            res_1 = mySin(1, x, m);
            res_2 = mySin(2, x, m);
        }
        else
        {
            res_1 = mySin(1, PI-x, m);
            res_2 = mySin(2, PI-x, m);
        }

        //Output result
        cout << setprecision(6) << "\nmySin(" << inputX << ") is "<< fixed << setprecision(m) << res_1 << "  ---Taylor Expansion" << endl;
        cout.unsetf(ios::fixed);

        cout << setprecision(6) << "\nmySin(" << inputX << ") is "<< fixed << setprecision(m) << res_2 << "  ---Improved Euler Method" << endl;
        cout.unsetf(ios::fixed);

        cout << setprecision(6) << "\n  Sin(" << inputX << ") is "<< fixed << setprecision(m) << sin(inputX) << "\n" << endl;
        cout.unsetf(ios::fixed);

        //Quit or not
        cout << "Press Q or q to quit, other key to continue" << endl;
        ch = getch();
    }
    return 0;
}