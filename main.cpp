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

void inputNode(ifstream&,vector<adhocpp::Node>&);
void inputElement(ifstream&,vector<adhocpp::Element>&, vector<adhocpp::Node>&);

using namespace std;

int main() {
	clock_t tStart = clock();	//TIME START

	//NODE CREATING
	ifstream infile("/home/hafidz/workspace/BAR/src/inputBar.dat");
	vector <adhocpp::Node> node;
	inputNode(infile,node);

	//ELEMENT CREATING
	vector <adhocpp::Element> elm;
	inputElement(infile,elm,node);


	//MATRIX SYSTEM
	adhocpp::System Sys(node.size(),&node,elm);
	Sys.showStifMat();
	Sys.checkSymmetry();

	//BOUNDARY CONDITION displacement (mm, ms, GPa, kN, kg)
	vector <int> exceptForceId;
	int nBC;
	infile >> nBC;
	for (int i=0;i<nBC;i++){

		int id,val,cord;
		string dis;
		infile >> id >> dis >> val;
		if (dis == "ux"){
			node[id-1].setUX(val);
			cord = (id-1)*2;
		}
		else if (dis == "uy"){
			node[id-1].setUY(val);
			cord = (id-1)*2+1;
		}
		Sys.setDis(cord,val);
		exceptForceId.push_back(cord);
	}

	//BOUNDARY CONDITION force (mm, ms, GPa, kN, kg)
	int nF;
	infile >> nF;
	for (int i=0;i<nBC;i++){

		int id,val,cord;
		string f;
		infile >> id >> f >> val;
		if (f == "fx"){
			node[id-1].setFX(val);
			cord = (id-1)*2;
		}
		else if (f == "fy"){
			node[id-1].setFY(val);
			cord = (id-1)*2+1;
		}
		Sys.setForce(cord,val);
	}

	Sys.calculateDis(exceptForceId);
	Sys.showDisplacement();
	Sys.showForce();


	cout << "\n\033[1;32Time for calculation : \033[0m" << (double)(clock()-tStart)/CLOCKS_PER_SEC << " sec" << endl;
	infile.close(); return 0;
}

void inputNode(ifstream& infile, vector <adhocpp::Node>& node){
	int nnode;
	infile >> nnode;
	for (int i=0;i<nnode;i++){
		double x,y;
		infile >> x >> y;
		node.push_back(adhocpp::Node(x,y));
	}
}

void inputElement(ifstream& infile,vector<adhocpp::Element>&elm, vector<adhocpp::Node>&node){
	int nelm;
	infile >> nelm;
	for (int i=0;i<nelm;i++){
		int a,b;
		double x,y;
		infile >>a >>b>> x >> y;
		elm.push_back(adhocpp::Element(&node[a-1],&node[b-1],x,y));
	}
}
