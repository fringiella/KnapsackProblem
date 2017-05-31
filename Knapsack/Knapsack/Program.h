#include <queue>
#include <vector>
#include "Knapsack.h"
#include "Node.h"
#ifndef MAIN_H
#define MAIN_H
class Program
{
private:
	double PCFreq;
	__int64 counter;
	int c(int i, int S);
	int F(int k, int y);
	int ** dynamicResult;
	int *scaledValues;	
	int ** fptasResult;	
	double Average(vector<double> vals);
	Knapsack dynamicKnapsack;
	Knapsack fptasKnapsack;
	Knapsack fptasResultKnapsack;
	bool testing;
	int bestValue;
public:
	void StartTimer();
	double GetTimeAndStopTimer();
	Knapsack GetKnapsackFromFile(string path, int weight);
	double Bound(Node node, Knapsack knapsack);
	Knapsack BranchAndBound(Knapsack knapsack);
	Knapsack Bruteforce(Knapsack knapsack);
	void CinInt(int &number);
	Knapsack DynamicProgramming(double &time, Knapsack testKnapsack);
	Knapsack FPTAS(float epsilon, double &time, Knapsack testKnapsack, float &resultValue);
	Knapsack DynamicProgrammingBasedOnValue(double &time, Knapsack testKnapsack);
	void TestQuality(int weight,
	int startItems, int stepItems, int maxItems, float eps);
	void Tests(int startWeight, int stepWeight, int maxWeight,
	int startItems, int stepItems, int maxItems, int algorithm);
	
};
#endif