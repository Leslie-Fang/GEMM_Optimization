#include <iostream>
#include <sys/time.h>
#include "optimization2.h"
#include "helper.h"

using namespace std;

void optimization2(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){
	struct timeval start;
	struct timeval end;
    
    //Define the variable in register
    register float res00, res01, res02, res03; 
    register float res10, res11, res12, res13;
    register float res20, res21, res22, res23;
    register float res30, res31, res32, res33;
    register float lhs0, lhs1, lhs2, lhs3;
    register float rhs0, rhs1, rhs2, rhs3;

    gettimeofday(&start,NULL);

    for(int i=0;i<M;i += 4){
    	for(int j=0;j<N;j += 4){
            res00 = 0; res01 = 0; res02 = 0; res03 = 0;
            res10 = 0; res11 = 0; res12 = 0; res13 = 0;
            res20 = 0; res21 = 0; res22 = 0; res23 = 0;
            res30 = 0; res31 = 0; res32 = 0; res33 = 0;

            //float * rhs0 = nullptr;
    		for(int k=0; k<K; k++){
                rhs0 = rhs[k*N+j];
                rhs1 = rhs[k*N+j+1];
                rhs2 = rhs[k*N+j+2];
                rhs3 = rhs[k*N+j+3];

                lhs0 = lhs[i*K+k];
                lhs1 = lhs[(i+1)*K+k];
                lhs2 = lhs[(i+2)*K+k];
                lhs3 = lhs[(i+3)*K+k];

    			res00 += lhs0 * rhs0;
    			res01 += lhs0 * rhs1;
    			res02 += lhs0 * rhs2;
    			res03 += lhs0 * rhs3;

                res10 += lhs1 * rhs0;
                res11 += lhs1 * rhs1;
                res12 += lhs1 * rhs2;
                res13 += lhs1 * rhs3;

                res20 += lhs2 * rhs0;
                res21 += lhs2 * rhs1;
                res22 += lhs2 * rhs2;
                res23 += lhs2 * rhs3;

                res30 += lhs3 * rhs0;
                res31 += lhs3 * rhs1;
                res32 += lhs3 * rhs2;
                res33 += lhs3 * rhs3;
    		}
            res[i*N+j] = res00;
            res[i*N+j+1] = res01;
            res[i*N+j+2] = res02;
            res[i*N+j+3] = res03;

            res[(i+1)*N+j] = res10;
            res[(i+1)*N+j+1] = res11;
            res[(i+1)*N+j+2] = res12;
            res[(i+1)*N+j+3] = res13;

            res[(i+2)*N+j] = res20;
            res[(i+2)*N+j+1] = res21;
            res[(i+2)*N+j+2] = res22;
            res[(i+2)*N+j+3] = res23;

            res[(i+3)*N+j] = res30;
            res[(i+3)*N+j+1] = res31;
            res[(i+3)*N+j+2] = res32;
            res[(i+3)*N+j+3] = res33;
    	}
    }

    
    gettimeofday(&end,NULL);

    cout<<"Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}

	return;
}
