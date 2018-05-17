/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef _NODE_H_
#define _NODE_H_

namespace adhocpp {

class Node {
	double x, y,ux,uy,fx, fy;
	int id;
	static int index;
public:
	Node(double, double);
	void getNode();
	void getindex();
	int getid();
	double getX();
	double getY();
	double getUX();
	double getUY();

	void setX(double);
	void setY(double);
	void setUX(double);
	void setUY(double);
	void setFX(double);
	void setFY(double);

	double getFX();
	double getFY();


};

} // namespace adhocpp

#endif // _NODE_H_ 
