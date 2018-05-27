//============================================================================
// Name        : BAR.cpp
// Author      : hafidz
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include "Node.h"
#include "Element.h"
#include "System.h"
#include "Mtx.h"

using namespace std;

void inputNode(ifstream&,vector<adhocpp::Node>&);
void inputElement(ifstream&,vector<adhocpp::Element>&, vector<adhocpp::Node>&);
void inputBCDisplacement (ifstream&,adhocpp::System&,vector<int>&, vector<adhocpp::Node>&);
void inputBCForce (ifstream&,adhocpp::System&,vector<adhocpp::Node>&);

int main() {
	/*
	// argv[0] is the path to your executable.
	if(argc < 2) return 0 ;

	// argv[1] is the first command line option.
	ifstream inputFile(argv[1]);
	*/

	clock_t tStart = clock();	//TIME START

	//NODE CREATING
	ifstream inputFile;
	inputFile.open("inputBar.dat");
	vector <adhocpp::Node> node;
	inputNode(inputFile,node);

	//ELEMENT CREATING
	vector <adhocpp::Element> element;
	inputElement(inputFile,element,node);


	//MATRIX SYSTEM
	adhocpp::System Sys(&node,&element);
	Sys.showStifMat();
	Sys.checkSymmetry();


	//BOUNDARY CONDITION displacement (mm, ms, GPa, kN, kg)
	vector <int> exceptForceId;
	inputBCDisplacement(inputFile,Sys,exceptForceId,node);

	//BOUNDARY CONDITION force (mm, ms, GPa, kN, kg)
	inputBCForce(inputFile,Sys,node);

	//CALCULATE DISPLACEMENT SYSTEM
	Sys.calculateDis(exceptForceId);
	Sys.showDisplacement();

	//CALCULATE FORCE SYSTEM
	Sys.calculateForce(exceptForceId);
	Sys.showForce();

	//CALCULATE STRESS SYSTEM
	Sys.calculateStress();
	Sys.showStress();

	cout << "\n\033[1;32Time for calculation : \033[0m" << (double)(clock()-tStart)/CLOCKS_PER_SEC << " sec" << endl;
	inputFile.close(); return 0;
}


void inputNode(ifstream& inputFile, vector <adhocpp::Node>& node){
	int nnode;
	inputFile >> nnode;
	string data;
	inputFile >> data >> data >> data >> data;
	for (int i=0;i<nnode;i++){
		int no;
		inputFile >> no;
		vector <double> coordinate(3);
		for (int i=0;i<3;i++){
			inputFile >> coordinate[i];
		}
		node.push_back(coordinate);
	}
}

void inputElement(ifstream& inputFile,vector<adhocpp::Element>&elm, vector<adhocpp::Node>&node){
	int nelm;
	int nodea,nodeb, no;
	double radius,modulus;

	inputFile >> nelm;
	string data;

	inputFile >> data >> data >> data >> data >> data;

	for (int i=0;i<nelm;i++){
		inputFile >> no >> nodea >> nodeb >> radius >> modulus;
		elm.push_back(adhocpp::Element(&node[nodea-1],&node[nodeb-1],radius,modulus));
	}
}

void inputBCDisplacement (ifstream& inputFile,adhocpp::System& Sys,vector<int>& exceptForceId,vector<adhocpp::Node>& node){
	int nBC;
	inputFile >> nBC;
	string data;
	inputFile >> data >> data >> data >> data;
	for (int i=0;i<nBC;i++){
		int id, cord,no;
		double val;
		string dis;

		inputFile >> no >> id >> dis >> val ;
		if (dis == "ux"){
			node[id-1].setUX(val);
			cord = (id-1)*3;
		}
		else if (dis == "uy"){
			node[id-1].setUY(val);
			cord = (id-1)*3+1;
		}
		else if (dis == "uz"){
			node[id-1].setUZ(val);
			cord = (id-1)*3+2;
		}

		Sys.setDis(cord,val);
		exceptForceId.push_back(cord);
	}
}

void inputBCForce (ifstream& inputFile,adhocpp::System& Sys,vector<adhocpp::Node>& node){
	int nF;
	inputFile >> nF;
	string tmp;
	inputFile >> tmp >> tmp >> tmp >> tmp;
	for (int i=0;i<nF;i++){
		int id,cord,no;
		double val;
		string f;
		inputFile >>no>> id >> f >> val;
		if (f == "fx"){
			node[id-1].setFX(val);
			cord = (id-1)*3;
		}
		else if (f == "fy"){
			node[id-1].setFY(val);
			cord = (id-1)*3+1;
		}
		else if (f == "fz"){
			node[id-1].setFZ(val);
			cord = (id-1)*3+2;
		}
		Sys.setForce(cord,val);
	}
}
