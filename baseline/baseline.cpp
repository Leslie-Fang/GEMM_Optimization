#include <iostream>
#include <sys/time.h>
#include "baseline.h"
#include "helper.h"

using namespace std;

void baseline(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){

	struct timeval start;
	struct timeval end;
    gettimeofday(&start,NULL);

    for(int i=0;i<M;i++){
    	for(int j=0;j<N;j++){
    		res[i*N+j] = 0;
    		for(int k=0;k<K;k++){
    			res[i*N+j] += lhs[i*K+k] * rhs[k*N+j];
    		}
    	}
    }

    gettimeofday(&end,NULL);

    cout<<"baseline Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}
	return;
}