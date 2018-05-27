#ifndef MTX_H
#define MTX_H
#include <vector>

using namespace std;
class Mtx {											// square matrix

private:
  int dimn;											// dimension of matrix
  double** mx;										// entries of the matrix
  vector <vector <double> > mat;

public:
  Mtx(int n, double** t=0);							// constructor, all entries = t
  Mtx(vector <vector <double> >);
  Mtx(const Mtx& );									// copy constructor
  Mtx& operator=(const Mtx&);						// copy assignment
  ~Mtx(){											// destructor
    for (int i = 0; i< dimn; i++) delete[]  mx[i];
    delete[] mx;
  }

  double* operator[](int i) const { return mx[i]; }	// subscript, entry at row i and
													// column j is [i][j]

  double onenorm() const;							// one norm
  double maxnorm() const;							// maximum norm
  double frobnorm() const;							// Frobenius norm
  static vector<double> GaussElim(vector <vector <double> >,vector <double>);					// Gaussian elimination A x = bb
  void print() const;								// print matrix
};


#endif // MTX_H
