#include "Geometry.hpp"
#include "Laplace.hpp"
#include "VTKWriter.hpp"

#include <glog/logging.h>
#include <string>
#include <omp.h>

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  Geometry geo;
  geo.ImportFromTP(argv[1]);
  
  omp_set_num_threads(geo.OpenMP_NumOfThreads);

  Laplace L(geo);
  L.Solve();
  VTKWriter::WriteResult("test.vtu", geo, L.GetOutput());
}
