#include "bots.h"
#include <iostream>
#include <vector>
void cbotSimple::ChooseNextGridPosition() {
	gDijkstra.coordslist[0].reverse();
	gDijkstra.coordslist[1].reverse();
	int len = gDijkstra.coordslist[0].size();
	std::vector<int> xcoords(gDijkstra.coordslist[0].begin(), gDijkstra.coordslist[0].end());
	std::vector<int> Ycoords(gDijkstra.coordslist[1].begin(), gDijkstra.coordslist[1].end());
	bool done = false;
	for (unsigned int i = 0; i < xcoords.size(); i++) {
		std::cout << xcoords[i] << " : " << Ycoords[i] << std::endl;
		SetNext(xcoords[i], Ycoords[i], gLevel);
	}
}