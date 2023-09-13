#include "Graph.h"
#include <climits>

Graph::Graph() {
	source = 1;
	numOfAnts = 5;
	iterations = 100;
	finishFlag = 0;
	alpha = 1.0;
	beta = 5.0;
	Q = 1.0;
	ro = .5;
}

void Graph::engineSeed() {

	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r() };
	eng = std::mt19937(seed);
}

void Graph::shortestRoute(int iter) {
	for (int i = 1; i < numOfAnts + 1; i++) {
		if (ants[i]->distTraveled < bestAnt->distTraveled) {
			if (ants[i]->distTraveled == shortestDist) {
				bestAnt->distTraveled = ants[i]->distTraveled;
				bestAnt->id = ants[i]->id;
				bestAnt->path = ants[i]->path;
				std::cout << "Shortest possible route found of " << shortestDist << " by ant " << ants[i]->id << " on iteration " << iter << std::endl;
				finishFlag = true;
				break;
			}
			bestAnt->distTraveled = ants[i]->distTraveled;
			bestAnt->id = ants[i]->id;
			bestAnt->path = ants[i]->path;
			std::cout << "New shortest route found of " << ants[i]->distTraveled << " by ant " << ants[i]->id << " on iteration " << iter << std::endl;
		}
	}
}

void Graph::displayShortestRoute() {
	std::cout << std::endl << "Simulation finished..." << std::endl << std::endl;
	std::cout << "Best solution found: ";
	bestAnt->antOut();
	std::cout << std::endl << std::endl; 
}

void Graph::resetAnts() {

	for (int i = 1; i < numOfCities + 1; i++) {
		for (int j = 1; j < numOfAnts + 1; j++) {
			R[i][j] = 1;
		}
	}
	for (int i = 1; i < numOfAnts + 1; i++) {
		ants[i]->path = {};
		ants[i]->path.push_back(G[source][source]);
		ants[i]->currentPos = source;
		ants[i]->distTraveled = 0;
		R[source][i] = 0;
	}
}

void Graph::initAnts() {

	bestAnt = std::make_shared<Ant>();
	bestAnt->distTraveled = INT_MAX;

	ants.push_back(std::make_shared<Ant>());

	for (int i = 1; i < numOfAnts + 1; i++) {
		std::shared_ptr<Ant> a = std::make_shared<Ant>();
		a->id = i;
		a->path.push_back(G[source][source]);
		a->currentPos = source;
		R[source][i] = 0;
		ants.push_back(a);
	}
}

void Graph::initVectors() {

	R = std::vector<std::vector<bool>>(numOfCities + 1, std::vector<bool>(numOfAnts + 1,1));
	P = std::vector<std::vector<double>>(numOfCities + 1, std::vector<double>(numOfAnts + 1,0.0));
	G = std::vector<std::vector<std::shared_ptr<Edge>>>(numOfCities + 1);

	G[0].push_back(std::make_shared<Edge>());

	for (int i = 1; i < numOfCities + 1; i++) {
		std::shared_ptr<Edge> e = std::make_shared<Edge>();
		e->from = i;
		e->to = i;
		e->distance = 0;
		G[0].push_back(e);
	}
	for (int i = 1; i < numOfCities + 1; i++) {
		for (int j = 0; j < numOfCities + 1; j++) {
			std::shared_ptr<Edge> e = std::make_shared<Edge>();
			e->from = G[0][i]->from;
			e->to = G[0][j]->to;
			e->pheromone = 1;
			G[i].push_back(e);
		}
	}
}

void Graph::initCustom(std::string test) {

	std::uniform_int_distribution<> dist{ 1,100 };

	shortestDist = INT_MAX;

	initVectors();

	int input = 0;

	for (int i = 1; i < numOfCities + 1; i++) {
		for (int j = i + 1; j < numOfCities + 1; j++) {
			input = dist(eng);
			G[j][i]->distance = input;
			G[i][j]->distance = input;
		}
	}
}

void Graph::initTest(std::string test) {

	std::ifstream inputFile;
	inputFile.open(test);
	int input;

	if (!inputFile) {
		std::cout << "ERROR COULD NOT FIND INPUT FILE" << std::endl;
	}

	inputFile >> input;
	numOfCities = input;
	inputFile >> input;
	shortestDist = input;

	initVectors();

	for (int i = 1; i < numOfCities + 1 && !inputFile.eof(); i++) {
		for (int j = 1; j < numOfCities + 1 && !inputFile.eof(); j++) {
			inputFile >> input;
			G[i][j]->distance = input;
			G[j][i]->distance = input;

		}
	}
	inputFile.close();
}

void Graph::initialize(void(Graph::* funcPtr)(std::string), std::string test) {

	std::cout << "Initializing new simulation..." << std::endl << std::endl;

	engineSeed();
	(this->*funcPtr)(test);
	initAnts();
}

void Graph::updatePheromones() {

	double evap = 0.0;
	double deposit = 0.0;

	for (int i = 1; i < G.size(); i++) {
		for (int j = 1 + i; j < G[i].size(); j++) {
			evap = G[i][j]->pheromone * (1 - ro);
			G[i][j]->pheromone = evap;
			G[j][i]->pheromone = evap;
		}
	}
	for (int i = 1; i < numOfAnts + 1; i++) {
		deposit = Q / ants[i]->distTraveled;
		for (int j = 0; j < ants[i]->path.size(); j++) {
			ants[i]->path[j]->pheromone += deposit;
		}
	}
}

double Graph::edgeProb(std::shared_ptr<Ant> a, int city) {

	double probNum = 0.0;
	double probDenom = 0.0;
	double tauSum = 0.0;
	double etaSum = 0.0;

	probNum = (pow(G[a->currentPos][city]->pheromone, alpha) * pow(Q / G[a->currentPos][city]->distance, beta));

	for (int i = 1; i < numOfCities + 1; i++) {
		if (R[i][a->id] == 1) {
			tauSum = pow(G[a->currentPos][i]->pheromone, alpha);
			etaSum = pow(Q / G[a->currentPos][i]->distance, beta);
			probDenom += (tauSum * etaSum);
		}
	}
	return (probNum / probDenom);
}

void Graph::constructProbs() {
	for (int i = 1; i < numOfAnts + 1; i++) {
		for (int j = 1; j < numOfCities + 1; j++) {
			if (R[j][ants[i]->id] == 1) {
				P[j][i] = edgeProb(ants[i], j);
			}
			else {
				P[j][i] = 0.0;
			}
		}
	}
}

std::shared_ptr<Edge> Graph::makeChoice(std::shared_ptr<Ant> a) {

	std::uniform_real_distribution<> dist{ 0.0, 1.0 };
	double choice = 0.0;

	choice = dist(eng);
	for (int i = 1; i < numOfCities + 1; i++) {
		if (R[i][a->id] != 0) {
			choice -= P[i][a->id];
		}
		if (choice < 0) {
			R[i][a->id] = 0;
			return G[a->currentPos][i];
		}
		else {
			continue;
		}
	}
}

void Graph::constructPaths() {

	std::shared_ptr<Edge> eChosen = std::make_shared<Edge>();
	for (int i = 1; i < numOfCities; i++) {
		for (int j = 1; j < numOfAnts + 1; j++) {
			eChosen = makeChoice(ants[j]);
			ants[j]->path.push_back(eChosen);
			ants[j]->distTraveled += G[ants[j]->currentPos][eChosen->to]->distance;
			ants[j]->currentPos = eChosen->to;
		}
		constructProbs();
	}
	for (int i = 1; i < numOfAnts + 1; i++) {
		ants[i]->distTraveled += G[ants[i]->currentPos][source]->distance;
		ants[i]->currentPos = source;
		ants[i]->path.push_back(G[ants[i]->currentPos][source]);
	}
}

void Graph::ACO(void(Graph::* funcPtr)(std::string), std::string test) {

	initialize(funcPtr, test);

	std::cout << "Running simulation..." << std::endl << std::endl;

	int endCounter = 1;
	while (endCounter <= iterations && !finishFlag) {
		constructProbs();
		constructPaths();
		updatePheromones();
		shortestRoute(endCounter);
		resetAnts();
		endCounter++;
	}
	displayShortestRoute();
}
