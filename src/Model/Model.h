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
  void ReadImg();

 private:
  std::vector<std::vector<EasyBMP::RGBApixel>> img_matrix_;
  const std::map<std::string, std::vector<std::vector<int>>> kernel_map_{
      {"original_image", {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}},
      {"embos", {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}}},
      {"sharpen", {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}},
      {"box_blur", {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}},       // ????
      {"gaussian_blur", {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}},  // ????
      {"laplacian_filter", {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}},
      {"sobel_filter_left", {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}}},
      {"sobel_filter_right", {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}}};
};
}  // namespace s21