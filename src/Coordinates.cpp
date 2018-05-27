#include "Coordinates.h"

namespace adhocpp {

Coordinates::Coordinates(double a, double b, double c) {
	this->x = a;
	this->y = b;
	this->z = c;
}

double Coordinates::getX(){
	return this->x;
}
double Coordinates::getY(){
	return this->y;
}
double Coordinates::getZ(){
	return this->z;
}

void Coordinates::setX(double a){
	this->x = a;
}
void Coordinates::setY(double b){
	this->y = b;
}
void Coordinates::setZ(double c){
	this->z = c;
}


} // namespace adhocpp
