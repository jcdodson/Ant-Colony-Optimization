#include "ACOMenu.h"
#include <iostream>

using namespace std;

ACOMenu::ACOMenu() {
	G = make_shared<Graph>();
}

void ACOMenu::clrScr() {
	cout << "\033[2J\033[1;1H";
}

void ACOMenu::graphReset() {
	G = make_shared<Graph>();
}

void ACOMenu::parameterInfo() {
	cout << "***PARAMETER INFORMATION***" << endl;
	cout << "Number of Ants:		The number of ants to be released in the simulation" << endl;
	cout << "Number of Iteration:	The number of iterations before the simulation stops" << endl;
	cout << "ALPHA:					The weight of pheromone" << endl;
	cout << "BETA:					The weight of edge quality" << endl;
	cout << "Q:						The quality of short paths" << endl;
	cout << "RO:					The rate of pheromone evaporation" << endl;
	cout << endl << endl;
}

void ACOMenu::menu() {
	
	int option;
	int custOption;
	string test;
	void (Graph:: * funcPtr)(std::string) = &Graph::initTest;

	while (true) {
		cout << "***ACO MENU***" << endl;
		cout << "1.   4 Cities with predetermined distances" << endl;
		cout << "2.   5 Cities with predetermined distances" << endl;
		cout << "3.   6 Cities with predetermined distances" << endl;
		cout << "4.   17 Cities with pretermined distances" << endl;
		cout << "5.   26 Cities with pretermined distances" << endl;
		cout << "6.   48 State Capitals in the US" << endl;
		cout << "7.   Custom TSP" << endl;
		cout << "8.   Customize Settings" << endl;
		cout << "0.   Exit" << endl;
		cout << "Option: ";
		cin >> option;
		cout << endl;

		if (option == 0) {
			break;
		}
		switch (option) {

		case 1:
			test = "4_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 2:
			test = "5_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 3:
			test = "6_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 4:
			test = "17_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 5:
			test = "26_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 6:
			test = "48_city.txt";
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 7:
			test = "";
			funcPtr = &Graph::initCustom;
			cout << "Enter number of cities: ";
			cin >> custOption;
			G->numOfCities = custOption;
			G->ACO(funcPtr, test);
			cout << endl;
			break;
		case 8:
			clrScr();
			customMenu();
			cout << endl;
			break;
		default:
			cout << endl << "Invalid Option" << endl;
			break;
		}
		graphReset();
	}
}

void ACOMenu::customMenu() {

	int intInput;
	double dInput;
	int option;

	while (true) {
		cout << "***CUSTOM ACO MENU***" << endl;
		cout << "1.   Number of Ants" << endl;
		cout << "2.   Number of Iterations" << endl;
		cout << "3.   ALPHA" << endl;
		cout << "4.   BETA" << endl;
		cout << "5.   Q" << endl;
		cout << "6.   RO" << endl;
		cout << "7.   Parameter Information" << endl;
		cout << "8.   Reset to defaults" << endl;
		cout << "0.   Back" << endl;
		cout << "Option: ";
		cin >> option;

		if (option == 0) {
			clrScr();
			break;
		}
		switch (option) {

		case 1:
			clrScr();
			cout << "Enter the number of Ants you want released (Default: 5) (Current: " << G->numOfAnts << "): ";
			cin >> intInput;
			G->numOfAnts = intInput;
			cout << endl;
			break;
		case 2:
			clrScr();
			cout << "Enter the number of iterations you want (Default: 100) (Current: " << G->iterations << "): ";
			cin >> intInput;
			G->iterations = intInput;
			cout << endl;
			break;
		case 3:
			clrScr();
			cout << "Enter the value of ALPHA you want (Default: 1.0) (Current: " << G->alpha << "): ";
			cin >> dInput;
			G->alpha = dInput;
			cout << endl;
			break;
		case 4:
			clrScr();
			cout << "Enter the value of BETA you want (Default: 5.0) (Current: " << G->beta << "): ";
			cin >> dInput;
			G->beta = dInput;
			cout << endl;
			break;
		case 5:
			clrScr();
			cout << "Enter the value of Q you want (Default: 1.0) (Current: " << G->Q << "): ";
			cin >> dInput;
			G->Q = dInput;
			cout << endl;
			break;
		case 6:
			clrScr();
			cout << "Enter the value of RO you want (Default: 0.5) (Current: " << G->ro << "): ";
			cin >> dInput;
			G->ro = dInput;
			cout << endl;
			break;
		case 7:
			clrScr();
			parameterInfo();
			cout << endl;
			break;
		case 8:
			graphReset();
			break;
		}
	}
}
