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
#include "Element.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
const double pi = 3.1415926535897;
using namespace std;

namespace adhocpp {
int Element::index = 0;

Element::Element(Node* a, Node* b, double r, double E){
	first = a;
	second = b;
	this->length = pow(pow((this->first->getX() - this->second->getX()),2) + pow((this->first->getY() - this->second->getY()), 2),0.5);
	this->Area = pi*r*r;
	this->E = E;
	index++;
	this->id = index;
	/*
	//bar element creator
	for (int i=0;i<4;i++){
		vector <double> tmp;
		for (int j=0;j<4;j++){
			if ((i==0 && i==j) || (i==2 && i==j)){
				tmp.push_back(this->Area*this->E/this->length);
			}
			else if( (i==0 && j==2) || (i==2 && j==0) ){
				tmp.push_back(-this->Area*this->E/this->length);
			}
			else{
				tmp.push_back(0.0);
			}
		}
		K.push_back(tmp);
	}
	*/
	//rotation
	double dx = this->second->getX()-this->first->getX();
	double dy = this->second->getY()-this->first->getY();
	double c = dx/this->length,s=dy/this->length;

	this->K.resize(4);
	for (int i=0;i<4;i++){
		this->K[i].resize(4);
		for(int j=0;j<4;j++){
			if(i==j){
				if(i%2 == 0){
					this->K[i][j] = this->Area*this->E*c*c/this->length;
				}
				else{
					this->K[i][j] = this->Area*this->E*s*s/this->length;
				}
			}
			else{
				if ((i+j)%2 == 0){
					if (i%2==0){
						this->K[i][j] = -this->Area*this->E*c*c/this->length;
					}
					else{
						this->K[i][j] = -this->Area*this->E*s*s/this->length;
					}
				}
				else{
					if((i+j) == 3){
						this->K[i][j] = -this->Area*this->E*c*s/this->length;
					}
					else{
						this->K[i][j] =  this->Area*this->E*c*s/this->length;
					}
				}
			}
		}
	}

	cout <<"success creating element : " << id << endl << "size of mat : " << K.size() <<"x" << K[0].size() << endl;;
	this->showK();
}

void Element::getLength(){
	cout << length <<endl;
}

Node* Element::getNode1(){
	return this->first;
}

Node* Element::getNode2(){
	return this->second;
}

vector<vector<double> > Element::getK(){
	return this->K;
}

void Element::showK(){
	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			cout << setw(10) << setprecision(3) <<this->K[i][j];
		}
		cout << endl;
	}
}

} // namespace adhocpp
