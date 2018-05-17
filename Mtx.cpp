#include "Mtx.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

Mtx::Mtx(int n, double** a) {
  dimn = n;
  mx = new double* [dimn];
  for (int i =  0; i< dimn; i++)
  {
    mx[i] = new double [dimn];
    for (int j = 0; j < dimn; j++) mx[i][j] = a[i][j];
  }
}

Mtx::Mtx(vector <vector <double> > a){
	this->mat = a;
}

// copy constructor
Mtx::Mtx(const Mtx& M)
{
  dimn = M.dimn;
  mx = new double* [dimn];
  for (int i =  0; i < dimn; i++)
  {
    mx[i] = new double [dimn];
    for (int j = 0; j < dimn; j++) mx[i][j] = M.mx[i][j];
  }

}
// copy assignment
Mtx& Mtx::operator=(const Mtx& M)
{
  if (dimn!=M.dimn) {cout << "Matrices have different size in =";}
  for (int i =  0; i < dimn; i++)
  {
    for (int j = 0; j < dimn; j++) mx[i][j] = M.mx[i][j];

  }
  return *this;
}
// print matrix
void Mtx::print() const
{
	for (int i=0; i<dimn; i++)
    {
		for (int j=0;j<dimn;j++) cout << mx[i][j] << "\t";
	    cout << endl;
	}
}
// one norm
double Mtx::onenorm() const
{
	double norm = 0.0;

	for (int j = 0; j < dimn; j++)
	{
		double temp = 0.0;	// store column abs sum
		for (int i = 0; i < dimn; i++) temp += fabs(mx[i][j]);
		norm = max(norm, temp);
	}
	return norm;
}
// maximum norm
double Mtx::maxnorm() const
{
	double norm = 0.0;

	for (int i = 0; i < dimn; i++)
	{
		double temp = 0.0;	// store column abs sum
		for (int j = 0; j < dimn; j++) temp += fabs(mx[i][j]);
		norm = max(norm, temp);
	}
	return norm;
}
// Frobenius norm
double Mtx::frobnorm() const
{
	double norm = 0.0;

	for (int i = 0; i < dimn; i++)
		for (int j = 0; j < dimn; j++)	norm += mx[i][j] * mx[i][j];

	return sqrt(norm);
}
// Gaussian elimination A x = bb
vector<double> Mtx::GaussElim(vector <vector <double> > tmpx,vector<double> bb)
{
  int size = (int)tmpx.size();

  // LU decomposition without pivoting
  for (int k = 0; k < size - 1; k++) {
    if (tmpx[k][k] == 0)
      {cout << "pivot is zero in Mtx::GaussElim()";}
    for (int i = k + 1; i < size; i++) {
      if (tmpx[i][k] != 0) {   // tmpx[i][k] can be complex
        double mult = tmpx[i][k]/tmpx[k][k];
        tmpx[i][k] = mult;
        for (int j = k + 1; j < size; j++)
          tmpx[i][j] -= mult*tmpx[k][j];
      }
    }
  }

  // forwad substitution for L y = b. y still stored in bb
  for (int i = 1; i < size; i++)
    for (int j = 0; j < i; j++) bb[i] -= tmpx[i][j]*bb[j];

  // back substitution for U x = y. x still stored in bb
  for (int i = size - 1; i >= 0; i--) {
    for (int j=i+1; j<size; j++) bb[i] -= tmpx[i][j]*bb[j];
    bb[i] /= tmpx[i][i];
  }
  return bb;
} // end GaussElim()

