#include <iostream>
#include <ctime>
#include <cstdlib>
#include "helper.h"
using namespace std;

shared_ptr<float[]> matrix_generate_2D(bool RowMajor){
	cout<<"this is the matrix_generate_2D function"<<endl;

    shared_ptr<float[]> a(new float[M*N]);
	srand(time(0));
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			*(a.get()+i*M+j)=rand()/(double)RAND_MAX;
		}
	}
	return a;
}