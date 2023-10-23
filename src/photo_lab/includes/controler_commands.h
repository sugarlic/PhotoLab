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
  void Execute() override{};
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
class CommandToning : public CommandBase {
 public:
  using CommandBase::CommandBase;
  virtual void Execute() { controler_->Toning(); };
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
class CommandChangeBrightness : public CommandWithValueBase<float> {
 public:
  CommandChangeBrightness(std::shared_ptr<Controler> controler)
      : CommandWithValueBase(controler){};
  void Execute(ValueType value) override {
    controler_->ChangeBrightness(value);
  }
};
class CommandChangeContrast : public CommandWithValueBase<float> {
 public:
  CommandChangeContrast(std::shared_ptr<Controler> controler)
      : CommandWithValueBase(controler){};
  void Execute(ValueType value) override {
    controler_->ChangeContrast(value_ = value);
  }
};
class CommandSetShade : public CommandWithValueBase<float> {
 public:
  CommandSetShade(std::shared_ptr<Controler> controler)
      : CommandWithValueBase(controler){};
  void Execute(ValueType value) override {
    controler_->SetShade(value_ = value);
    controler_->ChangeSaturation();
  }
};
class CommandSetLightness : public CommandWithValueBase<float> {
 public:
  CommandSetLightness(std::shared_ptr<Controler> controler)
      : CommandWithValueBase(controler){};
  void Execute(ValueType value) override {
    controler_->SetLightness(value_ = value);
    controler_->ChangeSaturation();
  }
};
class CommandSetSaturation : public CommandWithValueBase<float> {
 public:
  CommandSetSaturation(std::shared_ptr<Controler> controler)
      : CommandWithValueBase(controler){};
  void Execute(ValueType value) override {
    controler_->SetSaturation(value_ = value);
    controler_->ChangeSaturation();
  }
};
}  // namespace s21
#endif  // CONTROLER_COMMANDS_H
