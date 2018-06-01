#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <vector>
#include "Node.h"
#include "Coordinates.h"

namespace adhocpp {

class Element {
	Node* first ;
	Node* second;
	std::vector <std::vector<double> > K;
	int id;
	double length , Area, E, strainEng, strainTrue, stressEng, stressTrue;
	static int index;

public:
	Element(Node*,Node*, double, double);
	double getLength();

	double 	getStressEng();
	void 	setStressEng(double);

	double 	getStressTrue();
	void 	setStressTrue(double);

	double 	getStrainEng();
	void 	setStrainEng(double);

	double 	getStrainTrue();
	void 	setStrainTrue(double);

	Node* getNode1();
	Node* getNode2();

	double getE();
	std::vector <std::vector<double> > getK();
	void showK();
};

} // namespace adhocpp

#endif // _ELEMENT_H_ 
