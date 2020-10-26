#include <iostream>
#include <sys/time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <fmaintrin.h>
#include "optimization7.h"
#include "helper.h"
#include "omp.h"

using namespace std;

void optimization7(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){
	struct timeval start;
	struct timeval end;

    //reorder memory layout of rhs to 2 rows together
    shared_ptr<float[]> rhs_new(new float[K*N]);
    for(int i=0;i<K;i+=2){
		for(int j=0;j<2*N;j++){
		    if(j%2 == 0){
               *(rhs_new.get()+i*N+j) = *(rhs.get()+i*N+j/2);
		    }else{
               *(rhs_new.get()+i*N+j) = *(rhs.get()+(i+1)*N+j/2);
		    }
		}
	}

    gettimeofday(&start, NULL);

    __m128 tmp;
    __m512 t0, t1, t2;
    __m512bh t0b, t1b;
    __m512 res0[8];

    #pragma omp parallel for num_threads(4) private(tmp) private(t0) private(t1) private(t2) private(t0b) private(t1b) private(res0)
    for(int i=0;i<M;i+=8){
        //这里i+8的8，表示这个loop一次算输出矩阵的8行，和这里我们用了res0[8] 的8个寄存器对应
    	for(int j=0;j<N;j+=16){
            //这里j+16的16，向量化一次计算16个单精度浮点数输出

            res0[0] = _mm512_setzero_ps();
            res0[1] = _mm512_setzero_ps();
            res0[2] = _mm512_setzero_ps();
            res0[3] = _mm512_setzero_ps();
            res0[4] = _mm512_setzero_ps();
            res0[5] = _mm512_setzero_ps();
            res0[6] = _mm512_setzero_ps();
            res0[7] = _mm512_setzero_ps();

    		for(int k=0; k<K; k+=2){
    		    //reduce axis once add 2 to use the bf16
                t1 = _mm512_loadu_ps(&rhs_new[k*N+j*2]);
                t2 = _mm512_loadu_ps(&rhs_new[k*N+j*2+16]);
                t1b = _mm512_cvtne2ps_pbh(t2, t1);

                tmp = _mm_loadu_ps(&lhs[i*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[0] = _mm512_dpbf16_ps(res0[0], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+1)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[1] = _mm512_dpbf16_ps(res0[1], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+2)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[2] = _mm512_dpbf16_ps(res0[2], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+3)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[3] = _mm512_dpbf16_ps(res0[3], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+4)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[4] = _mm512_dpbf16_ps(res0[4], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+5)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[5] = _mm512_dpbf16_ps(res0[5], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+6)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[6] = _mm512_dpbf16_ps(res0[6], t0b, t1b);

                tmp = _mm_loadu_ps(&lhs[(i+7)*K+k]);
                t0 = _mm512_broadcast_f32x2(tmp);
                t0b = _mm512_cvtne2ps_pbh(t0, t0);
                res0[7] = _mm512_dpbf16_ps(res0[7], t0b, t1b);

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

    gettimeofday(&end, NULL);

    cout<<"optimization7 Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}

	return;
}
