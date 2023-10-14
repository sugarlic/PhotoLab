#ifndef CONTROLER_H_
#define CONTROLER_H_

#include <memory>

#include "Model.h"

namespace s21 {
class Controler {
 public:
  Controler(std::shared_ptr<s21::Model> model) : model_{model} {};
  void ReadImg(const std::string &img_name);
  QImage WriteImg();
  QImage GetSource() { return model_->GetSource(); }
  void ChannelSelection(Model::ColorChannel channel);
  void AverageConversion();
  void ConversionByBrightness();
  void ConversionByDesaturation();  // ????
  void Negative();
  void Convolution(const std::string &convolution_name);
  void SobelFilterCombin();
  void ArbitraryMatrixMode(const std::vector<std::vector<double>> &matrix);
  void BrightnessChange(float brightness);
  void ContrastChange(float contrast);
  void SaturationChange(float shade, float lightness, float saturation);
  void Restart();
  std::string GetFilename() { return model_->GetFilename(); }

 private:
  std::shared_ptr<s21::Model> model_;
};
}  // namespace s21

#endif  //  CONTROLER_H_
