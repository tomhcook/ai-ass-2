#include "bots.h"
#include <algorithm>
#include <iostream>
using namespace std;

void cDijkstra::build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			InPath[i][j] = false;
		}
	}
	coordslist[0].clear();
	coordslist[1].clear();
	bool pnf = true;
	while (pnf) {
		bool first = true;
		bool go = true;
		int smalllocal[1][2];
		float smallest = 10000000;
		cost[bot.PositionX()][bot.PositionY()] = 0;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (closed[i][j] == false) {
					if (gLevel.isBlocked(i, j) == false) {
						int x = cost[i][j];
						if (smallest > x) {
							smallest = x;
							smalllocal[0][0] = i;
							smalllocal[0][1] = j;
						}
					}
				}
			}
		}
		closed[smalllocal[0][0]][smalllocal[0][1]] = true;
		//cross
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] + 1) == true) 
			if (closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1;
				linkX[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1;
				linkX[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][1];
							}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][0];

				linkY[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		//diagonal
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		//check if player is closed;
		if (closed[gTarget.PositionX()][gTarget.PositionY()] == true) {
			pnf = false;
		}

	}
	bool done = false;
	if (gTarget.PositionX() >= 0 && gTarget.PositionX() <= 40 && gTarget.PositionY() >= 0 && gTarget.PositionY() <= 40) {

		int nextclosedx = gTarget.PositionX();
		int nextclosedy = gTarget.PositionY();
		int hello = 0;
		while (!done) {
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				InPath[nextclosedx][nextclosedy] = true;
				coordslist[0].push_back(nextclosedx);
				coordslist[1].push_back(nextclosedy);
			}
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
			}
			if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))done = true;



		}
	}
	completed = true;
}

void cAStartman::build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			InPath[i][j] = false;
		}
	}
	float heuristic = 0.0f;
	coordslist[0].clear();
	coordslist[1].clear();
	bool pnf = true;
	while (pnf) {
		bool first = true;
		bool go = true;
		int smalllocal[1][2];
		float smallest = 10000000;
		cost[bot.PositionX()][bot.PositionY()] = 0;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (closed[i][j] == false) {
					if (gLevel.isBlocked(i, j) == false) {
						int x = cost[i][j];
						if (smallest > x) {
							smallest = x;
							smalllocal[0][0] = i;
							smalllocal[0][1] = j;

						}
					}
				}
			}
		}
		closed[smalllocal[0][0]][smalllocal[0][1]] = true;
		//cross
		heuristic = fabs(gTarget.PositionX() - bot.PositionX()) + fabs(gTarget.PositionY() - bot.PositionY());
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] + 1) == true)
			if (closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
				if (cost[smalllocal[0][0]][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
					cost[smalllocal[0][0]][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
					linkX[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][0];
					linkY[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][1];
				}
			}
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][0];

				linkY[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		//diagonal
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		//check if player is closed;
		if (closed[gTarget.PositionX()][gTarget.PositionY()] == true) {
			pnf = false;
		}

	}
	bool done = false;
	if (gTarget.PositionX() >= 0 && gTarget.PositionX() <= 40 && gTarget.PositionY() >= 0 && gTarget.PositionY() <= 40) {

		int nextclosedx = gTarget.PositionX();
		int nextclosedy = gTarget.PositionY();
		int hello = 0;
		while (!done) {
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				InPath[nextclosedx][nextclosedy] = true;
				coordslist[0].push_back(nextclosedx);
				coordslist[1].push_back(nextclosedy);
			}
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
			}
			if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))done = true;



		}
	}
	completed = true;
}

void cAStartdiag::build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			InPath[i][j] = false;
		}
	}
	float heuristic = 0.0f;
	coordslist[0].clear();
	coordslist[1].clear();
	bool pnf = true;
	while (pnf) {
		bool first = true;
		bool go = true;
		int smalllocal[1][2];
		float smallest = 10000000;
		cost[bot.PositionX()][bot.PositionY()] = 0;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (closed[i][j] == false) {
					if (gLevel.isBlocked(i, j) == false) {
						int x = cost[i][j];
						if (smallest > x) {
							smallest = x;
							smalllocal[0][0] = i;
							smalllocal[0][1] = j;

						}
					}
				}
			}
		}
		closed[smalllocal[0][0]][smalllocal[0][1]] = true;
		//cross
		heuristic = fabs(gTarget.PositionX() - bot.PositionX()) + fabs(gTarget.PositionY() - bot.PositionY());
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] + 1) == true)
			if (closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
				if (cost[smalllocal[0][0]][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
					cost[smalllocal[0][0]][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
					linkX[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][0];
					linkY[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][1];
				}
			}
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX())/(gTarget.PositionY() - bot.PositionY()+1));
				linkX[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][0];

				linkY[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		//diagonal
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f/2 + heuristic * fabs(abs(gTarget.PositionX() - bot.PositionX()) / (gTarget.PositionY() - bot.PositionY() + 1));
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		//check if player is closed;
		if (closed[gTarget.PositionX()][gTarget.PositionY()] == true) {
			pnf = false;
		}

	}
	bool done = false;
	if (gTarget.PositionX() >= 0 && gTarget.PositionX() <= 40 && gTarget.PositionY() >= 0 && gTarget.PositionY() <= 40) {

		int nextclosedx = gTarget.PositionX();
		int nextclosedy = gTarget.PositionY();
		int hello = 0;
		while (!done) {
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				InPath[nextclosedx][nextclosedy] = true;
				coordslist[0].push_back(nextclosedx);
				coordslist[1].push_back(nextclosedy);
			}
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
			}
			if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))done = true;



		}
	}
	completed = true;
}

void cAStartecu::build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			InPath[i][j] = false;
		}
	}
	float heuristic = 0.0f;
	coordslist[0].clear();
	coordslist[1].clear();
	bool pnf = true;
	while (pnf) {
		bool first = true;
		bool go = true;
		int smalllocal[1][2];
		float smallest = 10000000;
		cost[bot.PositionX()][bot.PositionY()] = 0;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (closed[i][j] == false) {
					if (gLevel.isBlocked(i, j) == false) {
						int x = cost[i][j];
						if (smallest > x) {
							smallest = x;
							smalllocal[0][0] = i;
							smalllocal[0][1] = j;

						}
					}
				}
			}
		}
		closed[smalllocal[0][0]][smalllocal[0][1]] = true;
		//cross
		heuristic = sqrt(fabs(gTarget.PositionX() - bot.PositionX()) * fabs(gTarget.PositionX() - bot.PositionX()) + fabs(gTarget.PositionY() - bot.PositionY()) * fabs(gTarget.PositionY() - bot.PositionY()));;
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] + 1) == true)
			if (closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
				if (cost[smalllocal[0][0]][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
					cost[smalllocal[0][0]][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
					linkX[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][0];
					linkY[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][1];
				}
			}
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][0];

				linkY[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		//diagonal
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		//check if player is closed;
		if (closed[gTarget.PositionX()][gTarget.PositionY()] == true) {
			pnf = false;
		}

	}
	bool done = false;
	if (gTarget.PositionX() >= 0 && gTarget.PositionX() <= 40 && gTarget.PositionY() >= 0 && gTarget.PositionY() <= 40) {

		int nextclosedx = gTarget.PositionX();
		int nextclosedy = gTarget.PositionY();
		int hello = 0;
		while (!done) {
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				InPath[nextclosedx][nextclosedy] = true;
				coordslist[0].push_back(nextclosedx);
				coordslist[1].push_back(nextclosedy);
			}
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
			}
			if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))done = true;



		}
	}
	completed = true;
}

void cAStartecu2::build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			InPath[i][j] = false;
		}
	}
	float heuristic = 0.0f;
	coordslist[0].clear();
	coordslist[1].clear();
	bool pnf = true;
	while (pnf) {
		bool first = true;
		bool go = true;
		int smalllocal[1][2];
		float smallest = 10000000;
		cost[bot.PositionX()][bot.PositionY()] = 0;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (closed[i][j] == false) {
					if (gLevel.isBlocked(i, j) == false) {
						int x = cost[i][j];
						if (smallest > x) {
							smallest = x;
							smalllocal[0][0] = i;
							smalllocal[0][1] = j;

						}
					}
				}
			}
		}
		closed[smalllocal[0][0]][smalllocal[0][1]] = true;
		//cross
		heuristic = (fabs(gTarget.PositionX() - bot.PositionX()) * fabs(gTarget.PositionX() - bot.PositionX()) + fabs(gTarget.PositionY() - bot.PositionY()) * fabs(gTarget.PositionY() - bot.PositionY()));;
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] + 1) == true)
			if (closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
				if (cost[smalllocal[0][0]][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
					cost[smalllocal[0][0]][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
					linkX[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][0];
					linkY[smalllocal[0][0]][smalllocal[0][1] + 1] = smalllocal[0][1];
				}
			}
		if (gLevel.isValid(smalllocal[0][0], smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0]][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0]][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0]][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1]) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1]] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1]] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1 + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][0];

				linkY[smalllocal[0][0] - 1][smalllocal[0][1]] = smalllocal[0][1];
			}
		}
		//diagonal
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] + 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] + 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] + 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic;
				linkX[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] + 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		if (gLevel.isValid(smalllocal[0][0] - 1, smalllocal[0][1] - 1) == true && closed[smalllocal[0][0]][smalllocal[0][1] + 1] == false) {
			if (cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] >= cost[smalllocal[0][0]][smalllocal[0][1]]) {
				cost[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = cost[smalllocal[0][0]][smalllocal[0][1]] + 1.4f + heuristic; 
				linkX[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][0];
				linkY[smalllocal[0][0] - 1][smalllocal[0][1] - 1] = smalllocal[0][1];
			}
		}
		//check if player is closed;
		if (closed[gTarget.PositionX()][gTarget.PositionY()] == true) {
			pnf = false;
		}

	}
	bool done = false;
	if (gTarget.PositionX() >= 0 && gTarget.PositionX() <= 40 && gTarget.PositionY() >= 0 && gTarget.PositionY() <= 40) {

		int nextclosedx = gTarget.PositionX();
		int nextclosedy = gTarget.PositionY();
		int hello = 0;
		while (!done) {
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				InPath[nextclosedx][nextclosedy] = true;
				coordslist[0].push_back(nextclosedx);
				coordslist[1].push_back(nextclosedy);
			}
			if (nextclosedx >= 0 && nextclosedx <= 40 && nextclosedy >= 0 && nextclosedy <= 40) {
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
			}
			if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))done = true;



		}
	}
	completed = true;
}
cDijkstra gDijkstra;
cAStartman gAStartman;
cAStartdiag gAStartdiag;
cAStartecu gAStartecu;
cAStartecu2 gAStartecu2;