#ifndef UGP_CLASS_H
#define UGP_CLASS_H

#include "Circle.h"
#include <vector>

struct Grid {
	std::vector<int> index;
};

class ugp {
private:
	Grid** G;
	GLfloat* lineVertices;
	Circle* c;
	int NUMG;
	int n;
public:
	ugp(int numberOfGrid, Circle* circle, int size);
	void InsertToGrid(); // insert index of circle to a grid
	void IterCircleInGrid(); // Itterate the circle in each grid to check collision
	void ClearCircleInGrid(); // clear all circle in each grid
	void DeleteGrid(); // delete grid
	void InitDrawGrid();
	void DrawGrid();
	void DeleteDrawGrid();
};

#endif