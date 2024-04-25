#ifndef __VTK_WRITER_HPP__
#define __VTK_WRITER_HPP__

#include "Laplace.hpp"
#include "VTKCellType.hpp"
#include <Eigen/Core>
#include <string>
#include <tuple>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkHexahedron.h>
#include <vtkTetra.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFloatArray.h>
#include <vtkXMLUnstructuredGridWriter.h>

using ResultEq = std::tuple<Eigen::MatrixXd, Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd>;

class VTKWriter {
  public:

    inline static void WriteResult(const std::string &filename, const Laplace &La) noexcept {
      auto grid = vtkSmartPointer<vtkUnstructuredGrid>::New();

      auto points = vtkSmartPointer<vtkPoints>::New();
      for (int i = 0; i < La.NumOfNodes; i++) points->InsertNextPoint(La.X(i, 0), La.X(i, 1), La.X(i, 2));
      grid->SetPoints(points);
    
      for (int ic = 0; ic < La.NumOfElems; ic++) {
        if (La.type(ic) == VTK_CellType::HEXAHEDRON) {
          auto cell = vtkSmartPointer<vtkHexahedron>::New();
          for (int i = 0; i < La.element.row(ic).size(); i++) cell->GetPointIds()->SetId(i, La.element(ic, i));
          grid->InsertNextCell(cell->GetCellType(), cell->GetPointIds());
        }
        else {
          std::cout << "undefined mesh type!\n";
          exit(EXIT_FAILURE);
        }
      }
    
      auto SetPointData1D_double = [&grid](const Eigen::VectorXd &data, const std::string name) -> void {
        auto array = vtkSmartPointer<vtkFloatArray>::New();
        array->SetName(name.c_str());
        array->SetNumberOfComponents(1);
        for (int i = 0; i < data.rows(); i++)
          array->InsertNextValue(data(i));
        grid->GetPointData()->AddArray(array);
      };
      SetPointData1D_double(La.GetOutput(), "solution");

      auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
      writer->SetFileName(filename.c_str());
      writer->SetDataModeToBinary();
      writer->SetInputData(grid);
      writer->Write();
    }
};

#endif