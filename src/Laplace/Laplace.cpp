#include "Laplace.hpp"
#include "EigenPardiso.hpp"
#include "GaussianQuadrature.hpp"
#include "VTKCellType.hpp"
#include "ShapeFunction.hpp"

void Laplace::Solve() noexcept {
  std::vector<Eigen::Triplet<double>> LHS;
  auto RHS = Eigen::VectorXd::Zero(geo.NumOfNodes);

  {
    tbb::concurrent_vector<Eigen::Triplet<double>> LHS_;
    #pragma omp parallel for
    for (int ic = 0; ic < geo.NumOfElems; ic++) {
      CalcStiffnessMatrix(ic, LHS_);
    }
    LHS.assign(LHS_.begin(),LHS_.end());
  }

  Eigen_Pardiso EP(geo.NumOfNodes);
  EP.SetValues(LHS, RHS);
  EP.SetDirichletBC(geo.ibp, geo.bp);
  Solution = EP.GetOutput();
}

void Laplace::CalcStiffnessMatrix(int ic, tbb::concurrent_vector<Eigen::Triplet<double>> &LHS) noexcept {
  GaussianQuadrature GQ(2);
  for (int i1 = 0; i1 < GQ.node.rows(); i1++) {
    for (int i2 = 0; i2 < GQ.node.rows(); i2++) {
      for (int i3 = 0; i3 < GQ.node.rows(); i3++) {
        // 複数要素混合の場合書き換えが必要
        Eigen::MatrixXd X(geo.element.cols(), 3);
        for (int i = 0; i < X.rows(); i++) {
          X(i, 0) = geo.X(geo.element(ic, i), 0);
          X(i, 1) = geo.X(geo.element(ic, i), 1);
          X(i, 2) = geo.X(geo.element(ic, i), 2);
        }

        Eigen::MatrixXd dNdr;
        Eigen::VectorXd N;
        if(geo.type(ic) == VTK_CellType::HEXAHEDRON) {
          dNdr = ShapeFunction::C3D8::dNdr(GQ.node(i1), GQ.node(i2), GQ.node(i3));
          N = ShapeFunction::C3D8::N(GQ.node(i1), GQ.node(i2), GQ.node(i3));
        }
        else {
          std::cout << "undefined mesh type!\n";
          exit(EXIT_FAILURE);
        }

        Eigen::MatrixXd dXdr = X.transpose() * dNdr;

        for (int i = 0; i < X.rows(); i++) {
          for (int j = 0; j < X.rows(); j++) {
            int idx1 = geo.element(ic, i), idx2 = geo.element(ic, j);
            
            double val = 0.0;
            for (int k = 0; k < 3; k++) {
              val += dNdr(i, k) * dNdr(j, k);
            }
            val *= GQ.weight(i1) * GQ.weight(i2) * GQ.weight(i3) * dXdr.determinant();

            LHS.push_back({idx1, idx2, val});
          }
        }

      } // i3
    } // i2
  } // i1
}