#ifndef MODEL_H_
#define MODEL_H_

#include <qimage.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "EasyBMP.h"

namespace s21 {
class Model {
  using pixel_mat = std::vector<std::vector<EasyBMP::RGBApixel>>;
  using kernel_mat = std::vector<std::vector<double>>;

 public:
  Model(){};
  ~Model(){};
  enum ColorChannel { kNone, kRed, kGreen, kBlue };
  void ReadImg(const std::string& img_name);
  QImage WriteImg();
  void ChannelSelection(ColorChannel channel);
  void AverageConversion();
  void ConversionByBrightness();
  void ConversionByDesaturation();  // ????
  void Negative();
  void Convolution(const std::string& convolution_name);
  void SobelFilterCombin();
  void ArbitraryMatrixMode(const kernel_mat& matrix);
  void BrightnessChange(float brightness);
  void ContrastChange(float contrast);
  void SaturationChange(float shade, float lightness, float saturation);
  void Restart();
  std::string GetFilename() { return filename_; }

 private:
  void MatrixTransformation(const pixel_mat& img_matrix_,
                            pixel_mat& filtered_matrix_,
                            const kernel_mat& kernel);
  std::string filename_ = "";
  pixel_mat img_matrix_;
  pixel_mat filtered_matrix_;
  // pixel_mat interjacent_image_;
  const std::map<std::string, kernel_mat> kernel_map_{
      {"Original image", {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}},
      {"Embos", {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}}},
      {"Sharpen", {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}},
      {"Box blur",
       {{1 / 9.f, 1 / 9.f, 1 / 9.f},
        {1 / 9.f, 1 / 9.f, 1 / 9.f},
        {1 / 9.f, 1 / 9.f, 1 / 9.f}}},  // ????
      {"Gaussian blur",
       {{1 / 16.f, 2 / 16.f, 1 / 16.f},
        {2 / 16.f, 4 / 16.f, 2 / 16.f},
        {1 / 16.f, 2 / 16.f, 1 / 16.f}}},  // ????
      {"Laplacian filter", {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}},
      {"Sobel filter left", {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}}},
      {"Sobel filter right", {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}}};
  QImage CreateQimage(BMP image);
  void RGBtoHSL(float r, float g, float b, float& h, float& s, float& l);
  void HSLtoRGB(float h, float s, float l, float& r, float& g, float& b);
  float HueToRGB(float p, float q, float t);
};
}  // namespace s21

#endif  //  MODEL_H_
