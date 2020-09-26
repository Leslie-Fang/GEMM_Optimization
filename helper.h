#ifndef HELPER_H_
#define HELPER_H_
#include <memory>

#define M 200
#define K 200
#define N 200

#define eps 1.0e-5

std::shared_ptr<float[]> matrix_lhs_generate_2D(bool RowMajor=true);
std::shared_ptr<float[]> matrix_rhs_generate_2D(bool RowMajor=true);
std::shared_ptr<float[]> rhs_memory_layout_reorder_to_ColMajor(std::shared_ptr<float[]> input);
std::shared_ptr<float[]> rhs_memory_layout_reorder_to_RowMajor(std::shared_ptr<float[]> input);

#endif