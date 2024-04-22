#include "Geometry.hpp"
#include "VTKCellType.hpp"
#include <sstream>

// #include <vtkSmartPointer.h>
// #include <vtkUnstructuredGrid.h>
// #include <vtkHexahedron.h>
// #include <vtkTetra.h>
// #include <vtkPoints.h>
// #include <vtkPointData.h>
// #include <vtkCellData.h>
// #include <vtkFloatArray.h>
// #include <vtkXMLUnstructuredGridWriter.h>

void Geometry::ImportFromTP(const std::string path_to_tp) {
  TextParser tp;
  if(tp.read(path_to_tp) != TP_NO_ERROR) {
    std::cout << "TP file read error!\n";
    exit(EXIT_FAILURE);
  }

  std::string label, base;

  base = "/Computation";
  TP_GetValue(tp, base + "/OpenMP_NumOfThreads", OpenMP_NumOfThreads);
  TP_GetValue(tp, base + "/NumOfGaussianNodes", NumOfGaussianNodes);

  std::string NodeFile, ElemFile, TypeFile, ibpFile, bpFile;
  base = "/Files";
  TP_GetValue(tp, base + "/NodeFile", NodeFile);
  TP_GetValue(tp, base + "/ElemFile", ElemFile);
  TP_GetValue(tp, base + "/TypeFile", TypeFile);
  TP_GetValue(tp, base + "/ibpFile", ibpFile);
  TP_GetValue(tp, base + "/bpFile", bpFile);

  auto NumOfLines = [](const std::string path) -> int {
    InputFileReader IFR(path);
    int count = 0;
    std::string line;
    while(IFR.GetNextLine(line))
      count++;
    return count;
  };

  NumOfNodes = NumOfLines(NodeFile);
  SetNodeInfo(NodeFile, ibpFile, bpFile);

  NumOfElems = NumOfLines(ElemFile);
  SetElemInfo(ElemFile, TypeFile);
}

void Geometry::SetNodeInfo(const std::string NodeFile, const std::string ibpFile,  const std::string bpFile) {
  X.resize(NumOfNodes, 3);
  ibp.resize(NumOfNodes);
  bp.resize(NumOfNodes);

  InputFileReader IFR_node(NodeFile), IFR_ibp(ibpFile),   IFR_bp(bpFile);
  std::string rNode, ribp, rbp;

  for(int i = 0; i < NumOfNodes; i++) {
    IFR_node.GetNextLine(rNode);
    IFR_ibp.GetNextLine(ribp);
    IFR_bp.GetNextLine(rbp);

    ibp(i) = stoi(ribp);
    bp(i) = stod(rbp);

    std::stringstream ssNode(rNode);
    std::string dNode, dibd, dbd;
    for (int j = 0; j < 3; j++) {
      getline(ssNode, dNode, ' ');
      X(i,j) = stod(dNode);
    }
  }
}

void Geometry::SetElemInfo(const std::string ElemFile, const std::string typeFile) {
  type.resize(NumOfElems);
  InputFileReader IFR_type(typeFile);
  std::string stype, smat;
  for (int i = 0; i < NumOfElems; i++) {
    IFR_type.GetNextLine(stype);
    type(i) = stoi(stype);
  }

  // 複数要素混合の場合書き換えが必要
  if(type(0) == VTK_CellType::HEXAHEDRON) {
    element.resize(NumOfElems, 8);
  }
  else {
    "undefined mesh type!\n";
    exit(EXIT_FAILURE);
  }

  InputFileReader IFR_elm(ElemFile);
  std::string selm;
  for (int ic = 0; ic < NumOfElems; ic++)
  {
    IFR_elm.GetNextLine(selm);
    std::stringstream ss(selm);
    std::string elm;
    int j = 0;
    while (getline(ss, elm, ' '))
    {
      element(ic, j) = stoi(elm);
      j++;
    }
  }
}

void Geometry::TP_GetValue(TextParser &tp, const std::string label, int &val) {
  if (!tp.getInspectedValue(label, val))
  {
    std::cout << label << " is NOT set!\n";
    exit(EXIT_FAILURE);
  }
}
void Geometry::TP_GetValue(TextParser &tp, const std::string label, double &val) {
  if (!tp.getInspectedValue(label, val))
  {
    std::cout << label << " is NOT set!\n";
    exit(EXIT_FAILURE);
  }
}
void Geometry::TP_GetValue(TextParser &tp, const std::string label, std::string &val) {
  if (!tp.getInspectedValue(label, val))
  {
    std::cout << label << " is NOT set!\n";
    exit(EXIT_FAILURE);
  }
}
