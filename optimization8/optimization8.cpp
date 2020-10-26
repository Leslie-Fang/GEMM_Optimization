#include <iostream>
#include <sys/time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <fmaintrin.h>
#include "optimization8.h"
#include "helper.h"
#include "omp.h"

using namespace std;

void optimization8(shared_ptr<float[]> lhs, shared_ptr<float[]> rhs, shared_ptr<float[]> res, bool verbose){
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

	//pre_transfer rhs to bf16
	shared_ptr<short[]> rhs_new2(new short[K*N]);
	__m512 temp0, temp1;
	__m512bh temp0_bf16;
	for(int i=0;i<K;i++){
		for(int j=0;j<N;j+=32){
            temp0 = _mm512_loadu_ps(&rhs_new[i*N+j]);
            temp1 = _mm512_loadu_ps(&rhs_new[i*N+j+16]);
            temp0_bf16 = _mm512_cvtne2ps_pbh(temp1, temp0);
            _mm512_storeu_ps(&rhs_new2[i*N+j], __m512(temp0_bf16));
		}
	}

    gettimeofday(&start, NULL);

	//pre_transfer lhs to bf16
	shared_ptr<short[]> lhs_new(new short[M*K]);
	for(int i=0;i<M;i++){
		for(int j=0;j<K;j+=32){
            temp0 = _mm512_loadu_ps(&lhs[i*K+j]);
            temp1 = _mm512_loadu_ps(&lhs[i*K+j+16]);
            temp0_bf16 = _mm512_cvtne2ps_pbh(temp1, temp0);
            _mm512_storeu_ps(&lhs_new[i*K+j], __m512(temp0_bf16));
		}
	}

    __m512bh t0b, t1b;
    __m512 res0[8];

    #pragma omp parallel for num_threads(4) private(t0b) private(t1b) private(res0)
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
                t1b = __m512bh(_mm512_loadu_ps(&rhs_new2[k*N+j*2]));

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[i*K+k]))));
                res0[0] = _mm512_dpbf16_ps(res0[0], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+1)*K+k]))));
                res0[1] = _mm512_dpbf16_ps(res0[1], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+2)*K+k]))));
                res0[2] = _mm512_dpbf16_ps(res0[2], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+3)*K+k]))));
                res0[3] = _mm512_dpbf16_ps(res0[3], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+4)*K+k]))));
                res0[4] = _mm512_dpbf16_ps(res0[4], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+5)*K+k]))));
                res0[5] = _mm512_dpbf16_ps(res0[5], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+6)*K+k]))));
                res0[6] = _mm512_dpbf16_ps(res0[6], t0b, t1b);

                t0b = __m512bh(_mm512_set1_ps(*((float*)(&lhs_new[(i+7)*K+k]))));
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

    cout<<"optimization8 Running: "<< (end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) << "ms"<<endl;

	if(verbose){
		for(int i=0;i<M;i++){
	    	for(int j=0;j<N;j++){
	    		cout<<res[i*N+j]<<endl;
	    	}
	    }
	}

	return;
}
