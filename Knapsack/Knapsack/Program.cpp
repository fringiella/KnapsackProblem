#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Windows.h"
#include "Item.h"
#include "Knapsack.h"
#include "Node.h"
#include "Program.h"
#include <iostream>
using namespace std;

void Program::CinInt(int &number)
{
	cin >> number;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "You can only enter numbers.\n";
		cout << "Enter a number.\n";
		cin >> number;
	}
}
void Program::StartTimer()
{

	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "Error!" << endl;

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	counter = li.QuadPart;
}
double Program::GetTimeAndStopTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double time = (li.QuadPart - counter) / PCFreq;
	counter = 0;
	return time;
}

Knapsack Program::GetKnapsackFromFile(string path, int weight)
{
	ifstream file(path);
	if (!file)
	{
		cout << "Couldn't open the file!" << endl;
	}
	else
	{
		int itemsNumber = 0, itemWeight = 0, itemValue = 0;
		file >> itemsNumber;
		if (itemsNumber == 0)
		{
			cout << "Error!" << endl;
			return 0;
		}
		else
		{
			Knapsack knapsack(weight);
			int i = 0;
			while (i < itemsNumber)
			{
				file >> itemWeight >> itemValue;
				Item item(i, itemWeight, itemValue);
				if (itemWeight == 0 || itemValue == 0)
				{
					cout << "Error!" << endl;
					return 0;
				}
				knapsack.AddItem(item);
				i++;
			}
			file.close();
			knapsack.SortItemsByValueToWeight();
			return knapsack;
		}
	}
}
double Program::Bound(Node node, Knapsack knapsack)
{
	int j = 0, k = 0;
	int totalWeight;
	double bound = 0;
	// the bound is 0 if weight of the node is bigger than knapsack's weight
	if (node.GetWeight() >= knapsack.GetMaxWeight())
		return 0;
	else
		bound = node.GetValue();

	j = node.GetLevel() + 1;

	totalWeight = node.GetWeight();

	while ((j < knapsack.GetItemsNumber()) && (totalWeight + knapsack.GetItemAt(j).GetWeight() <= knapsack.GetMaxWeight()))
	{
		totalWeight += knapsack.GetItemAt(j).GetWeight();
		bound += knapsack.GetItemAt(j).GetValue();
		j++;
	}

	k = j;

	if (k < knapsack.GetItemsNumber())
	{
		bound = bound + ((double)(knapsack.GetMaxWeight() - totalWeight) * knapsack.GetItemAt(k).GetValueToWeight());
	}
	return bound;

}
Knapsack Program::BranchAndBound(Knapsack knapsack)
{
	// priority queue ordering promising nodes by bound
	priority_queue <Node, vector <Node>, Node > queue;
	Node root;
	Node node;
	Node bestNode;
	int bestValue = 0;
	root.SetBound(Bound(root, knapsack));
	queue.push(root);
	while (!queue.empty())
	{
		root = queue.top();
		queue.pop();
		if (root.GetLevel() == -1)
			node.SetLevel(0);
		else if (root.GetLevel() != (knapsack.GetItemsNumber() - 1))
			node.SetLevel(root.GetLevel() + 1);

		// take or not to take an item
		//--------------------------------------
		// taking an item
		if (root.GetBound() > bestValue && root.GetLevel() < knapsack.GetItemsNumber() - 1)
		{
			node.SetWeight(root.GetWeight() + knapsack.GetItemAt(node.GetLevel()).GetWeight());
			node.SetValue(root.GetValue() + knapsack.GetItemAt(node.GetLevel()).GetValue());
			node.SetBound(Bound(node, knapsack));
			node.SetItems(root.GetItems());
			node.AddItem(knapsack.GetItemAt(node.GetLevel()));
			if (node.GetWeight() <= knapsack.GetMaxWeight() && node.GetValue() > bestValue)
			{
				bestValue = node.GetValue();
				bestNode = node;
			}

			if (node.GetBound() > bestValue)
			{
				queue.push(node);
			}
			//----------------------------------
			// not taking an item
			node.SetWeight(root.GetWeight());
			node.SetValue(root.GetValue());
			node.SetBound(Bound(node, knapsack));
			node.SetItems(root.GetItems());

			if (node.GetBound() > bestValue)
			{
				queue.push(node);
			}
			//----------------------------------
		}
	}
	return Knapsack(bestNode.GetValue(), bestNode.GetWeight(), bestNode.GetItems());
}


Knapsack Program:: Bruteforce(Knapsack knapsack)
{
	int size = knapsack.GetItemsNumber();
	int *tab = (int *)calloc(size, sizeof(int));
	int i = 0;
	int bestValue = 0;
	Knapsack bestKnapsack(0);

	while (true) 
	{
		int j = size;
		int tempWeight = 0;
		int tempValue = 0;
		int k;

		k = 1;
		for (j = 0; j < size; j++) 
		{
			tab[j] += k;

			k = tab[j] / 2;
			tab[j] = tab[j] % 2;
		}
		if (k) break;
		Knapsack tempKnapsack(0);
		for (k = 0; k < size; k++) 
		{
			if (tab[k] == 1)
			{
				tempWeight = tempWeight + knapsack.GetItemAt(k).GetWeight();
				tempValue = tempValue + knapsack.GetItemAt(k).GetValue();
				tempKnapsack.AddItem(knapsack.GetItemAt(k));
			}
		}

		if (tempValue > bestValue && tempWeight <= knapsack.GetMaxWeight()) 
		{
			bestValue = tempValue;
			bestKnapsack = tempKnapsack;
		}
		i++;
	}
	free(tab);
	return bestKnapsack;
}
int Program::c(int i, int S)
{
	int temp, temp2;
	if (i == 0 || S == 0)
		return 0;
	if (dynamicKnapsack.GetItemAt(i-1).GetWeight() > S)
	{
		return dynamicResult[i - 1][S];
	}
	else
	{
		temp = dynamicResult[i - 1][S];
		temp2 = dynamicResult[i - 1][S - dynamicKnapsack.GetItemAt(i - 1).GetWeight()]
			+ dynamicKnapsack.GetItemAt(i - 1).GetValue();
		return max(temp, temp2);
	}
}
Knapsack Program::DynamicProgramming(double &time, Knapsack testKnapsack)
{
	int temp, temp2;
	Knapsack knapsack;
	dynamicKnapsack = testKnapsack;
	dynamicResult = new int *[dynamicKnapsack.GetItemsNumber() + 1];
	for (int i = 0; i <= dynamicKnapsack.GetItemsNumber(); i++)
		dynamicResult[i] = new int[dynamicKnapsack.GetMaxWeight() + 1];
	StartTimer();

	for (int k = 0; k <= dynamicKnapsack.GetItemsNumber(); k++)
		for (int l = 0; l <= dynamicKnapsack.GetMaxWeight(); l++)
		{
			temp = c(k, l);
			dynamicResult[k][l] = temp;
		}
	time = GetTimeAndStopTimer();
	// backtracking
	int j = dynamicKnapsack.GetMaxWeight();
	for (int i = dynamicKnapsack.GetItemsNumber() ; i > 0; i--)
	{
		if (j - dynamicKnapsack.GetItemAt(i-1).GetWeight() >= 0)
		{
			temp = dynamicResult[i][j];
			temp2 = dynamicResult[i - 1][j - dynamicKnapsack.GetItemAt(i - 1).GetWeight()];
			if (temp == temp2 + dynamicKnapsack.GetItemAt(i - 1).GetValue())
			{
				Item item(dynamicKnapsack.GetItemAt(i - 1).GetID(), dynamicKnapsack.GetItemAt(i - 1).GetWeight(), dynamicKnapsack.GetItemAt(i - 1).GetValue());
				knapsack.AddItem(item);
				j = j - item.GetWeight();

			}
		}

	}
	
	for (int i = 0; i <= dynamicKnapsack.GetItemsNumber() ; i++)
		delete dynamicResult[i];
	return knapsack;
}
int Program::F(int k, int y)
{
	if (y == 0)
		return 0;
	else if (y >= 1 && k == 0)
		return MAXINT;
	
	else if (k >= 1 && y >= 1)
	{
		if (y - scaledValues[k - 1] < 0 ||
			fptasResult[k - 1][y - scaledValues[k - 1]] == MAXINT)
			return fptasResult[k - 1][y];
		else
			return min(fptasResult[k - 1][y], fptasResult[k - 1][y - scaledValues[k - 1]]
				+ fptasKnapsack.GetItemAt(k-1).GetWeight());
	}
}

// epsilon - maximum set error
Knapsack Program::FPTAS(float epsilon, double &time, Knapsack testKnapsack, float &resultValue)
{
	float max = 0;
	Knapsack fptasResultKnapsack;
	fptasKnapsack = testKnapsack;
	for (int i = 0; i < fptasKnapsack.GetItemsNumber(); i++)
	{
		if (fptasKnapsack.GetItemAt(i).GetValue() > max)
		{
			max = fptasKnapsack.GetItemAt(i).GetValue();
		}
	}

	float p_max = max;
	int result;

	// scalling factor
	float K = (epsilon * p_max) / (float)fptasKnapsack.GetItemsNumber();
	// if K is less than 1, algorithm will be normal dynamic programming without approximation
	if (K < 1) K = 1;

	// scalling all items by K
	scaledValues = new int[fptasKnapsack.GetItemsNumber()];
	for (int i = 0; i < fptasKnapsack.GetItemsNumber(); i++)
	{
		scaledValues[i] = floor((float)fptasKnapsack.GetItemAt(i).GetValue() / K);
	}

	p_max = floor(p_max / K);
	if (!testing)
	{
		cout << "Epsilon = " << epsilon << endl;
		cout << "Before scalling: " << endl << "p_max = " << p_max << endl;
		cout << "After scalling: " << endl;
		cout << "K = " << K << endl;
		cout << "p_max = " << p_max << endl;
	}

	fptasResult = new int *[fptasKnapsack.GetItemsNumber() + 1];
	int size = (fptasKnapsack.GetItemsNumber() * (int)p_max) + 1;
	for (int i = 0; i <= fptasKnapsack.GetItemsNumber(); i++)
		fptasResult[i] = new int[size];
	StartTimer();
	for (int l = 0; l <= fptasKnapsack.GetItemsNumber() * p_max; l++)
	{
		// Dynamic programming
		for (int k = 0; k <= fptasKnapsack.GetItemsNumber(); k++)
		{
			fptasResult[k][l] = F(k, l);
		}

		if (fptasResult[fptasKnapsack.GetItemsNumber()][l] <= fptasKnapsack.GetMaxWeight())
		{
			result = l;
		}
	}

	bestValue = result;
	time = GetTimeAndStopTimer();
	// backtracking
	for (int k = fptasKnapsack.GetItemsNumber(); k > 0; k--)
	{

		if (result - scaledValues[k - 1] >= 0)
		{
			if (fptasResult[k][result]
				== fptasResult[k - 1][result - scaledValues[k - 1]]
				+ fptasKnapsack.GetItemAt(k - 1).GetWeight())
			{
				Item item(fptasKnapsack.GetItemAt(k - 1).GetID(),
					fptasKnapsack.GetItemAt(k - 1).GetWeight(),
					fptasKnapsack.GetItemAt(k - 1).GetValue());
				fptasResultKnapsack.AddItem(item);
				result = result - scaledValues[k - 1];
			}
		}
	}


	for (int i = 0; i <= fptasKnapsack.GetItemsNumber(); i++)
		delete fptasResult[i];
	delete[]scaledValues;
	resultValue = (float)bestValue * K;

	return 	fptasResultKnapsack;

}

Knapsack Program::DynamicProgrammingBasedOnValue(double &time, Knapsack testKnapsack)
{
	float max = 0;
	Knapsack knapsack;
	fptasKnapsack = testKnapsack;
	for (int i = 0; i < fptasKnapsack.GetItemsNumber(); i++)
	{
		if (fptasKnapsack.GetItemAt(i).GetValue() > max)
		{
			max = fptasKnapsack.GetItemAt(i).GetValue();
		}
	}

	scaledValues = new int[fptasKnapsack.GetItemsNumber()];
	for (int i = 0; i < fptasKnapsack.GetItemsNumber(); i++)
	{
		scaledValues[i] = floor((float)fptasKnapsack.GetItemAt(i).GetValue());
	}
	int temp, temp2, wynik;

	fptasResult = new int *[fptasKnapsack.GetItemsNumber() + 1];
	int rozmiar = (fptasKnapsack.GetItemsNumber() * (int)max) + 1;
	for (int i = 0; i <= fptasKnapsack.GetItemsNumber(); i++)
		fptasResult[i] = new int[rozmiar];
	StartTimer();

	for (int l = 0; l <= fptasKnapsack.GetItemsNumber() * max; l++)
	{
		for (int k = 0; k <= fptasKnapsack.GetItemsNumber(); k++)
		{
			fptasResult[k][l] = F(k, l);
		}
		if (fptasResult[fptasKnapsack.GetItemsNumber()][l] <= fptasKnapsack.GetMaxWeight())
		{
			wynik = l;
		}
	}
	time = GetTimeAndStopTimer();
	// backtracking
	int j = wynik;
	for (int k = fptasKnapsack.GetItemsNumber(); k > 0; k--)
	{

		if (j - fptasKnapsack.GetItemAt(k - 1).GetValue() >= 0)
		{
			if (fptasResult[k][j]
				== fptasResult[k - 1][j - fptasKnapsack.GetItemAt(k - 1).GetValue()]
				+ fptasKnapsack.GetItemAt(k - 1).GetWeight())
			{
				Item item(fptasKnapsack.GetItemAt(k - 1).GetID(),
					fptasKnapsack.GetItemAt(k - 1).GetWeight(),
					fptasKnapsack.GetItemAt(k - 1).GetValue());
				knapsack.AddItem(item);
				j = j - fptasKnapsack.GetItemAt(k - 1).GetValue();
			}
		}
	}

	for (int i = 0; i <= fptasKnapsack.GetItemsNumber(); i++)
		delete fptasResult[i];
	return knapsack;
}

double Program::Average(vector<double> vals)
{
	double result = 0.0;

	for (int i = 0; i < vals.size(); i++)
	{
		result += vals[i];
	}

	if (vals.size() == 0)
		return 0;
	else
	{
		result /= (vals.size());
		return result;
	}

}

void Program::Tests(int startWeight, int stepWeight, int maxWeight,
	int startItems, int stepItems, int maxItems, int algorithm)
{
	float epsilon = 0;
	fstream file;
	string filename = "";
	vector <double> times;
	if (algorithm == 1)
	{
		filename = "resultBruteforce";
	}
	else if (algorithm == 2)
	{
		filename = "resultBB";
	}
	else if (algorithm == 3)
	{
		filename = "resultDynamicProgramming";
	}
	else if (algorithm == 4)
	{
		filename = "resultDynamicProgrammingBasedOnValue";
	}
	else if (algorithm == 5)
	{
		while (true)
		{
			cout << "Epsilion?" << endl;
			cin >> epsilon;
			if (epsilon < 1 && epsilon > 0) break;
			else cout << "Epsilon must be less than 1 and more than 0!" << endl;
		}
		filename = "resultFPTAS_" + to_string(epsilon);
	}
	else
	{
		return;
	}
	testing = true;
	// dopisanie na koncu nazwy maksymalnej wagi i liczby przedmiotow
	string s = "_" + to_string(maxWeight) + "_" + to_string(maxItems);
	filename += s + ".txt";
	file.open(filename, ios::out);

	cout << "Order of result in a file" << endl;
	for (int i = startWeight; i <= maxWeight; i += stepWeight)
	{
		cout << "Weight: " << i << endl;
		for (int j = startItems; j <= maxItems; j += stepItems)
		{
			cout << "Items number " << j << endl;
			for (int l = 0; l < 100; l++)
			{
				Knapsack knapsack(i);
				knapsack.GenerateItems(j);
				double dynamicTime = 0;
				StartTimer();
				if (algorithm == 1)
				{
					Bruteforce(knapsack);
					times.push_back(GetTimeAndStopTimer());
				}
				else if (algorithm == 2)
				{
					BranchAndBound(knapsack);
					times.push_back(GetTimeAndStopTimer());
				}
				else if (algorithm == 3)
				{
					GetTimeAndStopTimer();

					DynamicProgramming(dynamicTime, knapsack);
					times.push_back(dynamicTime);
				}
				else if (algorithm == 4)
				{
					GetTimeAndStopTimer();
					DynamicProgrammingBasedOnValue(dynamicTime, knapsack);
					times.push_back(dynamicTime);
				}
				else if (algorithm == 5)
				{
					GetTimeAndStopTimer();
					float result = 0;
					FPTAS(epsilon, dynamicTime, knapsack, result);
					times.push_back(dynamicTime);
				}

			}
			file << Average(times) << endl;
			times.clear();
		}
	}
	testing = false;
	file.close();
}

void Program::TestQuality(int weight,
	int startItems, int stepItems, int maxItems, float eps)
{
	testing = true;
	fstream file1, file2, file3;
	string s = to_string(startItems) + "_" + to_string(maxItems) + "_" + to_string(eps) + ".txt";
	string filename1 = "fptasQualityOptim" + s;
	string filename2 = "fptasQualityApprox" + s;
	string filename3 = "fptasQualityError" + s;
	file1.open(filename1, ios::out);
	file2.open(filename2, ios::out);
	file3.open(filename3, ios::out);
	cout << "Weight: " << weight << endl;
	for (int j = startItems; j <= maxItems; j += stepItems)
	{
		double time = 0;
		cout << "Items number: " << j << endl;
		fptasKnapsack = Knapsack(weight);
		fptasKnapsack.GenerateItems(j);
		Knapsack best = DynamicProgrammingBasedOnValue(time, fptasKnapsack);
		int bestValue = best.GetTotalValue();
		float result = 0;

		FPTAS(eps, time, fptasKnapsack, result);
		file1 << bestValue << endl;
		file2 << result << endl;
		float error = abs((result - bestValue) / bestValue);
		file3 << error << endl;
	}
	testing = false;;
	file1.close();
	file2.close();
	file3.close();
}