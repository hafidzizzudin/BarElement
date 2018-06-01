/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <vector>
#include "Node.h"
#include "Element.h"
#include "Mtx.h"

namespace adhocpp {

class System {
	std::vector < std::vector<double> > stifmat;
	std::vector <Element>* vecElement;
	std::vector <Node>* vecNode;
	std::vector <double> displacement;
	std::vector <double> force;



public:
	System(std::vector<Node>*,std::vector<Element>*);
	void showStifMat();
	void checkSymmetry();
	void setDis(int, double);
	void setForce (int, double);
	void showForce ();
	void showDisplacement();

	void showStressEng();
	void showStressTrue();

	void showStrainEng();
	void showStrainTrue();

	void calculateDis(std::vector <int>);
	void calculateForce(std::vector <int>);
	void calculateStressStrain();

	std::vector<std::vector<double> > getStifMat();
	std::vector <double> getForce();
	std::vector <double> getDis();

};

} // namespace adhocpp

#endif // _SYSTEM_H_ 
