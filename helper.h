#ifndef HELPER_H_
#define HELPER_H_
#include <memory>

#define M 200
#define K 200
#define N 200

#define eps 1.0e-5

std::shared_ptr<float[]> matrix_generate_2D(bool RowMajor=true);

#endif