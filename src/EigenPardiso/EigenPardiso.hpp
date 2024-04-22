#ifndef __EIGEN_PARDISO_HPP__
#define __EIGEN_PARDISO_HPP__

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/PardisoSupport>
#include <vector>
#include <iostream>

class Eigen_Pardiso {
  public:
    Eigen_Pardiso(int dof) {
      this->dof = dof;
      LHS.resize(dof, dof);
    }

    inline void SetValues(std::vector<Eigen::Triplet<double>> &LHSvec, const Eigen::VectorXd &RHS) noexcept {
      this->LHS.setFromTriplets(LHSvec.begin(), LHSvec.end());
      this->RHS = RHS;
    }

    void SetDirichletBC(const Eigen::VectorXi &idx, const Eigen::VectorXd &val) noexcept;
    const Eigen::VectorXd GetOutput() const noexcept;

  private:
    int dof;
    Eigen::SparseMatrix<double> LHS;
    Eigen::VectorXd RHS;
};

#endif