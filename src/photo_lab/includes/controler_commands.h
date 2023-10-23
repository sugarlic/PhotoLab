#ifndef CONTROLER_COMMANDS_H
#define CONTROLER_COMMANDS_H
#include "QColor"
#include "QDir"
#include "QFileDialog"
#include "controler.h"
namespace s21 {
class CommandBase {
 public:
  CommandBase(std::shared_ptr<Controler> controler) : controler_(controler) {}
  virtual void Execute() = 0;
  virtual ~CommandBase(){};

 protected:
  std::shared_ptr<Controler> controler_;
};
class ControlerCommandHolder {
 public:
  ControlerCommandHolder(std::unique_ptr<CommandBase> command)
      : command_(std::move(command)) {}

 protected:
  std::unique_ptr<CommandBase> command_;
};
template <typename T>
class CommandWithValueBase : public CommandBase {
 public:
  using CommandBase::CommandBase;
  using ValueType = T;
  virtual void Execute(ValueType value) = 0;

 protected:
  ValueType value_;
};
class CommandNegative : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->Negative(); };
};
class CommandAverageConversion : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->AverageConversion(); };
};
class CommandConversionByBrightness : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->ConversionByBrightness(); };
};
class CommandConversionByDesaturation : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->ConversionByDesaturation(); };
};
class CommandSobelFilterCombin : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->SobelFilterCombin(); };
};
class CommandRestart : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->Restart(); };
};
class CommandOpenBMP : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() {
    auto path = QFileDialog::getOpenFileName(nullptr, "Открыть BMP файл",
                                             QDir::current().absolutePath(),
                                             "BMP(*.bmp)");
    controler_->ReadImg(path.toStdString());
  };
};
class CommandSaveBMP : public CommandBase {
 public:
  using CommandBase::CommandBase;
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
class CommandBrightnessChange : public CommandWithValueBase<float> {
 public:
  using CommandWithValueBase::CommandBase;
  void Execute(ValueType value) override {
    controler_->BrightnessChange(value);
  }
};
class CommandContrastChange : public CommandWithValueBase<float> {
 public:
  using CommandWithValueBase::CommandBase;
  void Execute(ValueType value) override { controler_->ContrastChange(value); }
};
class CommandSaturationChange : public CommandWithValueBase<float[3]> {
 public:
  using CommandWithValueBase::CommandBase;
  void Execute(ValueType value) override {
    controler_->SaturationChange(value[0], value[1], value[2]);
  }
};
}  // namespace s21
#endif  // CONTROLER_COMMANDS_H
