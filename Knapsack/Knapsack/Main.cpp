#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include "Knapsack.h"
#include "Program.h"
#include<iostream>
using namespace std;

void main(void)
{
	string lineEnd = "\n";
	string menuString = "Create knapsack" + lineEnd + "1. Random knapsack " + lineEnd + "2. Knapsack from file" + lineEnd + "3. Tests" + lineEnd
		+ "4. Quality test FPTAS" + lineEnd;

	string maxWeightIn = "Max knapsack's weight?" + lineEnd;
	string numberOfItemsIn = "Number of items?" + lineEnd;

	string maxWeightOut = "Knapsack's weight: ";
	string numberOfItemOut = "Number of items: ";

	string subMenuString = "Choose algorithm " + lineEnd +
		"1. Bruteforce" + lineEnd + "2. Branch and Bound" + lineEnd +
		+"3. Dynamic programming" + lineEnd
		+ "4. Dynamic programming based on value" + lineEnd
		+ "5. FPTAS" + lineEnd
		+ "6. Back to menu" + lineEnd;

	string timeString = "Time: ";
	string milisecondsString = " ms";

	Program mainProgram;
	srand(time(NULL));
	int element = 0, w = 0, choice = 0, licznik = 0;
	string filename;
	bool start = true;
	while (start)
	{
		cout << menuString;
		mainProgram.CinInt(choice);
		switch (choice)
		{
		case 1:
		{
			while (true)
			{
				cout << maxWeightIn;
				mainProgram.CinInt(w);
				if (w > 0) break;
				else cout << "Must be more than 0!" << endl;
			}
			int p;
			while (true)
			{
				cout << numberOfItemsIn;
				mainProgram.CinInt(p);
				if (p > 1) break;
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
				mainProgram.CinInt(choice);
				cout << endl;
				switch (choice)
				{

				case 1:
				{
					cout << "1. Bruteforce" << endl;
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.Bruteforce(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();

				}break;
				case 2:
				{
					cout << "2. Branch and Bound" << endl;
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.BranchAndBound(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 3:
				{
					cout << "3. Dynamic programming" << endl;
					double time;
					Knapsack bestKnapsack = mainProgram.DynamicProgramming(time, knapsack);
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 4:
				{
					cout << "4. Dynamic programming based on value" << endl;
					double time;
					Knapsack bestKnapsack = mainProgram.DynamicProgrammingBasedOnValue(time, knapsack);
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 5:
				{
					cout << "4. FPTAS" << endl;
					float e;
					while (true)
					{
						cout << "Epsilion?" << endl;
						cin >> e;
						if (e < 1 && e > 0) break;
						else cout << "Must be less than 1 and more than 0!" << endl;
					}
					double time;
					float result = 0;
					Knapsack bestKnapsack = mainProgram.FPTAS(e, time, knapsack, result);
					cout << timeString << time << milisecondsString << endl;
					cout << "Minimal knapsack value possible to get from FPTAS: " << result << endl;
					cout << bestKnapsack.ToString();

				}break;
				case 6:
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
			ifstream file(filename);

			if (!file)
			{
				cout << filename << " - no such file!" << endl;
				break;
			}
			while (weight < 1)
			{
				cout << maxWeightIn << endl;
				mainProgram.CinInt(weight);
			}

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
				mainProgram.CinInt(choice);
				cout << endl;
				switch (choice)
				{
				case 1:
				{
					cout << "1. Bruteforce" << endl;
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.Bruteforce(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();

				}break;
				case 2:
				{
					cout << "2. Branch and bound" << endl;
					double time;
					mainProgram.StartTimer();
					Knapsack bestKnapsack = mainProgram.BranchAndBound(knapsack);
					time = mainProgram.GetTimeAndStopTimer();
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 3:
				{
					cout << "3. Dynamic programming" << endl;
					double time;
					Knapsack bestKnapsack = mainProgram.DynamicProgramming(time, knapsack);
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 4:
				{
					cout << "4. Dynamic programming based on value" << endl;
					double time;
					Knapsack bestKnapsack = mainProgram.DynamicProgrammingBasedOnValue(time, knapsack);
					cout << timeString << time << milisecondsString << endl;
					cout << bestKnapsack.ToString();
				}break;
				case 5:
				{
					cout << "5. FPTAS" << endl;
					float e;
					while (true)
					{
						cout << "Epsilion?" << endl;
						cin >> e;
						if (e < 1 && e > 0) break;
						else cout << "Must be less than 1 and more than 0!" << endl;
					}
					double time;
					float result = 0;
					Knapsack bestKnapsack = mainProgram.FPTAS(e, time, knapsack, result);
					cout << timeString << time << milisecondsString << endl;
					cout << "Minimal knapsack value possible to get from FPTAS: " << result << endl;
					cout << bestKnapsack.ToString();

				}break;
				case 6:
				{
					system("cls");
					start = true;
				}break;
				}

			}

		}break;
		case 3:
		{
			cout << "Which algorithm do you want to test? " << endl;
			cout << "1. Bruteforce" << endl
				<< "2. B&B" << endl
				<< "3. Dynamic programming" << endl
				<< "4. Dynamic programming based on value" << endl
				<< "5. FPTAS" << endl;
			mainProgram.CinInt(choice);
			cout << endl;
			int startWeight, stepWeight, maxWeight, startItems, stepItems, maxItems;
			int algorithm = choice;
			if (algorithm > 5) break;
			cout << "Start weight?" << endl;
			mainProgram.CinInt(startWeight);
			cout << endl;

			cout << "Weight step?" << endl;
			mainProgram.CinInt(stepWeight);
			cout << endl;

			cout << "Max weight?" << endl;
			mainProgram.CinInt(maxWeight);
			cout << endl;

			cout << "Start items number?" << endl;
			mainProgram.CinInt(startItems);
			cout << endl;

			cout << "Items number step?" << endl;
			mainProgram.CinInt(stepItems);
			cout << endl;

			cout << "Max items number?" << endl;
			mainProgram.CinInt(maxItems);
			cout << endl;

			mainProgram.Tests(startWeight, stepWeight, maxWeight, startItems, stepItems, maxItems, algorithm);
		}break;
		case 4:
		{
			int weight, startItems, stepItems, maxItems;
			float epsilon;
			cout << "Weight?" << endl;
			mainProgram.CinInt(weight);
			cout << endl;

			cout << "Start items number?" << endl;
			mainProgram.CinInt(startItems);
			cout << endl;

			cout << "Items number step?" << endl;
			mainProgram.CinInt(stepItems);
			cout << endl;

			cout << "Max items number" << endl;
			mainProgram.CinInt(maxItems);
			cout << endl;

			while (true)
			{
				cout << "Epsilon?" << endl;
				cin >> epsilon;
				if (epsilon < 1 && epsilon > 0) break;
				else cout << "Must be less than 1 and more than 0!" << endl;
			}
			mainProgram.TestQuality(weight, startItems, stepItems, maxItems, epsilon);
		}break;		
		}
	}
	system("pause");
	return;
}
