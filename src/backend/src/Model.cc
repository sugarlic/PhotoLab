#include "Model.h"

#include <fstream>

namespace s21 {
void Model::ReadImg(const std::string &img_name) {
  std::ifstream file(img_name);
  if (!file.is_open()) return;
  filename_ = img_name;
  BMP img;
  img.ReadFromFile(img_name.c_str());
  int width = img.TellWidth();
  int height = img.TellHeight();
  pixel_mat help_matrix(height, std::vector<EasyBMP::RGBApixel>(width));

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      auto &pixel = help_matrix[i][j];
      pixel.Red = img.GetPixel(j, i).Red;
      pixel.Green = img.GetPixel(j, i).Green;
      pixel.Blue = img.GetPixel(j, i).Blue;
      pixel.Alpha = 255;
    }
  }
  img_matrix_ = std::move(help_matrix);
  filtered_matrix_ = img_matrix_;
}

QImage Model::WriteImg() {
  if (img_matrix_.empty()) return QImage();
  BMP output_img;
  output_img.SetSize(img_matrix_[0].size(), img_matrix_.size());
  for (size_t i = 0; i < img_matrix_.size(); i++)
    for (size_t j = 0; j < img_matrix_[0].size(); j++)
      output_img.SetPixel(j, i, filtered_matrix_[i][j]);

  return CreateQimage(output_img);
}
QImage Model::GetSource() { return QImage(filename_.c_str(), ".bmp"); };
void Model::ChannelSelection(ColorChannel channel) {
  if (channel == kNone) return;
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto &img_px = img_matrix_[i][j];
      auto value = channel == kRed     ? img_px.Red
                   : channel == kGreen ? img_px.Green
                                       : img_px.Blue;
      filter_px.Red = filter_px.Green = filter_px.Blue = value;
    }
  }
}

// Simple Filtrs

void Model::AverageConversion() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto img_px = img_matrix_[i][j];
      img_px.Red /= 3;
      img_px.Green /= 3;
      img_px.Blue /= 3;
      auto new_byte = img_px.Red + img_px.Green + img_px.Blue;
      filter_px.Red = filter_px.Green = filter_px.Blue = new_byte;
    }
  }
}

void Model::ConversionByBrightness() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto img_px = img_matrix_[i][j];
      img_px.Red *= 0.299;
      img_px.Green *= 0.587;
      img_px.Blue *= 0.114;
      auto new_byte = img_px.Red + img_px.Green + img_px.Blue;
      filter_px.Red = filter_px.Green = filter_px.Blue = new_byte;
    }
  }
}

void Model::ConversionByDesaturation() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &img_px = img_matrix_[i][j];
      auto &filter_px = filtered_matrix_[i][j];
      auto value = (std::min({img_px.Red, img_px.Blue, img_px.Green}) +
                    std::max({img_px.Red, img_px.Blue, img_px.Green})) /
                   2;
      filter_px.Red = filter_px.Green = filter_px.Blue = value;
    }
  }
}

void Model::Negative() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto &img_px = img_matrix_[i][j];
      filter_px.Red = 255 - img_px.Red;
      filter_px.Green = 255 - img_px.Green;
      filter_px.Blue = 255 - img_px.Blue;
    }
  }
}

// Convolution

void Model::MatrixTransformation(const pixel_mat &img_matrix_,
                                 pixel_mat &filtered_matrix_,
                                 const kernel_mat &kernel) {
  int row_right_limit = !(kernel.size() == 2);
  int column_right_limit = !(kernel[0].size() == 2);
  int img_rows = img_matrix_.size();

  for (int i = 0; i < img_rows; i++) {
    int img_cols = img_matrix_[i].size();

    for (int j = 0; j < img_cols; j++) {
      int red = 0, green = 0, blue = 0;
      for (int k = -1; k <= row_right_limit; k++) {
        for (int l = -1; l <= column_right_limit; l++) {
          int row = std::clamp<int>(i + k, 0, img_rows - 1);
          int col = std::clamp<int>(j + l, 0, img_cols - 1);
          auto img_px = img_matrix_[row][col];
          auto kernel_val = kernel[k + 1][l + 1];
          red += img_px.Red * kernel_val;
          green += img_px.Green * kernel_val;
          blue += img_px.Blue * kernel_val;
        }
      }
      auto &filter_px = filtered_matrix_[i][j];
      filter_px.Red = std::clamp<float>(red, 0, 255);
      filter_px.Green = std::clamp<float>(green, 0, 255);
      filter_px.Blue = std::clamp<float>(blue, 0, 255);
    }
  }
}

void Model::Convolution(const std::string &convolution_name) {
  if (kernel_map_.find(convolution_name) == kernel_map_.end() ||
      img_matrix_.empty())
    return;
  kernel_mat kernel = (*kernel_map_.find(convolution_name)).second;
  MatrixTransformation(img_matrix_, filtered_matrix_, kernel);
}

void Model::SobelFilterCombin() {
  if (img_matrix_.empty()) return;
  pixel_mat sobel_filter_left(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));
  pixel_mat sobel_filter_right(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));

  kernel_mat left_kernel = (*kernel_map_.find("Sobel filter left")).second;
  kernel_mat right_kernel = (*kernel_map_.find("Sobel filter right")).second;

  MatrixTransformation(img_matrix_, sobel_filter_left, left_kernel);
  MatrixTransformation(img_matrix_, sobel_filter_right, right_kernel);

  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto &sob_right_px = sobel_filter_right[i][j];
      auto &sob_left_px = sobel_filter_left[i][j];
      filter_px.Red = sob_left_px.Red + sob_right_px.Red;
      filter_px.Green = sob_left_px.Green + sob_right_px.Green;
      filter_px.Blue = sob_left_px.Blue + sob_right_px.Blue;
    }
  }
}

void Model::ArbitraryMatrixMode(const kernel_mat &matrix) {
  if (!img_matrix_.empty())
    MatrixTransformation(img_matrix_, filtered_matrix_, matrix);
}

QImage Model::CreateQimage(BMP bmp_image) {
  int width = bmp_image.TellWidth();
  int height = bmp_image.TellHeight();

  QImage qImage(width, height, QImage::Format_RGB32);

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      RGBApixel pixel = bmp_image.GetPixel(x, y);
      qImage.setPixel(x, y, qRgb(pixel.Red, pixel.Green, pixel.Blue));
    }
  }

  return qImage;
}

void Model::BrightnessChange(float brightness) {
  if (img_matrix_.empty()) return;
  filtered_matrix_ = img_matrix_;
  for (size_t i = 0; i < filtered_matrix_.size(); i++)
    for (size_t j = 0; j < filtered_matrix_[0].size(); j++) {
      auto &pixel = filtered_matrix_[i][j];
      pixel.Red = std::clamp<float>(pixel.Red * brightness, 0, 255);
      pixel.Blue = std::clamp<float>(pixel.Blue * brightness, 0, 255);
      pixel.Green = std::clamp<float>(pixel.Green * brightness, 0, 255);
    }
}

void Model::ContrastChange(float contrast) {
  if (img_matrix_.empty()) return;
  filtered_matrix_ = img_matrix_;
  for (size_t i = 0; i < filtered_matrix_.size(); i++)
    for (size_t j = 0; j < filtered_matrix_[0].size(); j++) {
      auto &pixel = filtered_matrix_[i][j];
      pixel.Red = std::clamp<float>((pixel.Red - 128) * contrast + 128, 0, 255);
      pixel.Blue =
          std::clamp<float>((pixel.Blue - 128) * contrast + 128, 0, 255);
      pixel.Green =
          std::clamp<float>((pixel.Green - 128) * contrast + 128, 0, 255);
    }
}

void Model::SaturationChange(float shade, float lightness, float saturation) {
  if (img_matrix_.empty()) return;
  filtered_matrix_ = img_matrix_;
  for (size_t i = 0; i < filtered_matrix_.size(); i++)
    for (size_t j = 0; j < filtered_matrix_[0].size(); j++) {
      auto &pixel = filtered_matrix_[i][j];
      float h, s, l;
      float r = pixel.Red / 255.f;
      float g = pixel.Green / 255.f;
      float b = pixel.Blue / 255.f;
      RGBtoHSL(r, g, b, h, s, l);

      h = std::clamp<float>(h * shade, 0, 360);
      s = std::clamp<float>(s * saturation, 0, 1);
      l = std::clamp<float>(l * lightness, 0, 1);

      HSLtoRGB(h, s, l, r, g, b);

      pixel.Red = std::clamp<float>(r * 255, 0, 255);
      pixel.Green = std::clamp<float>(g * 255, 0, 255);
      pixel.Blue = std::clamp<float>(b * 255, 0, 255);
    }
}

void Model::Restart() { filtered_matrix_ = img_matrix_; }

void Model::RGBtoHSL(float r, float g, float b, float &h, float &s, float &l) {
  const float &maxVal = std::max({r, g, b});
  const float &minVal = std::min({r, g, b});

  float delta = maxVal - minVal;

  if (delta == 0) {
    h = 0;
  } else if (&maxVal == &r) {
    h = 60 * std::fmod((g - b) / delta, 6);
  } else if (&maxVal == &g) {
    h = 60 * ((b - r) / delta + 2);
  } else if (&maxVal == &b) {
    h = 60 * ((r - g) / delta + 4);
  }

  l = (maxVal + minVal) / 2;

  if (delta == 0) {
    s = 0;
  } else {
    s = delta / (1 - std::abs(2 * l - 1));
  }
}

void Model::HSLtoRGB(float h, float s, float l, float &r, float &g, float &b) {
  if (s == 0) {
    r = g = b = l;
  } else {
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    float hk = h / 360;

    r = HueToRGB(p, q, hk + 1 / 3.0);
    g = HueToRGB(p, q, hk);
    b = HueToRGB(p, q, hk - 1 / 3.0);
  }
}

float Model::HueToRGB(float p, float q, float t) {
  if (t < 0) t += 1;
  if (t > 1) t -= 1;
  if (t < 1 / 6.0) return p + (q - p) * 6 * t;
  if (t < 1 / 2.0) return q;
  if (t < 2 / 3.0) return p + (q - p) * (2 / 3.0 - t) * 6;
  return p;
}
}  // namespace s21
