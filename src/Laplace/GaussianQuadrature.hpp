#ifndef __GAUSSIAN_QUADRATURE_HPP__
#define __GAUSSIAN_QUADRATURE_HPP__

#include <Eigen/Core>
#include <iostream>

class GaussianQuadrature {
  public:
    GaussianQuadrature(int NumOfGaussianNodes) {
      this->NumOfGaussianNodes = NumOfGaussianNodes;
      node.resize(NumOfGaussianNodes);
      weight.resize(NumOfGaussianNodes);
      if(NumOfGaussianNodes == 1) {
        node(0) = 0.0;
        weight(0) = 2.0;
      }
      else if(NumOfGaussianNodes == 2) {
        node(0) = -1.0/sqrt(3.0);
        node(1) = 1.0/sqrt(3.0);
        weight(0) = 1.0;
        weight(1) = 1.0;
      }
      else {
        std::cout << "invalid number!\n";
        exit(EXIT_FAILURE);
      }
    }

    inline const double GetNode(int i) { return node(i); }
    inline const double GetWeight(int i) { return weight(i); }
    inline const int GetNumOfGaussianNodes() { return NumOfGaussianNodes; }

  private:
    int NumOfGaussianNodes;
    Eigen::VectorXd node, weight;
};

#endif