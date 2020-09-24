#ifndef BASELINE_H_
#define BASELINE_H_

#include <memory>

void baseline(std::shared_ptr<float[]> lhs, std::shared_ptr<float[]> rhs, std::shared_ptr<float[]> res, bool verbose=false);

#endif