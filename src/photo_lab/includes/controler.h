#ifndef CONTROLER_H_
#define CONTROLER_H_

#include <memory>

#include "Model.h"

namespace s21 {
class Controler {
 public:
  Controler(std::shared_ptr<s21::Model> model) : model_{model} {};
  void ReadImg(const std::string &img_name);
  void WriteImg(const std::string &img_name);
  void ChannelSelection(int red, int green, int blue);
  void AverageConversion();
  void ConversionByBrightness();
  void ConversionByDesaturation();  // ????
  void Negative();
  void Convolution(const std::string &convolution_name);
  void SobelFilterCombin();
  void ArbitraryMatrixMode(const std::vector<std::vector<double>> &matrix);

 private:
  std::shared_ptr<s21::Model> model_;
};
}  // namespace s21

#endif  //  CONTROLER_H_