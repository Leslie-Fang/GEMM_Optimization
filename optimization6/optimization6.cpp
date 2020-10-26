#include <iostream>
#include <sys/time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <fmaintrin.h>
#include "optimization6.h"
#include "helper.h"
#include "omp.h"

using namespace std;

void optimization6(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){
	struct timeval start;
	struct timeval end;

    gettimeofday(&start,NULL);

    __m512 t0, t1;
    __m512 res0[8];

    #pragma omp parallel for num_threads(4) private(t0) private(t1) private(res0)
    for(int i=0;i<M;i+=8){
        //这里i+8的8，表示这个loop一次算输出矩阵的8行，和这里我们用了res0[8] 的8个寄存器对应
    	for(int j=0;j<N;j+=16){
            //这里j+16的16，表示的是512位寄存器除以32位单精度浮点=16，向量化一次16个单精度浮点数
            res0[0] = _mm512_setzero_ps();
            res0[1] = _mm512_setzero_ps();
            res0[2] = _mm512_setzero_ps();
            res0[3] = _mm512_setzero_ps();
            res0[4] = _mm512_setzero_ps();
            res0[5] = _mm512_setzero_ps();
            res0[6] = _mm512_setzero_ps();
            res0[7] = _mm512_setzero_ps();
    		for(int k=0; k<K; k++){
                t1 = _mm512_loadu_ps(&rhs[k*N+j]);

                t0 = _mm512_set1_ps(lhs[i*K+k]);
                res0[0] = _mm512_fmadd_ps(t0, t1, res0[0]);

                t0 = _mm512_set1_ps(lhs[(i+1)*K+k]);
                res0[1] = _mm512_fmadd_ps(t0, t1, res0[1]);

                t0 = _mm512_set1_ps(lhs[(i+2)*K+k]);
                res0[2] = _mm512_fmadd_ps(t0, t1, res0[2]);

                t0 = _mm512_set1_ps(lhs[(i+3)*K+k]);
                res0[3] = _mm512_fmadd_ps(t0, t1, res0[3]);

                t0 = _mm512_set1_ps(lhs[(i+4)*K+k]);
                res0[4] = _mm512_fmadd_ps(t0, t1, res0[4]);

                t0 = _mm512_set1_ps(lhs[(i+5)*K+k]);
                res0[5] = _mm512_fmadd_ps(t0, t1, res0[5]);

                t0 = _mm512_set1_ps(lhs[(i+6)*K+k]);
                res0[6] = _mm512_fmadd_ps(t0, t1, res0[6]);

                t0 = _mm512_set1_ps(lhs[(i+7)*K+k]);
                res0[7] = _mm512_fmadd_ps(t0, t1, res0[7]);
    		}
            _mm512_storeu_ps(&res[i*N+j], res0[0]);
            _mm512_storeu_ps(&res[(i+1)*N+j], res0[1]);
            _mm512_storeu_ps(&res[(i+2)*N+j], res0[2]);
            _mm512_storeu_ps(&res[(i+3)*N+j], res0[3]);
            _mm512_storeu_ps(&res[(i+4)*N+j], res0[4]);
            _mm512_storeu_ps(&res[(i+5)*N+j], res0[5]);
            _mm512_storeu_ps(&res[(i+6)*N+j], res0[6]);
            _mm512_storeu_ps(&res[(i+7)*N+j], res0[7]);
    	}
    }

    gettimeofday(&end,NULL);

    cout<<"optimization6 Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}

	return;
}
