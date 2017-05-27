#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
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
