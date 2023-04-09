#pragma once
struct Edge {
	private:
		int from;
		int to;
		int distance;
		double pheromone;
		friend class Ant;
		friend class Graph;
};

