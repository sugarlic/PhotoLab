#ifndef CONTROLER_COMMANDS_H
#define CONTROLER_COMMANDS_H
#include "QColor"
#include "QDir"
#include "QFileDialog"
#include "controler.h"
namespace s21 {
class CommandBase {
 public:
  virtual void Execute() = 0;
  virtual ~CommandBase(){};

 protected:
  CommandBase(std::shared_ptr<Controler> controler) : controler_(controler) {}
  std::shared_ptr<Controler> controler_;
};
class CommandNegative : public CommandBase {
 public:
  CommandNegative(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->Negative(); };
};
class CommandAverageConversion : public CommandBase {
 public:
  CommandAverageConversion(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->AverageConversion(); };
};
class CommandConversionByBrightness : public CommandBase {
 public:
  CommandConversionByBrightness(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->ConversionByBrightness(); };
};
class CommandConversionByDesaturation : public CommandBase {
 public:
  CommandConversionByDesaturation(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->ConversionByDesaturation(); };
};
class CommandSobelFilterCombin : public CommandBase {
 public:
  CommandSobelFilterCombin(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->SobelFilterCombin(); };
};
class CommandRestart : public CommandBase {
 public:
  CommandRestart(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() { controler_->Restart(); };
};
class CommandOpenBMP : public CommandBase {
 public:
  CommandOpenBMP(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    auto path = QFileDialog::getOpenFileName(nullptr, "Открыть BMP файл",
                                             QDir::current().absolutePath(),
                                             "BMP(*.bmp)");
    controler_->ReadImg(path.toStdString());
  };
};
class CommandSaveBMP : public CommandBase {
 public:
  CommandSaveBMP(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    auto path = QFileDialog::getSaveFileName(nullptr, "Сохранить BMP файл", "",
                                             "BMP(*.bmp)");
    auto image = controler_->WriteImg();
    image.save(path);
  };
};
class CommandConvolution : public CommandBase {
 public:
  CommandConvolution(std::shared_ptr<Controler> controler,
                     std::string convolution_name)
      : CommandBase(controler), convolution_name_(convolution_name) {}
  virtual void Execute() { controler_->Convolution(convolution_name_); };

 private:
  std::string convolution_name_;
};
class CommandChannelSelection : public CommandBase {
 public:
  CommandChannelSelection(std::shared_ptr<Controler> controler,
                          std::shared_ptr<Model::ColorChannel> channel)
      : CommandBase(controler), channel_(channel) {}
  virtual void Execute() {
    auto channel = channel_ ? *channel_ : Model::kNone;
    controler_->ChannelSelection(channel);
  };

 private:
  std::shared_ptr<Model::ColorChannel> channel_;
};
}  // namespace s21
#endif  // CONTROLER_COMMANDS_H
