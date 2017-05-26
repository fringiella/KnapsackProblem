#include <vector>
#include <string>
#include "Item.h"
using namespace std;
#ifndef KNAPSACK_H
#define KNAPSACK_H
class Knapsack
{
private:
	vector<Item> items;
	int totalWeight;
	int totalValue;
	int maxWeight;
	Item RandomItem(int id);

public:
	Knapsack(int max);
	Knapsack::Knapsack(int totValue, int totWeight, vector <Item> i);
	Knapsack();
	void AddItem(Item i);
	double NumberOfSubsets();
	vector<Item> GetItems() { return items; }
	Item GetItemAt(int i) { return items[i]; }
	int GetItemsNumber() { return items.size(); }
	int GetTotalWeight() { return totalWeight; }
	int GetTotalValue() { return totalValue; }
	int GetMaxWeight() { return maxWeight; }
	string ToString();
	void GenerateItems(int n);
	void SortItemsByValueToWeight();
	void ClearItems() { items.clear(); };
};
#endif