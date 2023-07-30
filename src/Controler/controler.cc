#include "Controler.h"

void s21::Controler::ReadImg(const std::string &img_name) {
  model_->ReadImg(img_name);
}

void s21::Controler::WriteImg(const std::string &img_name) {
  model_->WriteImg(img_name);
}

void s21::Controler::ChannelSelection(char RGB) {
  // model_->ChannelSelection(RGB);
}

void s21::Controler::AverageConversion() { model_->AverageConversion(); }

void s21::Controler::ConversionByBrightness() {
  model_->ConversionByBrightness();
}

void s21::Controler::ConversionByDesaturation() {
  model_->ConversionByDesaturation();
}

void s21::Controler::Negative() { model_->Negative(); }

void s21::Controler::Convolution(const std::string &convolution_name) {
  model_->Convolution(convolution_name);
}

void s21::Controler::SobelFilterCombin() { model_->SobelFilterCombin(); }
