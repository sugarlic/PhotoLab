#include "controler.h"
namespace s21 {

void Controler::ReadImg(const std::string &img_name) {
  model_->ReadImg(img_name);
}

QImage Controler::WriteImg() { return model_->WriteImg(); }

void Controler::ChannelSelection(Model::ColorChannel channel) {
  model_->ChannelSelection(channel);
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

void Controler::BrightnessChange(float brightness) {
  model_->ChangeBrightness(brightness);
}

void Controler::ContrastChange(float contrast) {
  model_->ChangeContrast(contrast);
}

void Controler::SaturationChange(float shade, float lightness,
                                 float saturation) {
  model_->ChangeSaturation(shade, lightness, saturation);
}

void Controler::Restart() { model_->Restart(); }
void Controler::Toning() { model_->Toning(); }
}  // namespace s21
