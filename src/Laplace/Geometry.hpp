#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include <Eigen/Core>
#include <TextParser.h>
#include <string>
#include <fstream>
#include <iostream>

class Geometry {
  public:
    int NumOfNodes, NumOfElems;
    Eigen::MatrixXd X; // reference coordination
    Eigen::MatrixXi element;
    Eigen::VectorXi type;
    Eigen::VectorXi ibp;
    Eigen::VectorXd bp;

    int OpenMP_NumOfThreads;
    int NumOfGaussianNodes;

    void ImportFromTP(const std::string path_to_tp);

  private:
    void SetNodeInfo(const std::string NodeFile, const std::string ibpFile,  const std::string bpFile);
    void SetElemInfo(const std::string ElemFile, const std::string typeFile);

    void TP_GetValue(TextParser &tp, const std::string label, int &val);
    void TP_GetValue(TextParser &tp, const std::string label, double &val);
    void TP_GetValue(TextParser &tp, const std::string label, std::string &val);

    class InputFileReader {
      public:
        InputFileReader(const std::string path)
        {
          if (!Open(path))
          {
            std::cout << "file open error!\n";
            exit(EXIT_FAILURE);
          }
        }
        ~InputFileReader()
        {
          ifs.close();
        }

        inline bool GetNextLine(std::string &str) noexcept
        {
          if (getline(ifs, str))
            return true;
          else
            return false;
        }

      private:
        std::ifstream ifs;
        inline bool Open(const std::string path) noexcept
        {
          ifs.open(path);
          if (ifs)
            return true;
          else
            return false;
        }
    };
};

#endif