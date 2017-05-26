#include "Node.h"

bool Node::operator ()(const Node & n1, const Node & n2)
{
	if (n1.bound < n2.bound) return true;
	if (n1.bound > n2.bound) return false;
	else return false;
}

string Node::ToString()
{
	string s = "";
	for (int i = 0; i < items.size(); i++)
	{
		s += "ID: " + to_string(items[i].GetID()) + " WEIGHT: " + to_string(items[i].GetWeight()) + " VALUE: "
			+ to_string(items[i].GetValue()) + "\n";
	}
	return s;
}
Node::Node()
{
	level = -1;
	weight = 0;
	value = 0;
}