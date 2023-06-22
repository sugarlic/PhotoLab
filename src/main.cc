#include <chrono>

#include "Model/Model.h"

using namespace std::chrono;

int main() {
  auto t0 = high_resolution_clock::now();

  s21::Model model;
  try {
    model.ReadImg("../Images/Lena.bmp");
    model.Convolution("box_blur");
    model.WriteImg("output.bmp");
  } catch (...) {
    std::cout << "Не удалось открыть файл\n";
  }

  auto t1 = high_resolution_clock::now();
  std::cout << "Time: " << duration_cast<milliseconds>(t1 - t0).count()
            << "msec\n";

  return 0;
}