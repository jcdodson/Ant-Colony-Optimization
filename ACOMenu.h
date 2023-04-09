#pragma once
#include "Graph.h"

class ACOMenu {
	public:
		ACOMenu();
		void clrScr();
		void graphReset();
		void parameterInfo();
		void menu();
		void customMenu();
	private:
		std::shared_ptr<Graph> G;
};

