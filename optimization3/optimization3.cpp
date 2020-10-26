#include <iostream>
#include <sys/time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <fmaintrin.h>
#include "optimization3.h"
#include "helper.h"

using namespace std;

void optimization3(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){
	struct timeval start;
	struct timeval end;

    gettimeofday(&start,NULL);

    __m128 t0, t1;
    __m128 res0, res1, res2, res3;
    for(int i=0;i<M;i += 4){
    	for(int j=0;j<N;j += 4){
            res0 = _mm_setzero_ps();
            res1 = _mm_setzero_ps();
            res2 = _mm_setzero_ps();
            res3 = _mm_setzero_ps();
    		for(int k=0; k<K; k++){
                t1 = _mm_load_ps(&rhs[k*N+j]);

                t0 = _mm_load_ps1(&lhs[i*K+k]);
                res0 = _mm_fmadd_ps(t0, t1, res0);

                t0 = _mm_load_ps1(&lhs[(i+1)*K+k]);
                res1 = _mm_fmadd_ps(t0, t1, res1);

                t0 = _mm_load_ps1(&lhs[(i+2)*K+k]);
                res2 = _mm_fmadd_ps(t0, t1, res2);

                t0 = _mm_load_ps1(&lhs[(i+3)*K+k]);
                res3 = _mm_fmadd_ps(t0, t1, res3);
    		}
            _mm_store_ps(&res[i*N+j], res0);
            _mm_store_ps(&res[(i+1)*N+j], res1);
            _mm_store_ps(&res[(i+2)*N+j], res2);
            _mm_store_ps(&res[(i+3)*N+j], res3);
    	}
    }

    gettimeofday(&end,NULL);

    cout<<"optimization3 Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}

	return;
}
