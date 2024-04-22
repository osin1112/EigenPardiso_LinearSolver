# EigenPardiso_LinearSolver

The C++ application for solving linear systems.
The method is based on Eigen/PardisoSupport (https://eigen.tuxfamily.org/dox/group__PardisoSupport__Module.html)

# Dependencies

1. CMake (https://cmake.org/)
2. Eigen (https://eigen.tuxfamily.org/index.php?title=Main_Page)
3. google-glog (https://code.google.com/archive/p/google-glog/)
4. intel oneAPI (https://www.intel.com/content/www/us/en/developer/tools/oneapi/overview.html#gs.86dnje)
5. TextParser (https://github.com/avr-aics-riken/TextParser)
6. Visualization Toolkit (VTK) (https://vtk.org/)

# Install & run the test problem

```
sh build.sh
cd example/test
sh run.sh
```