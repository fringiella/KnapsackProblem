#ifndef ITEM_H
#define ITEM_H
class Item
{
private:
	int id;
	int weight;
	int value;
	double valueToWeight;

public:
	Item(int id, int weight, int value);
	Item();
	double GetValueToWeight();
	bool operator ()(const Item & i1, const Item & i2);
	int GetID() { return id; }
	int GetWeight() { return weight; }
	int GetValue() { return value; }
	void IncrementWeight() { weight++; }

};
#endif