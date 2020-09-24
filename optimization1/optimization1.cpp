#include <iostream>
#include <sys/time.h>
#include "optimization1.h"
#include "helper.h"

using namespace std;

void optimization1(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){

	struct timeval start;
	struct timeval end;
    
    register float res0, res1, res2, res3, lhs0; //Define the variable in register

    gettimeofday(&start,NULL);

    for(int i=0;i<M;i++){
    	for(int j=0;j<N;j += 4){
            res0 = 0;
            res1 = 0;
            res2 = 0;
            res3 = 0;
    		for(int k=0;k<K;k++){
                lhs0 = lhs[i*K+k];
    			res0 += lhs0 * rhs[k*N+j];
    			res1 += lhs0 * rhs[k*N+j+1];
    			res2 += lhs0 * rhs[k*N+j+2];
    			res3 += lhs0 * rhs[k*N+j+3];
    		}
            res[i*N+j] = res0;
            res[i*N+j+1] = res1;
            res[i*N+j+2] = res2;
            res[i*N+j+3] = res3;
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