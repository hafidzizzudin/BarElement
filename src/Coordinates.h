#ifndef _COORDINATES_H_
#define _COORDINATES_H_

namespace adhocpp {

class Coordinates {
	double x,y,z;
public:
	Coordinates(double, double, double);

	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);


};

} // namespace adhocpp

#endif // _COORDINATES_H_ 
