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
	this->first = a;

	this->second = b;

	double dx = this->second->getX() - this->first->getX();
	double dy = this->second->getY() - this->first->getY();
	double dz = this->second->getZ() - this->first->getZ();
	this->length = pow((pow(dx,2) + pow(dy, 2) + pow(dz,2)),0.5);

	this->Area = pi*r*r;

	this->E = E;

	index++;
	this->id = index;

	/*
	//BAR ELEMENT 1D CREATOR
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
	/*
	//BAR ELEMENT 2D CREATOR
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
	*/

	//BAR ELEMENT 3D CREATOR
	double Cx = dx/this->length, Cy = dy/this->length, Cz = dz/this->length;

	this->K.resize(6);
	for(int i=0;i<(int)this->K.size();i++){
		this->K[i].resize(6);
		for (int j=0;j<(int)this->K[i].size();j++){
			vector <int> index(2);
			vector <double> C(2);
			index[0]=i%3+1,index[1]=j%3+1;
			for (unsigned k=0;k<C.size();k++){
				if (index[k] == 1){
					C[k] = Cx;
				}
				else if (index[k] == 2){
					C[k] = Cy;
				}
				else if (index[k] == 3){
					C[k] = Cz;
				}
			}

			this->K[i][j] = this->Area*this->E*C[0]*C[1]/this->length;

			if (fabs(K[i][j]) < 1e-100){
				K[i][j] = 0;
				continue;
			}


			if((i<3 && j<3) || (i>=3 && j>=3)){
				continue;
			}
			else{
				this->K[i][j] = -1*this->K[i][j];
			}
		}
	}

	//cout <<"success creating element : " << id << endl << "size of mat : " << K.size() <<"x" << K[0].size() << endl;;
	//this->showK();
}

double Element::getLength(){
	return this->length;
}

Node* Element::getNode1(){
	return this->first;
}

Node* Element::getNode2(){
	return this->second;
}

double Element::getStress(){
	return this->stress;
}//Get Stress

double Element::getE(){
	return this->E;
}//Get Modulus young;

void Element::setStress(double sigma){
	this->stress = sigma;
}//Set Stress

vector<vector<double> > Element::getK(){
	return this->K;
}

void Element::showK(){
	//ios_base::fmtflags f( cout.flags() );
	for (unsigned i=0;i<this->K.size();i++){
		for (unsigned j=0;j<this->K[i].size();j++){
			cout << setw(10) << setprecision(4) << this->K[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//cout.flags( f );
}

} // namespace adhocpp
