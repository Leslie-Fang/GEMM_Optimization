#ifndef HELPER_H_
#define HELPER_H_
#include <memory>

#define M 1024
#define K 1024
#define N 1024

#define eps 1.0e-4

std::shared_ptr<float[]> matrix_lhs_generate_2D(bool RowMajor=true);
std::shared_ptr<float[]> matrix_rhs_generate_2D(bool RowMajor=true);
std::shared_ptr<float[]> rhs_memory_layout_reorder_to_ColMajor(std::shared_ptr<float[]> input);
std::shared_ptr<float[]> rhs_memory_layout_reorder_to_RowMajor(std::shared_ptr<float[]> input);

#endif