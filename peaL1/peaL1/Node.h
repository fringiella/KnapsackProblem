#include "Item.h"
#include <vector>
#include <string>
using namespace std;
#ifndef NODE_H
#define NODE_H
class Node
{
private:
	int level;
	int value;
	int weight;
	double bound;
	vector<Item> items;
public:
	bool operator ()(const Node & n1, const Node & n2);
	string ToString();
	Node();
	int GetLevel() { return level; }
	int GetValue() { return value; }
	int GetWeight() { return weight; }
	double GetBound() { return bound; }
	vector <Item> GetItems() { return items; }
	void SetBound(int b) { bound = b; }
	void SetLevel(int l) { level = l; }
	void SetValue(int v) { value = v; }
	void SetWeight(int w) { weight = w; }
	void SetItems(vector <Item> i) { items = i; }
	void AddItem(Item item) { items.push_back(item); }
};
#endif


