#ifndef OPTIMIZATION_H_
#define OPTIMIZATION_H_

#include <memory>

void optimization1(std::shared_ptr<float[]> lhs, std::shared_ptr<float[]> rhs, std::shared_ptr<float[]> res, bool verbose=false);

#endif