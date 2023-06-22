#ifndef MODEL_H_
#define MODEL_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../Libs/EasyBMP/EasyBMP.h"

namespace s21 {
class Model {
 public:
  Model(){};
  ~Model(){};
  void ReadImg(const std::string &img_name);
  void WriteImg(const std::string &img_name);
  void ChannelSelection(char RGB);
  void AverageConversion();
  void ConversionByBrightness();
  void ConversionByDesaturation();  // ????
  void Negative();
  void Convolution(const std::string &convolution_name);

 private:
  std::vector<std::vector<EasyBMP::RGBApixel>> img_matrix_;
  std::vector<std::vector<EasyBMP::RGBApixel>> filtered_matrix_;
  const std::map<std::string, std::vector<std::vector<double>>> kernel_map_{
      {"original_image", {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}},
      {"embos", {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}}},
      {"sharpen", {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}},
      {"box_blur", {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}},  // ????
      {"gaussian_blur",
       {{1 / 2.5, 2 / 2.5, 1 / 2.5},
        {2 / 2.5, 4 / 2.5, 2 / 2.5},
        {1 / 2.5, 2 / 2.5, 1 / 2.5}}},  // ????
      {"laplacian_filter", {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}},
      {"sobel_filter_left", {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}}},
      {"sobel_filter_right", {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}}};
};
}  // namespace s21

#endif  //  MODEL_H_