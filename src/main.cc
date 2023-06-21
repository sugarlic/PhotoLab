#include <iostream>
#include <vector>

#include "../Libs/EasyBMP/EasyBMP.h"

void DiscolorationByBrightnessOfColors(
    std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix);
void Negativ(std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix);
void DecolorizationThroughAveraging(
    std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix);

int main() {
  BMP img;
  img.ReadFromFile("../Images/Lena.bmp");
  int width = img.TellWidth();
  int height = img.TellHeight();

  std::vector<std::vector<EasyBMP::RGBApixel>> img_matrix(
      height, std::vector<EasyBMP::RGBApixel>(width));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      img_matrix[i][j].Red = img.GetPixel(j, i).Red;
      img_matrix[i][j].Green = img.GetPixel(j, i).Green;
      img_matrix[i][j].Blue = img.GetPixel(j, i).Blue;
    }
  }

  // определить ядро свертки (фильтр)
  std::vector<std::vector<int>> kernel = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};

  // применить фильтр свертки
  std::vector<std::vector<EasyBMP::RGBApixel>> filtered_matrix(
      height, std::vector<EasyBMP::RGBApixel>(width));
  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      int red = 0, green = 0, blue = 0;
      for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
          red += img_matrix[i + k][j + l].Red * kernel[k + 1][l + 1];
          green += img_matrix[i + k][j + l].Green * kernel[k + 1][l + 1];
          blue += img_matrix[i + k][j + l].Blue * kernel[k + 1][l + 1];
        }
      }
      filtered_matrix[i][j].Red = std::min(255, std::max(0, red));
      filtered_matrix[i][j].Green = std::min(255, std::max(0, green));
      filtered_matrix[i][j].Blue = std::min(255, std::max(0, blue));
    }
  }

  BMP output_img;
  output_img.SetSize(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBApixel pixel;
      pixel.Red = filtered_matrix[i][j].Red;
      pixel.Green = filtered_matrix[i][j].Green;
      pixel.Blue = filtered_matrix[i][j].Blue;
      output_img.SetPixel(j, i, pixel);
    }
  }
  output_img.WriteToFile("output.bmp");

  //   // сохранить измененное изображение в файл
  //   for (int i = 0; i < height; i++) {
  //     for (int j = 0; j < width; j++) {
  //       img.SetPixel(j, i, img_matrix[i][j]);
  //     }
  //   }
  //   img.WriteToFile("output.bmp");

  return 0;
}

void DiscolorationByBrightnessOfColors(
    std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix) {
  for (size_t i = 0; i < img_matrix.size(); i++) {
    for (size_t j = 0; j < img_matrix[0].size(); j++) {
      img_matrix[i][j].Red = 0.299 * img_matrix[i][j].Red +
                             0.587 * img_matrix[i][j].Green +
                             0.114 * img_matrix[i][j].Blue;
      img_matrix[i][j].Green = 0.299 * img_matrix[i][j].Red +
                               0.587 * img_matrix[i][j].Green +
                               0.114 * img_matrix[i][j].Blue;
      img_matrix[i][j].Blue = 0.299 * img_matrix[i][j].Red +
                              0.587 * img_matrix[i][j].Green +
                              0.114 * img_matrix[i][j].Blue;
    }
  }
}

void Negativ(std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix) {
  for (size_t i = 0; i < img_matrix.size(); i++) {
    for (size_t j = 0; j < img_matrix[0].size(); j++) {
      img_matrix[i][j].Red = 255 - img_matrix[i][j].Red;
      img_matrix[i][j].Green = 255 - img_matrix[i][j].Green;
      img_matrix[i][j].Blue = 255 - img_matrix[i][j].Blue;
    }
  }
}

void DecolorizationThroughAveraging(
    std::vector<std::vector<EasyBMP::RGBApixel>> &img_matrix) {
  for (size_t i = 0; i < img_matrix.size(); i++) {
    for (size_t j = 0; j < img_matrix[0].size(); j++) {
      img_matrix[i][j].Red = img_matrix[i][j].Red / 3 +
                             img_matrix[i][j].Green / 3 +
                             img_matrix[i][j].Blue / 3;
      img_matrix[i][j].Green = img_matrix[i][j].Red / 3 +
                               img_matrix[i][j].Green / 3 +
                               img_matrix[i][j].Blue / 3;
      img_matrix[i][j].Blue = img_matrix[i][j].Red / 3 +
                              img_matrix[i][j].Green / 3 +
                              img_matrix[i][j].Blue / 3;
    }
  }
}
