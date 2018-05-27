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
#include <math.h>
#include <algorithm>
#include "Node.h"

namespace adhocpp {
	System::System(std::vector<Node>* pointertonode, std::vector<Element>* elm){
		this->vecNode = pointertonode;
		this->vecElement = elm;
		this->displacement.resize((*this->vecNode).size()*3);
		this->force.resize((*this->vecNode).size()*3);

		this->stifmat.resize((*this->vecNode).size()*3);
		for(unsigned i=0;i<stifmat.size();i++){
			this->stifmat[i].resize((*this->vecNode).size()*3,0);
		}

		/*
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
		*/
		for (unsigned i=0;i<(*this->vecElement).size();i++){
			int idnode1 = (*this->vecElement)[i].getNode1()->getid() , idnode2 = (*this->vecElement)[i].getNode2()->getid();
			for (int r=0;r<6;r++){
				int R;
				if(r<3){
					R = (idnode1-1)*3+r;
				}
				else{
					R = (idnode2-1)*3+r%3;
				}

				for(int c=0;c<6;c++){
					int C;
					if (c<3){
						C = (idnode1-1)*3+c;
					}
					else{
						C = (idnode2-1)*3+c%3;
					}
					this->stifmat[R][C] = this->stifmat[R][C] + (*this->vecElement)[i].getK()[r][c];
				}
			}
		}

	}//System


	void System::showStifMat(){
		std::ios_base::fmtflags f( cout.flags() );
		std::cout << "STIFNESS MATRIX SYSTEM\n"<< std::endl;

		for (unsigned i=0;i<this->stifmat.size();i++){
			for(unsigned j=0;j<this->stifmat[i].size();j++){
				std::cout << std::setw(10) << std::setprecision(4) << this->stifmat[i][j] ;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		cout.flags( f );
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

	void System::calculateDis(std::vector<int> except){
		std::sort(except.begin(),except.end());
		std::reverse(except.begin(),except.end()); //become descending

		//COPY STIF AND FORCE
		vector<vector<double> > modStifMat = this->stifmat;
		vector <double> modForce = this->force;

		//ERASING ROW
		for (unsigned i=0;i<except.size();i++){
			//shrinking force
			modForce.erase(modForce.begin()+except[i]);

			//shrinking stifmat
			modStifMat.erase(modStifMat.begin()+except[i]);
		}

		//INCLUDE KNOWN BOUNDARY IN FORCE
		for (unsigned i=0;i<modForce.size();i++){
			for (unsigned j=0;j<except.size();j++){
				modForce[i] = modForce[i] - modStifMat[i][except[j]]*this->displacement[except[j]];
			}
		}

		//ERASING COLOMN OF STIFFNESS MATRIX
		for (unsigned i=0;i<modStifMat.size();i++){
			for (unsigned j=0;j<except.size();j++){
				modStifMat[i].erase(modStifMat[i].begin()+except[j]);
			}
		}

		//CALCULATION DISPLACEMENT

		modForce = Mtx::GaussElim(modStifMat,modForce);

		std::reverse(except.begin(),except.end()); //become ascending
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
			int idnode = i/3,uxuy = i%3;
			if (uxuy == 0){
				(*vecNode)[idnode].setUX(this->displacement[i]);
			}
			else if(uxuy == 1){
				(*vecNode)[idnode].setUY(this->displacement[i]);
			}
			else if(uxuy == 2){
				(*vecNode)[idnode].setUZ(this->displacement[i]);
			}
		}
	}//Calculate displacement

	void System::showDisplacement(){
		std::ios_base::fmtflags f( cout.flags() );
		std::cout <<"DISPLACEMENT OF THE SYSTEM :" << std::endl;
		for (unsigned i=0;i<this->vecNode->size();i++){
			std::cout<< "UX"<< i+1 <<"	" <<std::setw(7) << std::fixed << std::setprecision(4) << (*vecNode)[i].getUX() << " mm" << endl;
			std::cout<< "UY"<< i+1 <<"	" <<std::setw(7) << (*vecNode)[i].getUY() << " mm" << endl;
			std::cout<< "UZ"<< i+1 <<"	" <<std::setw(7) << (*vecNode)[i].getUZ() << " mm" << endl;
		}
		cout.flags( f );
		std::cout << std::endl;
	}

	void System::showForce(){
		std::ios_base::fmtflags f( std::cout.flags() );
		std::cout <<"FORCE OF THE SYSTEM :" << std::endl;
		for (unsigned i=0;i<this->vecNode->size();i++){
			std::cout <<"FX"<< i+1 <<"	" <<std::setw(7) << std::fixed << std::setprecision(4) << (*vecNode)[i].getFX() << " kN"<<std::endl;
			std::cout <<"FY"<< i+1 <<"	" <<std::setw(7) << (*vecNode)[i].getFY() << " kN" << std::endl;
			std::cout <<"FZ"<< i+1 <<"	" <<std::setw(7) << (*vecNode)[i].getFZ() << " kN" << std::endl;
		}
		std::cout.flags( f );
		std::cout << std::endl;

	}

	void System::showStress(){
		std::ios_base::fmtflags f( std::cout.flags() );
		std::cout <<"STRESS OF THE SYSTEM :" << std::endl;
		for (unsigned i=0;i<(*this->vecElement).size();i++){
			std::cout <<"Stress in element "<< i+1 <<"	: " << std::setw(7) << std::fixed << std::setprecision(4) << (*this->vecElement)[i].getStress() << " GPa" << std::endl;
		}
		std::cout.flags( f );
		std::cout << std::endl;
	}//Show Stress

	void System::calculateForce(vector<int> exept){
		std::sort(exept.begin(),exept.end());
		std::reverse(exept.begin(),exept.end());//become descending

		for (unsigned i=0;i<exept.size();i++){
			for (unsigned j=0;j<this->displacement.size();j++){
				this->force[exept[i]] = this->force[exept[i]] + this->stifmat[exept[i]][j]*this->displacement[j];
			}
		}

		//ASSIGN FORCE ON NODE
		for (unsigned i=0;i<this->force.size();i++){
			int idnode = i/3,uxuy = i%3;
			if (uxuy == 0){
				(*vecNode)[idnode].setFX(this->force[i]);
			}
			else if(uxuy == 1){
				(*vecNode)[idnode].setFY(this->force[i]);
			}
			else if(uxuy == 2){
				(*vecNode)[idnode].setFZ(this->force[i]);
			}
		}
	}//Calculate Force

	void System::calculateStress(){
		for (unsigned i=0;i<(*this->vecElement).size();i++){
			double x1,y1,z1,x2,y2,z2;
			x1 = (*this->vecElement)[i].getNode1()->getX() + (*this->vecElement)[i].getNode1()->getUX();
			y1 = (*this->vecElement)[i].getNode1()->getY() + (*this->vecElement)[i].getNode1()->getUY();
			z1 = (*this->vecElement)[i].getNode1()->getZ() + (*this->vecElement)[i].getNode1()->getUZ();

			x2 = (*this->vecElement)[i].getNode2()->getX() + (*this->vecElement)[i].getNode2()->getUX();
			y2 = (*this->vecElement)[i].getNode2()->getY() + (*this->vecElement)[i].getNode2()->getUY();
			z2 = (*this->vecElement)[i].getNode2()->getZ() + (*this->vecElement)[i].getNode2()->getUZ();

			double dx = x2-x1, dy = y2-y1, dz = z2-z1;

			double lnew = pow(pow(dx,2)+pow(dy,2)+pow(dz,2),0.5);

			double strain = fabs((lnew-(*this->vecElement)[i].getLength()))/(*this->vecElement)[i].getLength();

			(*this->vecElement)[i].setStress( (*this->vecElement)[i].getE()*strain );
		}

	}//Calculate Stress

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
