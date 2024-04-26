#include "Laplace.hpp"
#include "EigenPardiso.hpp"
#include "GaussianQuadrature.hpp"
#include "VTKCellType.hpp"
#include "ShapeFunction.hpp"

void Laplace::Solve() noexcept {
  tbb::concurrent_vector<Eigen::Triplet<double>> LHS;
  Eigen::VectorXd RHS = Eigen::VectorXd::Zero(NumOfNodes);
  
  #pragma omp parallel for
  for (int ic = 0; ic < NumOfElems; ic++) {
    CalcStiffnessMatrix(ic, LHS);
    CalcRHS(ic,RHS);
  }

  Eigen_Pardiso EP(NumOfNodes);
  EP.SetValues(LHS, RHS);
  EP.SetDirichletBC(ibp, bp);
  Solution = EP.GetOutput();
}

void Laplace::CalcStiffnessMatrix(int ic, tbb::concurrent_vector<Eigen::Triplet<double>> &LHS) noexcept {
  GaussianQuadrature GQ(2);
  for (int i1 = 0; i1 < GQ.GetNumOfGaussianNodes(); i1++) {
    for (int i2 = 0; i2 < GQ.GetNumOfGaussianNodes(); i2++) {
      for (int i3 = 0; i3 < GQ.GetNumOfGaussianNodes(); i3++) {
        Eigen::MatrixXd x(element.row(ic).size(), 3);
        for (int i = 0; i < x.rows(); i++) {
          x(i, 0) = this->X(element(ic, i), 0);
          x(i, 1) = this->X(element(ic, i), 1);
          x(i, 2) = this->X(element(ic, i), 2);
        }

        Eigen::MatrixXd dNdr;
        Eigen::VectorXd N;
        if(type(ic) == VTK_CellType::HEXAHEDRON) {
          dNdr = ShapeFunction::C3D8::dNdr(GQ.GetNode(i1), GQ.GetNode(i2), GQ.GetNode(i3));
          N = ShapeFunction::C3D8::N(GQ.GetNode(i1), GQ.GetNode(i2), GQ.GetNode(i3));
        }
        else {
          std::cout << "undefined mesh type!\n";
          exit(EXIT_FAILURE);
        }

        Eigen::MatrixXd dxdr = x.transpose() * dNdr;

        for (int i = 0; i < x.rows(); i++) {
          for (int j = 0; j < x.rows(); j++) {
            int idx1 = element(ic, i), idx2 = element(ic, j);
            
            double val = 0.0;
            for (int k = 0; k < 3; k++) {
              val += dNdr(i, k) * dNdr(j, k);
            }
            val *= GQ.GetWeight(i1) * GQ.GetWeight(i2) * GQ.GetWeight(i3) * dxdr.determinant();

            LHS.push_back({idx1, idx2, val});
          }
        }

      } // i3
    } // i2
  } // i1
}

void Laplace::CalcRHS(int ic, Eigen::VectorXd &RHS) noexcept {
  GaussianQuadrature GQ(2);
  for (int i1 = 0; i1 < GQ.GetNumOfGaussianNodes(); i1++) {
    for (int i2 = 0; i2 < GQ.GetNumOfGaussianNodes(); i2++) {
      for (int i3 = 0; i3 < GQ.GetNumOfGaussianNodes(); i3++) {
        Eigen::MatrixXd x(element.row(ic).size(), 3);
        for (int i = 0; i < x.rows(); i++) {
          x(i, 0) = this->X(element(ic, i), 0);
          x(i, 1) = this->X(element(ic, i), 1);
          x(i, 2) = this->X(element(ic, i), 2);
        }

        Eigen::MatrixXd dNdr;
        Eigen::VectorXd N;
        if(type(ic) == VTK_CellType::HEXAHEDRON) {
          dNdr = ShapeFunction::C3D8::dNdr(GQ.GetNode(i1), GQ.GetNode(i2), GQ.GetNode(i3));
          N = ShapeFunction::C3D8::N(GQ.GetNode(i1), GQ.GetNode(i2), GQ.GetNode(i3));
        }
        else {
          std::cout << "undefined mesh type!\n";
          exit(EXIT_FAILURE);
        }

        Eigen::MatrixXd dxdr = x.transpose() * dNdr;

        Eigen::MatrixXd Me = N*N.transpose()*GQ.GetWeight(i1)*GQ.GetWeight(i2)*GQ.GetWeight(i3)*dxdr.determinant();
        Eigen::VectorXd fe(8);
        for(int i = 0; i < 8; i++) fe(i) = sin(2.0*M_PI*x(i,2)/3.0);
        Eigen::VectorXd Re = -Me*fe;

        for(int i = 0; i < x.rows(); i++) {
          int idx = element(ic,i);
          RHS(idx) += Re(i);
        }

        // for (int i = 0; i < x.rows(); i++) {
        //   for (int j = 0; j < x.rows(); j++) {
        //     int idx1 = element(ic, i), idx2 = element(ic, j);
            
        //     double val = N(i)*N(j)*sin(hoge);

        //     RHS()
        //   }
        // }
      }
    }
  }
}