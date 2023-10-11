#include "Model.h"

#include <fstream>

void s21::Model::ReadImg(const std::string &img_name) {
  std::ifstream file(img_name);
  if (!file.is_open()) throw std::invalid_argument("Choose file");
  BMP img;
  img.ReadFromFile(img_name.c_str());
  int width = img.TellWidth();
  int height = img.TellHeight();
  std::vector<std::vector<EasyBMP::RGBApixel>> help_matrix(
      height, std::vector<EasyBMP::RGBApixel>(width));

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

QImage s21::Model::WriteImg() {
  if (img_matrix_.empty()) throw std::runtime_error("ERROR");
  BMP output_img;
  output_img.SetSize(img_matrix_[0].size(), img_matrix_.size());
  for (int i = 0; i < img_matrix_.size(); i++)
    for (int j = 0; j < img_matrix_[0].size(); j++)
      output_img.SetPixel(j, i, filtered_matrix_[i][j]);

  return CreateQimage(output_img);
}

void s21::Model::ChannelSelection(int red, int green, int blue) {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &pixel = filtered_matrix_[i][j];
      pixel.Red = red;
      pixel.Green = green;
      pixel.Blue = blue;
    }
  }
}

// Simple Filtrs

void s21::Model::AverageConversion() {
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

void s21::Model::ConversionByBrightness() {
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

void s21::Model::ConversionByDesaturation() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto img_px = img_matrix_[i][j];
      double blue = img_px.Blue;
      double red = img_px.Red;
      double green = img_px.Green;

      filtered_matrix_[i][j].Red = (std::fmin(red, std::fmin(blue, green)) +
                                    std::fmax(red, std::fmax(blue, green))) /
                                   2;
    }
  }
}

void s21::Model::Negative() {
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

void MatrixTransformation(
    const std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix_,
    std::vector<std::vector<EasyBMP::RGBApixel>> &filtered_matrix_,
    const std::vector<std::vector<double>> &kernel) {
  int row_right_limit{};
  int column_right_limit{};
  kernel.size() == 2 ? row_right_limit = 0 : row_right_limit = 1;
  kernel[0].size() == 2 ? column_right_limit = 0 : column_right_limit = 1;
  for (int i = 1; i < img_matrix_.size() - 1; i++) {
    for (int j = 1; j < img_matrix_[i].size() - 1; j++) {
      double red = 0, green = 0, blue = 0;
      for (int k = -1; k <= row_right_limit; k++) {
        for (int l = -1; l <= column_right_limit; l++) {
          auto &img_px = img_matrix_[i + k][j + l];
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

void s21::Model::Convolution(const std::string &convolution_name) {
  if (kernel_map_.find(convolution_name) == kernel_map_.end() ||
      img_matrix_.empty())
    return;
  std::vector<std::vector<double>> kernel =
      (*kernel_map_.find(convolution_name)).second;
  MatrixTransformation(img_matrix_, filtered_matrix_, kernel);
}

void s21::Model::SobelFilterCombin() {
  if (img_matrix_.empty()) return;
  using pixel_mat = std::vector<std::vector<EasyBMP::RGBApixel>>;
  using double_mat = std::vector<std::vector<double>>;
  pixel_mat sobel_filter_left(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));
  pixel_mat sobel_filter_right(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));

  double_mat left_kernel = (*kernel_map_.find("Sobel filter left")).second;
  double_mat right_kernel = (*kernel_map_.find("Sobel filter right")).second;

  MatrixTransformation(img_matrix_, sobel_filter_left, left_kernel);
  MatrixTransformation(img_matrix_, sobel_filter_right, right_kernel);

  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      auto &filter_px = filtered_matrix_[i][j];
      auto &sob_right_px = sobel_filter_right[i][j];
      auto &sob_left_px = sobel_filter_left[i][j];
      filter_px.Red = sob_left_px.Red + sob_left_px.Red;
      filter_px.Green = sob_left_px.Green + sob_left_px.Green;
      filter_px.Blue = sob_left_px.Blue + sob_left_px.Blue;
    }
  }
}

void s21::Model::ArbitraryMatrixMode(
    const std::vector<std::vector<double>> &matrix) {
  if (!img_matrix_.empty())
    MatrixTransformation(img_matrix_, filtered_matrix_, matrix);
}

QImage s21::Model::CreateQimage(BMP bmp_image) {
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

void s21::Model::Restart() { filtered_matrix_ = img_matrix_; }
