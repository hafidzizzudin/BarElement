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

Node::Node(double a, double b) {
	this->x = a;
	this->y = b;
	this->index++;
	this->id = this->index;
	this->fx = 0;
	this->fy = 0;
	//cout << "new node was created : " << index<< endl;
}
double Node::getX(){
	return this->x;
}

double Node::getY(){
	return this->y;
}

double Node::getUX(){
	return this->ux;
}

double Node::getUY(){
	return this->uy;
}

void Node::getNode(){
	cout << this->x <<" " <<this->y << endl;
}

void Node::getindex(){
	cout << this->index <<endl;
}
int Node::getid(){
	return this->id ;
}

void Node::setX(double a){
	this->x = a;
}

void Node::setY(double a){
	this->y = a;
}

void Node::setUX(double a){
	this->ux = a;
}

void Node::setUY(double a){
	this->uy = a;
}

void Node::setFX(double a){
	this->fx = a;
}

void Node::setFY(double a){
	this->fy = a;
}


double Node::getFX(){
	return this->fx;
}

double Node::getFY(){
	return this->fy;
}


} // namespace adhocpp
