#include "Ugp.h"
#include <vector>
#include <iostream>

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 800


ugp::ugp(int numberOfGrid, Circle* circle, int size)
	: NUMG(numberOfGrid), c(circle), n(size)
{
	lineVertices = NULL;
	G = new Grid * [NUMG];
	for (int i = 0; i < NUMG; ++i) {
		G[i] = new Grid[NUMG];
	}
}

void ugp::InsertToGrid()
{
	// width and height of each grid
	float W = SCREEN_WIDTH / NUMG;
	float H = SCREEN_HEIGHT / NUMG;
	float x, y, r;
	for (int i = 0; i < n; i++) { // Iterate each circle
		x = c[i].GetCenterRad()[0]; // x coordinate of the center of circle
		y = c[i].GetCenterRad()[1]; // y coordinate of the center of circle
		r = c[i].GetCenterRad()[2]; // radius of the circle
		for (int j = 0; j < NUMG; j++) // Iterate each grid
			for (int k = 0; k < NUMG; k++)
				if (x + r >= W * j && x - r <= W * (j + 1) && y + r >= H * k && y - r <= H * (k + 1))
					G[j][k].index.push_back(i);
	}
}


void ugp::IterCircleInGrid() {
	for (int i = 0; i < NUMG; ++i) // itter grid
		for (int j = 0; j < NUMG; ++j)
			if (G[i][j].index.size() > 1)
				for (int k = 0; k < G[i][j].index.size() - 1; k++) // itter circle
					for (int l = k + 1; l < G[i][j].index.size(); l++)
						Collision(c[G[i][j].index[k]], c[G[i][j].index[l]]);
}

void ugp::ClearCircleInGrid()
{
	for (int i = 0; i < NUMG; i++)
		for (int j = 0; j < NUMG; j++)
			G[i][j].index.clear();
}

void ugp::DeleteGrid()
{
	//std::cout << "Delete grid" << std::endl;
	for (int i = 0; i < NUMG; ++i) {
		delete[] G[i];
	}
	delete[] G;
}

void ugp::InitDrawGrid()
{
	int numOfVertices = (NUMG - 1) * 8;
	lineVertices = new GLfloat[numOfVertices];

	// horizontal line
	int j = 1;
	for (int i = 0; i < (NUMG - 1) * 4; i += 4) {
		lineVertices[i] = 0;
		lineVertices[i + 1] = SCREEN_HEIGHT / NUMG * j;
		lineVertices[i + 2] = SCREEN_WIDTH;
		lineVertices[i + 3] = SCREEN_HEIGHT / NUMG * j;
		j++;
	}
	j = 1;
	for (int i = (NUMG - 1) * 4; i < numOfVertices; i += 4 ) {
		lineVertices[i] = SCREEN_WIDTH / NUMG * j;
		lineVertices[i + 1] = 0;
		lineVertices[i + 2] = SCREEN_WIDTH / NUMG * j;
		lineVertices[i + 3] = SCREEN_HEIGHT;
		j++;
	}


}
void ugp::DrawGrid()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, lineVertices);
	glDrawArrays(GL_LINES, 0, (NUMG - 1) * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ugp::DeleteDrawGrid()
{
	delete[] lineVertices;
}