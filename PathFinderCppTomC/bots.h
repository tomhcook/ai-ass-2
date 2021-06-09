#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================
#include <list>
#include <iterator>
#include "botbase.h"
struct coords {
	int x;
	int y;
};
class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};
class cbotSimple : public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cDijkstrabot : public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cAstarbotman: public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cAstarbotdiag: public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cAstarbotecu: public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cAstarbotecu2: public cBotBase {
	virtual void ChooseNextGridPosition();
};
class cDijkstra {
public:
	bool closed[GRIDWIDTH][GRIDHEIGHT]; 
	//whether or not location is closed
	float cost[GRIDWIDTH][GRIDHEIGHT]; 
	//cost value for each location
	int linkX[GRIDWIDTH][GRIDHEIGHT]; 
	//link X coord for each location
	int linkY[GRIDWIDTH][GRIDHEIGHT]; 
	//link Y coord for each location
	bool InPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in 
	bool completed;
	cDijkstra(){ completed = false; };
	virtual void build(cBotBase& bot);
	std::list<int> coordslist [2];

};
extern cDijkstra gDijkstra;
class cAStartman : public cDijkstra {
public: virtual void build(cBotBase& bot);
};

class cAStartdiag : public cDijkstra {
public: virtual void build(cBotBase& bot);
};
class cAStartecu : public cDijkstra {
public: virtual void build(cBotBase& bot);
};
class cAStartecu2 : public cDijkstra {
public: virtual void build(cBotBase& bot);
};
extern cAStartman gAStartman;
extern cAStartdiag gAStartdiag;
extern cAStartecu gAStartecu;
extern cAStartecu2 gAStartecu2;





