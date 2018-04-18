#include <string>
#include <vector>
#include "de_solver.h"
#include "task.h"


/*
Bound numbers

     2
	+--+
	|  | 3
	|  |     4
1	|  +_______+
	|          | 5
	+----------+
	    6
*/

int main(int argc, char** argv) {
	Task* task = new Task(1.0, 1.0);
	task->boundaryConditions[0] = 1;
	task->boundaryConditions[1] = 1;
	task->boundaryConditions[2] = 1;
	task->boundaryConditions[3] = 1;
	task->boundaryConditions[4] = 1;
	task->boundaryConditions[5] = 1;
	std::vector<double> ox, oy;
	ox.push_back(1.0);
	ox.push_back(2.0);
	ox.push_back(4.0);
	oy.push_back(1.0);
	oy.push_back(2.0);
	oy.push_back(3.0);
	
	Domain domain(ox, oy);
	DESolver solver(domain, task);
	solver.solve();
	solver.printInfo(ox, oy);

	return 0;
}