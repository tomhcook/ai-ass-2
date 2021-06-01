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
	int nextclosedx = gTarget.PositionX();
	int nextclosedy = gTarget.PositionY();
	int hello = 0;
	while (!done) {
			InPath[nextclosedx][nextclosedy] = true;
			coordslist[0].push_back(nextclosedx);
			coordslist[1].push_back(nextclosedy);
				int tx = nextclosedx;
				int ty = nextclosedy;
				nextclosedx = linkX[tx][ty];
				nextclosedy = linkY[tx][ty];
				if ((nextclosedx == bot.PositionX()) && (nextclosedy == bot.PositionY()))
					done = true;
	}
	completed = true;
}

cDijkstra gDijkstra;
