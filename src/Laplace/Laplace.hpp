#ifndef __LAPLACE_HPP__
#define __LAPLACE_HPP__

#include "Geometry.hpp"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>
#include <string>
#include <omp.h>
#include <tbb/concurrent_vector.h>

class Laplace : public Geometry {
  public:
    Laplace(std::string path_to_tp) {
      ImportFromTP(path_to_tp);
      omp_set_num_threads(OpenMP_NumOfThreads);
    }

    inline const Eigen::VectorXd GetOutput() const noexcept { return Solution; };
    void Solve() noexcept;

  private:
    void CalcStiffnessMatrix(int ic, tbb::concurrent_vector<Eigen::Triplet<double>> &LHS) noexcept;
    void CalcRHS(int ic, Eigen::VectorXd &RHS) noexcept;

    Eigen::VectorXd Solution;
};

#endif