#include "Knapsack.h"
#include <queue>
#include <math.h>
using namespace std;

Knapsack::Knapsack(int max)
{
	totalValue = 0;
	totalWeight = 0;
	maxWeight = max;
}
Knapsack::Knapsack(int totValue, int totWeight, vector <Item> i)
	: totalValue(totValue), totalWeight(totWeight), items(i) { }

Knapsack::Knapsack()
{
	totalValue = 0;
	totalWeight = 0;
	maxWeight = 0;
}
double Knapsack::NumberOfSubsets()
{
	return pow(2, GetItemsNumber());
}

void Knapsack::AddItem(Item i)
{
	items.push_back(i);
	totalWeight += i.GetWeight();
	totalValue += i.GetValue();
}

Item Knapsack::RandomItem(int id)
{
	int maxW = 20;
	int maxV = 15;

	int w = (rand() % maxW) + 1;
	int v = (rand() % maxV) + 1;
	Item i(id, w, v);
	return i;
}

void Knapsack::GenerateItems(int n)
{
	for (int i = 0; i < n; i++)
	{
		Item item = RandomItem(i);
		AddItem(item);
	}
	//  forcing the weight sum of items to be bigger than the knapsack max weight
	if (totalWeight < ceil((double)maxWeight * 1.25))
	{
		// the difference between items' weigth and 125% of a max knapsack's weight
		int dif = (int)ceil((double)maxWeight * 1.25) - totalWeight;
		while (dif > 0)
		{
			// adding a difference equally to all items
			for (int i = 0; i < n; i++)
			{
				if (dif == 0) break;
				items[i].IncrementWeight();
				totalWeight++;
				dif--;
			}
		}
	}
	SortItemsByValueToWeight();
}

void Knapsack::SortItemsByValueToWeight()
{
	priority_queue <Item, vector<Item>, Item> queue;
	for (int i = 0; i < items.size(); i++)
	{
		queue.push(items[i]);
	}
	items.clear();
	while (!queue.empty())
	{
		Item item = queue.top();
		queue.pop();
		items.push_back(item);
	}

}
string Knapsack::ToString()
{
	string s = "";
	for (int i = 0; i < GetItemsNumber(); i++)
	{
		s += "ID: " + to_string(items[i].GetID()) + " WEIGHT: " + to_string(items[i].GetWeight()) + " VALUE: "
			+ to_string(items[i].GetValue()) + "\n";
	}
	s+= "VALUE of all items in the knapsack: " + to_string(totalValue) + "\n"
		+ "WEIGHT of all items in the knapsack: " + to_string(totalWeight) + "\n"; 
	return s;
}