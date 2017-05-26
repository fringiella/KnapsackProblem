#include "Item.h"
using namespace std;
Item :: Item()
{
	id = 0;
	weight = 0;
	value = 0;
}

Item::Item(int id, int weight, int value)
	: id(id), weight(weight), value(value) 
{
	valueToWeight = (double)value / (double)weight;
}

double Item :: GetValueToWeight()
{
	return valueToWeight;
}
bool Item::operator ()(const Item & i1, const Item & i2)
{
	if (i1.valueToWeight < i2.valueToWeight)
		return true;
	if (i1.valueToWeight > i2.valueToWeight) 
		return false;
	else 
		return false;
}

