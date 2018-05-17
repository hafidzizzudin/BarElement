/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <vector>
#include "Node.h"

namespace adhocpp {

class Element {
	Node* first;
	Node* second;
	std::vector <std::vector<double> > K;
	int id;
	double length , Area, E;
	static int index;

public:
	Element(Node*,Node*, double, double);
	void getLength();
	Node* getNode1();
	Node* getNode2();
	std::vector <std::vector<double> > getK();
	void showK();
};

} // namespace adhocpp

#endif // _ELEMENT_H_ 
