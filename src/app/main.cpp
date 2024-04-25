#include "Geometry.hpp"
#include "Laplace.hpp"
#include "VTKWriter.hpp"

#include <glog/logging.h>

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  Laplace La(argv[1]);
  La.Solve();
  VTKWriter::WriteResult("test.vtu", La);
}
