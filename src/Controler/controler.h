#ifndef CONTROLER_H_
#define CONTROLER_H_

#include <memory>

#include "../Model/model.h"

namespace s21 {
class Controler {
 public:
  Controler(s21::Model *model) : model_{model} {};
  void ReadImg(const std::string &img_name);
  void WriteImg(const std::string &img_name);
  void ChannelSelection(char RGB);
  void AverageConversion();
  void ConversionByBrightness();
  void ConversionByDesaturation();  // ????
  void Negative();
  void Convolution(const std::string &convolution_name);
  void SobelFilterCombin();

 private:
  std::unique_ptr<s21::Model> model_;
};
}  // namespace s21

#endif  //  CONTROLER_H_