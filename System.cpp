/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Internal Includes ---
#include "System.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Node.h"

namespace adhocpp {
	System::System(int nnd, std::vector<Node>* pointertonode, std::vector<Element> elm){
		this->vecNode = pointertonode;
		this->vecElement = elm;
		this->displacement.resize(nnd*2);
		this->force.resize(nnd*2);

		this->stifmat.resize(nnd*2);
		for(unsigned i=0;i<stifmat.size();i++){
			this->stifmat[i].resize(nnd*2,0);
		}


		for (unsigned i=0;i<this->vecElement.size();i++){
			int idnode1 = this->vecElement[i].getNode1()->getid() , idnode2 = this->vecElement[i].getNode2()->getid();
			for (int r=0;r<4;r++){
				int R;
				if(r<2){
					R = (idnode1-1)*2+r;
				}
				else{
					R = (idnode2-1)*2+r%2;
				}

				for(int c=0;c<4;c++){
					int C;
					if (c<2){
						C = (idnode1-1)*2+c;
					}
					else{
						C = (idnode2-1)*2+c%2;
					}
					this->stifmat[R][C] = this->stifmat[R][C] + this->vecElement[i].getK()[r][c];
				}
			}
		}

	}


	void System::showStifMat(){
		std::cout << "STIFNESS MATRIX SYSTEM\n"<< std::endl;
		int oldprec = std::cout.precision();
		for (unsigned i=0;i<this->stifmat.size();i++){
			for(unsigned j=0;j<this->stifmat[i].size();j++){
				std::cout << std::setw(10) << std::setprecision(3) << this->stifmat[i][j] ;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout.precision(oldprec);
	}


	void System::checkSymmetry(){
		bool check = true;
		for (unsigned i=1;i<this->stifmat.size();i++){
			for (unsigned j=0;j<i;j++){
				if (this->stifmat[i][j] != this->stifmat[j][i]){
					check = !check;
					goto out;
				}
			}
		}
		out:
		if(check){
			std::cout << "The stiffness matrix is symmetry\n\n";
		}
		else{
			std::cout << "The stiffness matrix is not symmetry, please check again\n\n";
		}
	}

	void System::setDis(int id, double val){
		this->displacement[id] = val;
	}

	void System::setForce(int id, double val){
		this->force[id] = val;
	}

	void System::showForce(){
		for (unsigned i=0;i<this->force.size();i++){
			std::cout << this->force[i] << std::endl;
		}
		std::cout << std::endl;
	}

	void System::calculateDis(std::vector<int> except){
		std::sort(except.begin(),except.end());
		std::reverse(except.begin(),except.end());

		//COPY STIF AND FORCE
		vector<vector<double> > modStifMat = this->stifmat;
		vector <double> modForce = this->force;

		//SHRINKING
		for (unsigned i=0;i<except.size();i++){
			//shrinking force
			modForce.erase(modForce.begin()+except[i]);

			//shrinking stifmat
			modStifMat.erase(modStifMat.begin()+except[i]);
			for (unsigned j=0;j<modStifMat.size();j++){
				modStifMat[j].erase(modStifMat[j].begin()+except[i]);
			}
		}

		//CALCULATION DISPLACEMENT

		modForce = Mtx::GaussElim(modStifMat,modForce);

		std::reverse(except.begin(),except.end());
		int loc = 0,disloc=0;
		for (int k=0;k<(int)this->displacement.size();k++){
			if (loc<(int)except.size()){
			if (k == except[loc]){
				loc++;
			}
			else{
				this->displacement[k] = modForce[disloc];
				disloc++;
			}
			}
			else{
				this->displacement[k] = modForce[disloc];
				disloc++;
			}
		}
		//ASSIGN DISPLACEMENT ON NODE
		for (unsigned i=0;i<this->displacement.size();i++){
			int idnode = i/2,uxuy = i%2;
			if (uxuy == 0){
				(*vecNode)[idnode].setUX(this->displacement[i]);
			}
			else if(uxuy == 1){
				(*vecNode)[idnode].setUY(this->displacement[i]);
			}
		}
	}

	void System::showDisplacement(){
		int oldprec = std::cout.precision();
		for (unsigned i=0;i<this->vecNode->size();i++){
			std::cout <<std::setw(7) << std::fixed << std::setprecision(4) << (*vecNode)[i].getUX() << endl;
			std::cout <<std::setw(7) << (*vecNode)[i].getUY() << endl;
		}
		std::cout.precision(oldprec);
		std::cout << std::endl;
	}

	void System::calculateForce(vector<int> exept){

	}

	std::vector<std::vector<double> > System::getStifMat(){
		return this->stifmat;
	}

	std::vector<double> System::getForce(){
		return this->force;
	}

	std::vector <double> System::getDis(){
		return this->displacement;
	}

} // namespace adhocpp
