//Name: Angelos Mavrogiannis
//Andrew ID: angelosm
//Date: 11/20/2018
//Course: Engineering Computation _Section B
//Problem Set 12 - Multi-threaded PI

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <thread>
#include <vector>


#define PI 3.14159265358979323846 //keeping 20 decimal points as on lecture problem

// Calculates area of a circle with radius=1.0
class UnitCircleAreaCalculator
{
public:
	double area;
	double d;
	double x0, x1, y0, y1;

	static void ThreadEntry(UnitCircleAreaCalculator *thisPtr);
	void Calculate(void);
};

/* static */ void UnitCircleAreaCalculator::ThreadEntry(UnitCircleAreaCalculator *thisPtr)
{
	thisPtr->Calculate();
}

void UnitCircleAreaCalculator::Calculate(void)
{
	const double dA = d * d;
	area = 0.0;
	for (double y = y0; y < y1; y += d)
		for (double x = x0; x < x1; x += d)
			if (x * x + y * y < 1.0)
				area += dA;
}

double absoluteValue(double input) { //made this function because freefood was throwing an error
	if (input >= 0)					//due to the use of abs()
		return input * 1;
	else
		return input * (-1);
}

int main(void)
{
	std::vector <int> nThread {2, 4, 6, 8}; //using vectors so that the resolution and the number of
	std::vector <double> resolution {100, 1000, 10000, 100000}; //threads used is adjustable
	std::vector <int> timeElapsed;
	std::vector <double> error;
	std::vector <double> piValues;
	std::vector <int> res;
	std::vector <int> thr;
	for (int j = 0; j < nThread.size(); j++) {
		for (int k = 0; k < resolution.size(); k++) {
			time_t t0 = time(NULL);
			std::vector <UnitCircleAreaCalculator> calcParam;
			calcParam.resize(nThread[j]);
			for (int y = 0; y < nThread[j]; ++y)
			{
				const double y0 = (double)y / (double)nThread[j];       //calculating the area of
				const double y1 = (double)(y + 1) / (double)nThread[j];// a quarter circle only
				calcParam[y].d = 1 / resolution[k];
				calcParam[y].x0 = 0.0;
				calcParam[y].x1 = 1.0;
				calcParam[y].y0 = y0;
				calcParam[y].y1 = y1;
			}

			std::vector <std::thread> threadArray;
			threadArray.resize(nThread[j]);
			for (int i = 0; i < nThread[j]; ++i)
			{
				// Thread can be moved or swapped, but cannot be copied!
				std::thread
					t(UnitCircleAreaCalculator::ThreadEntry, &calcParam[i]);
				threadArray[i].swap(t);
			}

			double area = 0.0;
			for (int i = 0; i < nThread[j]; ++i)
			{
				threadArray[i].join();
				area += calcParam[i].area;
			}
			thr.push_back(nThread[j]);    //storing the resulting value of PI, the percent error (compared to the true
			res.push_back(resolution[k]);//value of PI),and the elapsed time for the calculation
			timeElapsed.push_back((int)(time(NULL) - t0));
			error.push_back(absoluteValue((4 * area - PI) / PI) * 100);
			piValues.push_back(4 * area);
		}
	}

	//printing in a format that looks like a meaningful array
	for (int i = 0; i < nThread.size() * resolution.size(); i++) {
		if (i == 0) {
			std::cout << std::setw(10) << "Run" << std::setw(13) << "Resolution" << std::setw(11) <<
				"Threads" << std::setw(11) << "Time" << std::setw(14) << "Error (%)"
				<< std::setw(25) << "Value" << std::endl;
		}
		std::cout << std::setprecision(8) << std::fixed;
		std::cout << std::setw(10) << i + 1 << " " << std::setw(12) << res[i] << " " << std::setw(10) << thr[i] << " ";
		std::cout << std::setw(10) << timeElapsed[i] << "    " << std::setw(10) << error[i] << "    ";
		std::cout << std::setprecision(20) << std::fixed; //keeping 20 decimal points as we did on
		std::cout << std::setw(10) << piValues[i] << std::endl;//the lecture example
	}

	return 0;
}
