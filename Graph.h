#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <math.h>
#include "Ant.h"
#include "Edge.h"

class Graph {
	public:
		Graph();
		void engineSeed();
		void shortestRoute(int);
		void displayShortestRoute();
		void resetAnts();
		void initAnts();
		void initVectors();
		void initCustom(std::string);
		void initTest(std::string);
		void initialize(void (Graph::*)(std::string), std::string);
		void updatePheromones();
		void constructProbs();
		double edgeProb(std::shared_ptr<Ant>,int);
		std::shared_ptr<Edge> makeChoice(std::shared_ptr<Ant>);
		void constructPaths();
		void ACO(void (Graph::*)(std::string), std::string);

	private:
		bool finishFlag;
		int numOfCities;
		int numOfAnts;
		int source;
		int shortestDist;
		int iterations;
		double alpha;
		double beta;
		double Q;
		double ro;
		std::mt19937 eng;
		std::shared_ptr<Ant> bestAnt;
		std::vector<std::shared_ptr<Ant>> ants;
		std::vector<std::vector<bool>> R;
		std::vector<std::vector<double>> P;
		std::vector<std::vector<std::shared_ptr<Edge>>> G;
		friend class ACOMenu;
};

#endif
