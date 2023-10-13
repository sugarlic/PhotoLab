#include "controler.h"
namespace s21 {

void Controler::ReadImg(const std::string &img_name) {
  model_->ReadImg(img_name);
}

QImage Controler::WriteImg() { return model_->WriteImg(); }

void Controler::ChannelSelection(int red, int green, int blue) {
  model_->ChannelSelection(red, green, blue);
}

void Controler::AverageConversion() { model_->AverageConversion(); }

void Controler::ConversionByBrightness() { model_->ConversionByBrightness(); }

void Controler::ConversionByDesaturation() {
  model_->ConversionByDesaturation();
}

void Controler::Negative() { model_->Negative(); }

void Controler::Convolution(const std::string &convolution_name) {
  model_->Convolution(convolution_name);
}

void Controler::SobelFilterCombin() { model_->SobelFilterCombin(); }

void Controler::ArbitraryMatrixMode(
    const std::vector<std::vector<double>> &matrix) {
  model_->ArbitraryMatrixMode(matrix);
}

void s21::Controler::BrightnessChange(float brightness) {
  model_->BrightnessChange(brightness);
}

void s21::Controler::ContrastChange(float contrast) {
  model_->ContrastChange(contrast);
}

void s21::Controler::Restart() { model_->Restart(); }
}  // namespace s21
