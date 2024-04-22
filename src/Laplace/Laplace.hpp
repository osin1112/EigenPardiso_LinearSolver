#ifndef __LAPLACE_HPP__
#define __LAPLACE_HPP__

#include "Geometry.hpp"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>
#include <tbb/concurrent_vector.h>

class Laplace {
  public:
    Laplace(Geometry &geo) {
      this->geo = geo;
    }

    inline const Eigen::VectorXd GetOutput() const noexcept { return Solution; };
    void Solve() noexcept;

  private:
    void CalcStiffnessMatrix(int ic, tbb::concurrent_vector<Eigen::Triplet<double>> &LHS) noexcept;
    // void CalcRHS(int ic) noexcept;

    Geometry geo;
    Eigen::VectorXd Solution;
};

#endif