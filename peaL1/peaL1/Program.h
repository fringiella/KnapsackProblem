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
public:
	void StartTimer();
	double GetTimeAndStopTimer();
	Knapsack GetKnapsackFromFile(string path, int weight);
	double Bound(Node node, Knapsack knapsack);
	Knapsack BranchAndBound(Knapsack knapsack);
	//vector<Knapsack> PowerSet(Knapsack knapsack);
	//Knapsack Bruteforce(Knapsack knapsack);
	Knapsack bruteforce(Knapsack knapsack);
};
#endif