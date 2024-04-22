#ifndef __SHAPE_FUNCTION_HPP__
#define __SHAPE_FUNCTION_HPP__

#include <Eigen/Core>

namespace ShapeFunction {
  namespace C3D8 {
    inline const Eigen::VectorXd N(double g1, double g2, double g3) noexcept {
      Eigen::VectorXd N(8);
      N(0) = (1e0 - g1) * (1e0 - g2) * (1e0 - g3) / 8.0;
      N(1) = (1e0 + g1) * (1e0 - g2) * (1e0 - g3) / 8.0;
      N(2) = (1e0 + g1) * (1e0 + g2) * (1e0 - g3) / 8.0;
      N(3) = (1e0 - g1) * (1e0 + g2) * (1e0 - g3) / 8.0;
      N(4) = (1e0 - g1) * (1e0 - g2) * (1e0 + g3) / 8.0;
      N(5) = (1e0 + g1) * (1e0 - g2) * (1e0 + g3) / 8.0;
      N(6) = (1e0 + g1) * (1e0 + g2) * (1e0 + g3) / 8.0;
      N(7) = (1e0 - g1) * (1e0 + g2) * (1e0 + g3) / 8.0;
      return N;
    }
    inline const Eigen::MatrixXd dNdr(double g1, double g2, double g3) noexcept {
      Eigen::MatrixXd dNdr(8, 3);
      dNdr(0, 0) = -(1e0 - g2) * (1e0 - g3) / 8.0;
      dNdr(0, 1) = -(1e0 - g1) * (1e0 - g3) / 8.0;
      dNdr(0, 2) = -(1e0 - g1) * (1e0 - g2) / 8.0;
      dNdr(1, 0) =  (1e0 - g2) * (1e0 - g3) / 8.0;
      dNdr(1, 1) = -(1e0 + g1) * (1e0 - g3) / 8.0;
      dNdr(1, 2) = -(1e0 + g1) * (1e0 - g2) / 8.0;
      dNdr(2, 0) =  (1e0 + g2) * (1e0 - g3) / 8.0;
      dNdr(2, 1) =  (1e0 + g1) * (1e0 - g3) / 8.0;
      dNdr(2, 2) = -(1e0 + g1) * (1e0 + g2) / 8.0;
      dNdr(3, 0) = -(1e0 + g2) * (1e0 - g3) / 8.0;
      dNdr(3, 1) =  (1e0 - g1) * (1e0 - g3) / 8.0;
      dNdr(3, 2) = -(1e0 - g1) * (1e0 + g2) / 8.0;
      dNdr(4, 0) = -(1e0 - g2) * (1e0 + g3) / 8.0;
      dNdr(4, 1) = -(1e0 - g1) * (1e0 + g3) / 8.0;
      dNdr(4, 2) =  (1e0 - g1) * (1e0 - g2) / 8.0;
      dNdr(5, 0) =  (1e0 - g2) * (1e0 + g3) / 8.0;
      dNdr(5, 1) = -(1e0 + g1) * (1e0 + g3) / 8.0;
      dNdr(5, 2) =  (1e0 + g1) * (1e0 - g2) / 8.0;
      dNdr(6, 0) =  (1e0 + g2) * (1e0 + g3) / 8.0;
      dNdr(6, 1) =  (1e0 + g1) * (1e0 + g3) / 8.0;
      dNdr(6, 2) =  (1e0 + g1) * (1e0 + g2) / 8.0;
      dNdr(7, 0) = -(1e0 + g2) * (1e0 + g3) / 8.0;
      dNdr(7, 1) =  (1e0 - g1) * (1e0 + g3) / 8.0;
      dNdr(7, 2) =  (1e0 - g1) * (1e0 + g2) / 8.0;
      return dNdr;
    }
  };
};

#endif