#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include "Knapsack.h"
#include "Program.h"
#include<iostream>
using namespace std;


void CinIntFail(int number)
{
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "You can only enter numbers.\n";
		cout << "Enter a number.\n";
		cin >> number;
	}
}

void main(void)
{
	string lineEnd = "\n";
	string menuString = "Create knapsack" + lineEnd + "1. Random knapsack " + lineEnd + "2. Knapsack from file" 
		+ lineEnd;
	string maxWeightIn = "Max knapsack's weight?" + lineEnd;
	string numberOfItemsIn = "Number of items?" + lineEnd;

	string maxWeightOut = "Knapsack's weight: ";
	string numberOfItemOut = "Number of items: ";

	string subMenuString = "Choose algorithm " + lineEnd + 
		"1. Bruteforce" + lineEnd + "2. Branch and Bound" + lineEnd
		+ "3. Back to menu" + lineEnd;

	string timeString = "Time: ";
	string milisecondsString = " ms";

	Program mainProgram;
	srand(time(NULL));
	int element, w, choice, licznik = 0;
	string filename;
	bool start = true;
	while (start)
	{
		cout << menuString;
		cin >> choice;
		CinIntFail(choice);
		switch (choice)
		{
		case 1:
		{
			while (true)
			{
				cout << maxWeightIn;
				cin >> w;
				CinIntFail(w);
				if (w > 0) break;
				else cout << "Must be more than 0!" << endl;
			}
			int p;
			while (true)
			{
				cout << numberOfItemsIn;
				cin >> p;
				CinIntFail(p);
				if (p > 1 ) break;
				else cout << "Must be more than 1!" << endl;
			}
			system("cls");
			Knapsack knapsack(w);
			knapsack.GenerateItems(p);
			start = false;
			cout << maxWeightOut << knapsack.GetMaxWeight() << endl
				<< numberOfItemOut << knapsack.GetItemsNumber() << endl;
			cout << knapsack.ToString();

			while (!start)
			{
				cout << subMenuString;
				cin >> choice;
				CinIntFail(choice);
				cout << endl;
				switch (choice)
				{

				case 1:
				{
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.bruteforce(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();

				}break;
				case 2:
				{
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.BranchAndBound(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 3:
				{
					system("cls");
					start = true;
				}break;
				}
			}
		}break;
		case 2:
		{
			int weight = 0;
			cout << "Filename of a file with knapsack?" << endl;
			cin >> filename;

			while (weight < 1)
			{
				cout << maxWeightIn << endl;
				cin >> weight;
				CinIntFail(weight);
			}

			ifstream file(filename);
			if (file)
			{
				file.close();
				Knapsack  knapsack = mainProgram.GetKnapsackFromFile(filename, weight);
				start = false;
				system("cls");
				cout << maxWeightOut << knapsack.GetMaxWeight() <<
					endl << numberOfItemOut << knapsack.GetItemsNumber() << endl;
				cout << knapsack.ToString();

				while (!start)
				{
					cout << subMenuString;
					cin >> choice;  
					CinIntFail(choice);
					cout << endl;
					switch (choice)
					{
					case 1:
					{
						double time;
						mainProgram.StartTimer();
						Knapsack bestKnapsack = mainProgram.bruteforce(knapsack);
						time = mainProgram.GetTimeAndStopTimer();
						cout << timeString << time << milisecondsString << endl;
						cout << bestKnapsack.ToString();

					}break;
					case 2:
					{
						double time;
						mainProgram.StartTimer();
						Knapsack bestKnapsack = mainProgram.BranchAndBound(knapsack);
						time = mainProgram.GetTimeAndStopTimer();
						cout << timeString << time << milisecondsString << endl;
						cout << bestKnapsack.ToString();
					}break;
					case 3:
					{
						system("cls");
						start = true;
					}break;
					}
				}


			}
			else
			{
				cout << filename << " - no such file!";
			}

		}break;

		}
	}
	system("pause");
	return;
}
