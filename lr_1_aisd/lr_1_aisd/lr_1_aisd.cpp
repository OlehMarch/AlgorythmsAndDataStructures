// lr_1_aisd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "cmath"
#include <conio.h>
#include "time.h"
const double eps = 0.00000001;
using namespace std;
//----------------------------------------------------------------------------------------------------------------------------------
bool checkError(double value) {
	if (value <= 1) {
		return false;
	}
	else {
		return true;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
double calculationsByStandartFuncs(double x) {
	double y;
	y = 5.0 * x - log(pow(1.0 - x, 2));
	return y;
}
//----------------------------------------------------------------------------------------------------------------------------------
double calculationsByCycles(float x) {
	double element = (x - 1.0) / (x + 1.0);
	double incrementOfElement = (x - 1.0) * (x - 1.0) / (x + 1.0) / (x + 1.0);
	double sum = 0.0;
	for (double i = 1.0; fabs(element) > eps; i += 2.0) {
		sum += element / i;
		element *= incrementOfElement;
	}
	return 2.0 * sum;
}
//----------------------------------------------------------------------------------------------------------------------------------
double calculationsByRecursion(float x, double element = 1., double incrementOfElement = 1., double i = 1., double sum = 0.) {
	return (fabs(element) > eps) ? calculationsByRecursion(x, (i == 1) ? (element = (x - 1.0) / (x + 1.0)) : element *= incrementOfElement, incrementOfElement = (x - 1.0) * (x - 1.0) / (x + 1.0) / (x + 1.0), i += 2., sum += element / i) : (2.0 * sum);
}
//----------------------------------------------------------------------------------------------------------------------------------
void _tmain(int argc, _TCHAR* argv[]) {
	float x = 0.;
	double y = 0.;
	double since, now;

	cout<<"Function to calculate:\n\n	5*x - ln((1 - x)^2)\n\nPlease insert value X = ";
	cin>>x;

	if (!checkError(x)) {
		cout<<"\nInserted value must be more then 1!\n\nPress any key to continue...";
		_getch();
		return;
	}

	since = clock();
	y = calculationsByStandartFuncs(x);
	now = clock()-since;	
	printf("\nCalculation which perfomed  12by standart function:\n y = %.10f\n", y);
	cout<<"Elapsed time to perform this function - "<<now/CLOCKS_PER_SEC<<endl;

	since = clock();
	y = calculationsByCycles(x);
	now = clock() - since;
	printf("\nCalculation which perfomed by cycling function:\n y = %.10f\n", 5 * x - 2 * y);
	cout<<"Elapsed time to perform this function - "<<now<<endl;

	since = clock();
	y = calculationsByRecursion(x);
	now = clock()-since;
	printf("\nCalculation which perfomed by recursion function:\n y = %.10f\n", 5 * x - 2 * y);
	cout<<"Elapsed time to perform this function - "<<now/CLOCKS_PER_SEC<<endl<<endl;

	cout<<"Press any key to continue...";
	_getch();
}