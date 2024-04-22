#include "EigenPardiso.hpp"
#include <iostream>

// for fluid
void Eigen_Pardiso::SetDirichletBC(const Eigen::VectorXi &ibp, const Eigen::VectorXd &val) noexcept {
  for (int i = 0; i < ibp.rows(); i++) {
    if (ibp(i) == 1) continue;

    RHS(i) = val(i);
    for (int j = 0; j < this->LHS.cols(); j++) {
      LHS.coeffRef(i, j) = 0.0;
    }
    LHS.coeffRef(i, i) = 1.0;
  }

  LHS.prune(0.0);
}

const Eigen::VectorXd Eigen_Pardiso::GetOutput() const noexcept {
  Eigen::PardisoLU<Eigen::SparseMatrix<double>> PardisoLU;
  PardisoLU.compute(LHS);
  if(PardisoLU.info() != Eigen::Success) {
    std::cout << "error at LU factorization!\n";
    exit(EXIT_FAILURE);
  }
  auto ans = PardisoLU.solve(RHS);
  if(PardisoLU.info() != Eigen::Success) {
    std::cout << "error at solving linear system!\n";
    exit(EXIT_FAILURE);
  }
  return ans;
}