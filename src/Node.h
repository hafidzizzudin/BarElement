#ifndef _NODE_H_
#define _NODE_H_
#include <vector>

namespace adhocpp {

class Node {
	std::vector <double> location;
	double x,y,z,ux,uy,uz,fx, fy,fz;
	int id;
	static int index;
public:
	Node(std::vector <double>);
	void getNode();
	void getindex();
	int getid();
	double getX();
	double getY();
	double getZ();

	double getUX();
	double getUY();
	double getUZ();

	void setX(double);
	void setY(double);
	void setZ(double);

	void setUX(double);
	void setUY(double);
	void setUZ(double);

	void setFX(double);
	void setFY(double);
	void setFZ(double);

	double getFX();
	double getFY();
	double getFZ();


};

} // namespace adhocpp

#endif // _NODE_H_ 
