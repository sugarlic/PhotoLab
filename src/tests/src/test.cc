#include <chrono>

#include "Controler/Controler.h"
#include "Model/Model.h"

using namespace std::chrono;

int main() {
  auto t0 = high_resolution_clock::now();
  s21::Model *model = new s21::Model;
  s21::Controler c{model};
  try {
    c.ReadImg("../Images/Lena.bmp");
    // c.Convolution("sobel_filter_right");
    c.SobelFilterCombin();
    c.WriteImg("./output.bmp");
  } catch (...) {
    std::cout << "Не удалось открыть файл\n";
  }

  auto t1 = high_resolution_clock::now();
  std::cout << "Time: " << duration_cast<milliseconds>(t1 - t0).count()
            << "msec\n";

  return 0;
}