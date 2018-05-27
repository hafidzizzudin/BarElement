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
#include "Node.h"
#include <iostream>
using namespace std;

namespace adhocpp {
int Node::index = 0;

Node::Node(vector <double> loc) {
	this->location = loc;
	this->x = loc[0];
	this->y = loc[1];
	this->z = loc[2];
	this->index++;
	this->id = this->index;
	this->fx = 0;
	this->fy = 0;
	this->fz = 0;

	//cout << "new node was created : " << index<< endl;
	//cout << "location : " << location[0] <<" " << location[1] <<" " << location[2] << endl;
}
double Node::getX(){
	return x;
}

double Node::getY(){
	return y;
}

double Node::getZ(){
	return z;
}

double Node::getUX(){
	return this->ux;
}

double Node::getUY(){
	return this->uy;
}
double Node::getUZ(){
	return this->uz;
}

void Node::getNode(){
	cout << this->location[0] <<" " <<this->location[1] << " " << this->location[2]<< endl;
}

void Node::getindex(){
	cout << this->index <<endl;
}
int Node::getid(){
	return this->id ;
}

void Node::setX(double a){
	this->location[0] = a;
}

void Node::setY(double a){
	this->location[1] = a;
}

void Node::setZ(double a){
	this->location[2] = a;
}

void Node::setUX(double a){
	this->ux = a;
}

void Node::setUY(double a){
	this->uy = a;
}

void Node::setUZ(double a){
	this->uz = a;
}

void Node::setFX(double a){
	this->fx = a;
}

void Node::setFY(double a){
	this->fy = a;
}

void Node::setFZ(double a){
	this->fz = a;
}


double Node::getFX(){
	return this->fx;
}

double Node::getFY(){
	return this->fy;
}

double Node::getFZ(){
	return this->fz;
}


} // namespace adhocpp
