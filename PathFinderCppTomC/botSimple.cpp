#include "bots.h"
#include <iostream>
#include <vector>
void cbotSimple::ChooseNextGridPosition() {
	bool done = false;
	//Use while loop, as randomly selected location might not be valid
	while (!done)
	{
		if (PositionX() > gTarget.PositionX())  done = SetNext((PositionX() -1), (PositionY()), gLevel);;
		if (PositionX() < gTarget.PositionX())  done = SetNext((PositionX() + 1), (PositionY()), gLevel);;
		if (PositionY() > gTarget.PositionY())  done = SetNext((PositionX()), (PositionY() + 1), gLevel);;
		if (PositionY() < gTarget.PositionY())  done = SetNext((PositionX() ), (PositionY() + -1), gLevel);;
	}
}
void cDijkstrabot::ChooseNextGridPosition() {
	cAStartecu gAStartecu;
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
void cAstarbotdiag::ChooseNextGridPosition() {
	gAStartdiag.coordslist[0].reverse();
	gAStartdiag.coordslist[1].reverse();
	int len = gAStartdiag.coordslist[0].size();
	std::vector<int> xcoords(gAStartdiag.coordslist[0].begin(), gAStartdiag.coordslist[0].end());
	std::vector<int> Ycoords(gAStartdiag.coordslist[1].begin(), gAStartdiag.coordslist[1].end());
	bool done = false;
	for (unsigned int i = 0; i < xcoords.size(); i++) {
		std::cout << xcoords[i] << " : " << Ycoords[i] << std::endl;
		SetNext(xcoords[i], Ycoords[i], gLevel);
	}
}
void cAstarbotman::ChooseNextGridPosition() {
	gAStartman.coordslist[0].reverse();
	gAStartman.coordslist[1].reverse();
	int len = gAStartman.coordslist[0].size();
	std::vector<int> xcoords(gAStartman.coordslist[0].begin(), gAStartman.coordslist[0].end());
	std::vector<int> Ycoords(gAStartman.coordslist[1].begin(), gAStartman.coordslist[1].end());
	bool done = false;
	for (unsigned int i = 0; i < xcoords.size(); i++) {
		std::cout << xcoords[i] << " : " << Ycoords[i] << std::endl;
		SetNext(xcoords[i], Ycoords[i], gLevel);
	}
}
void cAstarbotecu::ChooseNextGridPosition() {
	gAStartecu.coordslist[0].reverse();
	gAStartecu.coordslist[1].reverse();
	int len = gAStartecu.coordslist[0].size();
	std::vector<int> xcoords(gAStartecu.coordslist[0].begin(), gAStartecu.coordslist[0].end());
	std::vector<int> Ycoords(gAStartecu.coordslist[1].begin(), gAStartecu.coordslist[1].end());
	bool done = false;
	for (unsigned int i = 0; i < xcoords.size(); i++) {
		std::cout << xcoords[i] << " : " << Ycoords[i] << std::endl;
		SetNext(xcoords[i], Ycoords[i], gLevel);
	}
}
void cAstarbotecu2::ChooseNextGridPosition() {
	gAStartecu2.coordslist[0].reverse();
	gAStartecu2.coordslist[1].reverse();
	int len = gAStartecu2.coordslist[0].size();
	std::vector<int> xcoords(gAStartecu2.coordslist[0].begin(), gAStartecu2.coordslist[0].end());
	std::vector<int> Ycoords(gAStartecu2.coordslist[1].begin(), gAStartecu2.coordslist[1].end());
	bool done = false;
	for (unsigned int i = 0; i < xcoords.size(); i++) {
		std::cout << xcoords[i] << " : " << Ycoords[i] << std::endl;
		SetNext(xcoords[i], Ycoords[i], gLevel);
	}
}