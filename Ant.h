#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Edge.h"
struct Ant {
public:
	void antOut() {
		for (int i = 0; i < path.size(); i++) {
			std::cout << path[i]->to << " ";
		}
	}
	private:
		int id;
		int distTraveled;
		int currentPos{};
		std::vector<std::shared_ptr<Edge>> path;
		friend class Graph;
};

