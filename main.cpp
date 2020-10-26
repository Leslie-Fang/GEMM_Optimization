#include <iostream>
#include "baseline.h"
#include "optimization1.h"
#include "optimization2.h"
#include "optimization3.h"
#include "optimization4.h"
#include "optimization5.h"
#include "optimization6.h"
#include "optimization7.h"
#include "optimization8.h"
#include "helper.h"
using namespace std;

int main(int argc, char ** argv){
	shared_ptr<float[]> lhs = matrix_lhs_generate_2D();
	shared_ptr<float[]> rhs = matrix_rhs_generate_2D();

	// shared_ptr<float[]> lhs(new float[4]{1,2,3,4});
	// shared_ptr<float[]> rhs(new float[4]{1,2,3,4});

    shared_ptr<float[]> res(new float[M*N]{0});
	baseline(lhs, rhs, res);

    shared_ptr<float[]> res1(new float[M*N]{0});
	optimization1(lhs, rhs, res1);

	shared_ptr<float[]> res2(new float[M*N]{0});
	optimization2(lhs, rhs, res2);

	shared_ptr<float[]> res3(new float[M*N]{0});
	optimization3(lhs, rhs, res3);

	shared_ptr<float[]> res4(new float[M*N]{0});
	optimization4(lhs, rhs, res4);

	shared_ptr<float[]> res5(new float[M*N]{0});
	optimization5(lhs, rhs, res5);

	shared_ptr<float[]> res6(new float[M*N]{0});
	optimization6(lhs, rhs, res6);

	shared_ptr<float[]> res7(new float[M*N]{0});
    optimization7(lhs, rhs, res7);

	shared_ptr<float[]> res8(new float[M*N]{0});
    optimization8(lhs, rhs, res8);

    bool profilling = false;
	if(profilling){
        for(int i=0;i<20;i++){
            optimization7(lhs, rhs, res7);
        }
	}

    shared_ptr<float[]> base = res7;
    shared_ptr<float[]> compare = res8;
	for(int i=0;i<M;i++){
	    for(int j=0;j<N;j++){
	    	if(base[i*N+j] - compare[i*N+j] > eps ){
	    		cout<<"Mismatch value: "<<base[i*N+j] - compare[i*N+j]<<endl;
	    	}
	    }
	}
	
	return 0;
}