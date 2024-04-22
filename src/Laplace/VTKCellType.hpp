#ifndef __VTKCELLTYPES_HPP__
#define __VTKCELLTYPES_HPP__

namespace VTK_CellType {
  // Linear cells
  constexpr int EMPTY_CELL = 0;
  constexpr int VERTEX = 1;
  constexpr int POLY_VERTEX = 2;
  constexpr int LINE = 3;
  constexpr int POLY_LINE = 4;
  constexpr int TRIANGLE = 5;
  constexpr int TRIANGLE_STRIP = 6;
  constexpr int POLYGON = 7;
  constexpr int PIXEL = 8;
  constexpr int QUAD = 9;
  constexpr int TETRA = 10;
  constexpr int VOXEL = 11;
  constexpr int HEXAHEDRON = 12;
  constexpr int WEDGE = 13;
  constexpr int PYRAMID = 14;
  constexpr int PENTAGONAL_PRISM = 15;
  constexpr int HEXAGONAL_PRISM = 16;

  // Quadratic; isoparametric cells
  constexpr int QUADRATIC_EDGE = 21;
  constexpr int QUADRATIC_TRIANGLE = 22;
  constexpr int QUADRATIC_QUAD = 23;
  constexpr int QUADRATIC_POLYGON = 36;
  constexpr int QUADRATIC_TETRA = 24;
  constexpr int QUADRATIC_HEXAHEDRON = 25;
  constexpr int QUADRATIC_WEDGE = 26;
  constexpr int QUADRATIC_PYRAMID = 27;
  constexpr int BIQUADRATIC_QUAD = 28;
  constexpr int TRIQUADRATIC_HEXAHEDRON = 29;
  constexpr int QUADRATIC_LINEAR_QUAD = 30;
  constexpr int QUADRATIC_LINEAR_WEDGE = 31;
  constexpr int BIQUADRATIC_QUADRATIC_WEDGE = 32;
  constexpr int BIQUADRATIC_QUADRATIC_HEXAHEDRON = 33;
  constexpr int BIQUADRATIC_TRIANGLE = 34;

  // Cubic; isoparametric cell
  constexpr int CUBIC_LINE = 35;

  // Special class of cells formed by convex group of points
  constexpr int CONVEX_POINT_SET = 41;

  // Polyhedron cell (consisting of polygonal faces)
  constexpr int POLYHEDRON = 42;

  // Higher order cells in parametric form
  constexpr int PARAMETRIC_CURVE = 51;
  constexpr int PARAMETRIC_SURFACE = 52;
  constexpr int PARAMETRIC_TRI_SURFACE = 53;
  constexpr int PARAMETRIC_QUAD_SURFACE = 54;
  constexpr int PARAMETRIC_TETRA_REGION = 55;
  constexpr int PARAMETRIC_HEX_REGION = 56;

  // Higher order cells
  constexpr int HIGHER_ORDER_EDGE = 60;
  constexpr int HIGHER_ORDER_TRIANGLE = 61;
  constexpr int HIGHER_ORDER_QUAD = 62;
  constexpr int HIGHER_ORDER_POLYGON = 63;
  constexpr int HIGHER_ORDER_TETRAHEDRON = 64;
  constexpr int HIGHER_ORDER_WEDGE = 65;
  constexpr int HIGHER_ORDER_PYRAMID = 66;
  constexpr int HIGHER_ORDER_HEXAHEDRON = 67;

  // Arbitrary order Lagrange elements (formulated separated from generic higher order cells)
  constexpr int LAGRANGE_CURVE = 68;
  constexpr int LAGRANGE_TRIANGLE = 69;
  constexpr int LAGRANGE_QUADRILATERAL = 70;
  constexpr int LAGRANGE_TETRAHEDRON = 71;
  constexpr int LAGRANGE_HEXAHEDRON = 72;
  constexpr int LAGRANGE_WEDGE = 73;
  constexpr int LAGRANGE_PYRAMID = 74;
};

#endif