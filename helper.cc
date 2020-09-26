#include <iostream>
#include <ctime>
#include <cstdlib>
#include "helper.h"
using namespace std;

shared_ptr<float[]> matrix_lhs_generate_2D(bool RowMajor){
	cout<<"this is the matrix_generate_2D function"<<endl;

    shared_ptr<float[]> a(new float[M*K]);
	srand(time(0));
	for(int i=0;i<M;i++){
		for(int j=0;j<K;j++){
			*(a.get()+i*K+j)=rand()/(double)RAND_MAX;
		}
	}
	return a;
}

shared_ptr<float[]> matrix_rhs_generate_2D(bool RowMajor){
	cout<<"this is the matrix_generate_2D function"<<endl;

    shared_ptr<float[]> a(new float[K*N]);
	srand(time(0));
	for(int i=0;i<K;i++){
		for(int j=0;j<N;j++){
			*(a.get()+i*N+j)=rand()/(double)RAND_MAX;
		}
	}
	return a;
}

shared_ptr<float[]> rhs_memory_layout_reorder_to_ColMajor(shared_ptr<float[]> input){
    shared_ptr<float[]> a(new float[K*N]);
    for(int i=0;i<K;i++){
		for(int j=0;j<N;j++){
			*(a.get()+i+j*K)= *(input.get()+i*N+j);
		}
	}
	return a;
}

shared_ptr<float[]> rhs_memory_layout_reorder_to_RowMajor(shared_ptr<float[]> input){
    shared_ptr<float[]> a(new float[K*N]);
    for(int i=0;i<K;i++){
		for(int j=0;j<N;j++){
			//*(a.get()+i+j*K)= *(input.get()+i*N+j);
			*(a.get()+i*N+j)= *(input.get()+i+j*K);
		}
	}
	return a;
}