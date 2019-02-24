// Stat_values_using_threads.cpp : Uses an array and determines stat values.
// By Ian Workman

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <math.h> 
using namespace std;

//global values to be used
double avg;
double min;
double max;
double med;
double stdDev;

//prototype area
void average(double arr[], int n);
void minimum(double arr[], int n);
void maximum(double arr[], int n);
void median(double arr[], double sort[], int n);
void standard_deviation(double arr[], int n);

int _tmain(int argc, _TCHAR* argv[])
{
	//variable and array list
	const int size = 7;
	double list[size] = { 90, 81, 78, 95, 79, 72, 85 };
	double sorted[size];

	//thread list
	thread ma, mi, av, me, sd;

	//run threads
	ma = thread(maximum, list, size);
	mi = thread(minimum, list, size);
	av = thread(average, list, size);
	me = thread(median, list, sorted, size);
	sd = thread(standard_deviation, list, size);

	//join threads
	ma.join();
	mi.join();
	av.join();
	me.join();
	sd.join();

	//output
	cout << "For the array of: \n";
	for (int i = 0; i < size; i++)
	{
		cout << list[i] << " ";
	}
	cout << "\nMaximum value: " << max << "\nMinimum value: " << min
		<< "\nAverage value: " << avg << "\nMedian Value: " << med
		<< "\nStandard Deviation: " << stdDev << "\n";

	return 0;
}

//calculate the average of an array of doubles of size n
void average(double arr[], int n)
{
	//find sum
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}

	//find average and stoe in global variable
	avg = sum / n;
}

//find the minimum value of a double array
void minimum(double arr[], int n)
{
	min = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
}

//find the maximum value of a double array
void maximum(double arr[], int n)
{
	max = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
}

// find the median of a double array
void median(double arr[], double sort[], int n)
{
	//copy the original array to another array 
	for (int i = 0; i < n; i++)
	{
		sort[i] = arr[i];
	}

	//sort the new array
	double temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (sort[j] > sort[j + 1])
			{
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}

	//median is in the middle of the sorted array
	med = sort[n / 2];
}

//find the standard deviation of a double array of size n
void standard_deviation(double arr[], int n)
{
	//variable to hold the sum part of the stand deviation
	double numSum = 0;
	for (int i = 0; i < n; i++)
	{
		numSum += pow((arr[i] - avg), 2);
	}

	//find the standard deviation
	stdDev = sqrt(numSum / (n));
}
