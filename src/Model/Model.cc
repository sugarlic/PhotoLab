#include "Model.h"

void s21::Model::ReadImg(const std::string &img_name) {
  BMP img;
  img.ReadFromFile(img_name);
  int width = img.TellWidth();
  int height = img.TellHeight();

  std::vector<std::vector<EasyBMP::RGBApixel>> help_matrix(
      height, std::vector<EasyBMP::RGBApixel>(width));

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      help_matrix[i][j].Red = img.GetPixel(j, i).Red;
      help_matrix[i][j].Green = img.GetPixel(j, i).Green;
      help_matrix[i][j].Blue = img.GetPixel(j, i).Blue;
    }
  }
  img_matrix_ = std::move(help_matrix);
  filtered_matrix_ = img_matrix_;
}

void s21::Model::WriteImg(const std::string &img_name) {
  if (img_matrix_.empty()) return;
  BMP output_img;
  output_img.SetSize(img_matrix_[0].size(), img_matrix_.size());
  for (int i = 0; i < img_matrix_.size(); i++) {
    for (int j = 0; j < img_matrix_[0].size(); j++) {
      RGBApixel pixel;
      pixel.Red = filtered_matrix_[i][j].Red;
      pixel.Green = filtered_matrix_[i][j].Green;
      pixel.Blue = filtered_matrix_[i][j].Blue;
      output_img.SetPixel(j, i, pixel);
    }
  }
  output_img.WriteToFile(img_name);
}

// Simple Filtrs

void s21::Model::AverageConversion() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      filtered_matrix_[i][j].Red = img_matrix_[i][j].Red / 3 +
                                   img_matrix_[i][j].Green / 3 +
                                   img_matrix_[i][j].Blue / 3;
      filtered_matrix_[i][j].Green = img_matrix_[i][j].Red / 3 +
                                     img_matrix_[i][j].Green / 3 +
                                     img_matrix_[i][j].Blue / 3;
      filtered_matrix_[i][j].Blue = img_matrix_[i][j].Red / 3 +
                                    img_matrix_[i][j].Green / 3 +
                                    img_matrix_[i][j].Blue / 3;
    }
  }
  img_matrix_ = filtered_matrix_;
}

void s21::Model::ConversionByBrightness() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      filtered_matrix_[i][j].Red = 0.299 * img_matrix_[i][j].Red +
                                   0.587 * img_matrix_[i][j].Green +
                                   0.114 * img_matrix_[i][j].Blue;
      filtered_matrix_[i][j].Green = 0.299 * img_matrix_[i][j].Red +
                                     0.587 * img_matrix_[i][j].Green +
                                     0.114 * img_matrix_[i][j].Blue;
      filtered_matrix_[i][j].Blue = 0.299 * img_matrix_[i][j].Red +
                                    0.587 * img_matrix_[i][j].Green +
                                    0.114 * img_matrix_[i][j].Blue;
    }
  }
  img_matrix_ = filtered_matrix_;
}

void s21::Model::ConversionByDesaturation() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      double blue = img_matrix_[i][j].Blue;
      double red = img_matrix_[i][j].Red;
      double green = img_matrix_[i][j].Green;

      filtered_matrix_[i][j].Red = (std::fmin(red, std::fmin(blue, green)) +
                                    std::fmax(red, std::fmax(blue, green))) /
                                   2;
    }
  }
  img_matrix_ = filtered_matrix_;
}

void s21::Model::Negative() {
  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      filtered_matrix_[i][j].Red = 255 - img_matrix_[i][j].Red;
      filtered_matrix_[i][j].Green = 255 - img_matrix_[i][j].Green;
      filtered_matrix_[i][j].Blue = 255 - img_matrix_[i][j].Blue;
    }
  }
  img_matrix_ = filtered_matrix_;
}

// Convolution

void MatrixTransformation(
    const std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix_,
    std::vector<std::vector<EasyBMP::RGBApixel>> &filtered_matrix_,
    const std::vector<std::vector<double>> &kernel) {
  for (int i = 1; i < img_matrix_.size() - 1; i++) {
    for (int j = 1; j < img_matrix_[i].size() - 1; j++) {
      double red = 0, green = 0, blue = 0;
      for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
          red += img_matrix_[i + k][j + l].Red * kernel[k + 1][l + 1];
          green += img_matrix_[i + k][j + l].Green * kernel[k + 1][l + 1];
          blue += img_matrix_[i + k][j + l].Blue * kernel[k + 1][l + 1];
        }
      }
      filtered_matrix_[i][j].Red =
          static_cast<float>(std::fmin(255, std::fmax(0, red)));
      filtered_matrix_[i][j].Green =
          static_cast<float>(std::fmin(255, std::fmax(0, green)));
      filtered_matrix_[i][j].Blue =
          static_cast<float>(std::fmin(255, std::fmax(0, blue)));
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
  img_matrix_ = filtered_matrix_;
}

void s21::Model::SobelFilterCombin() {
  std::vector<std::vector<EasyBMP::RGBApixel>> sobel_filter_left(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));
  std::vector<std::vector<EasyBMP::RGBApixel>> sobel_filter_right(
      img_matrix_.size(),
      std::vector<EasyBMP::RGBApixel>(img_matrix_[0].size()));

  std::vector<std::vector<double>> left_kernel =
      (*kernel_map_.find("sobel_filter_left")).second;
  std::vector<std::vector<double>> right_kernel =
      (*kernel_map_.find("sobel_filter_right")).second;

  MatrixTransformation(img_matrix_, sobel_filter_left, left_kernel);
  MatrixTransformation(img_matrix_, sobel_filter_right, right_kernel);

  for (size_t i = 0; i < img_matrix_.size(); i++) {
    for (size_t j = 0; j < img_matrix_[0].size(); j++) {
      filtered_matrix_[i][j].Red =
          sobel_filter_left[i][j].Red + sobel_filter_right[i][j].Red;
      filtered_matrix_[i][j].Green =
          sobel_filter_left[i][j].Green + sobel_filter_right[i][j].Green;
      filtered_matrix_[i][j].Blue =
          sobel_filter_left[i][j].Blue + sobel_filter_right[i][j].Blue;
      ;
    }
  }
  img_matrix_ = filtered_matrix_;
}