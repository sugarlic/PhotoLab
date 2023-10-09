#ifndef CONTROLER_COMMANDS_H
#define CONTROLER_COMMANDS_H
#include "QColor"
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
  virtual void Execute() {
    controler_->Negative();
    controler_->WriteImg("output.bmp");
  };
};
class CommandAverageConversion : public CommandBase {
 public:
  CommandAverageConversion(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    controler_->AverageConversion();
    controler_->WriteImg("output.bmp");
  };
};
class CommandConversionByBrightness : public CommandBase {
 public:
  CommandConversionByBrightness(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    controler_->ConversionByBrightness();
    controler_->WriteImg("output.bmp");
  };
};
class CommandConversionByDesaturation : public CommandBase {
 public:
  CommandConversionByDesaturation(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    controler_->ConversionByDesaturation();
    controler_->WriteImg("output.bmp");
  };
};
class CommandSobelFilterCombin : public CommandBase {
 public:
  CommandSobelFilterCombin(std::shared_ptr<Controler> controler)
      : CommandBase(controler) {}
  virtual void Execute() {
    controler_->SobelFilterCombin();
    controler_->WriteImg("output.bmp");
  };
};
class CommandConvolution : public CommandBase {
 public:
  CommandConvolution(std::shared_ptr<Controler> controler,
                     std::string convolution_name)
      : CommandBase(controler), convolution_name_(convolution_name) {}
  virtual void Execute() {
    controler_->Convolution(convolution_name_);
    controler_->WriteImg("output.bmp");
  };

 private:
  std::string convolution_name_;
};
class CommandChannelSelection : public CommandBase {
 public:
  CommandChannelSelection(std::shared_ptr<Controler> controler,
                          std::shared_ptr<QColor> color_storage)
      : CommandBase(controler), color_storage_(color_storage) {}
  virtual void Execute() {
    auto color = color_storage_ ? *color_storage_ : QColor();
    controler_->ChannelSelection(color.red(), color.green(), color.blue());
    controler_->WriteImg("output.bmp");
  };

 private:
  std::shared_ptr<QColor> color_storage_;
};
}  // namespace s21
#endif  // CONTROLER_COMMANDS_H