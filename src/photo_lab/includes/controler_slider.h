#ifndef CONTROLER_SLIDER_H
#define CONTROLER_SLIDER_H
#include <QSlider>
#include <array>

#include "controler_commands.h"
namespace s21 {

class ControlerSlider : public QSlider {
  Q_OBJECT
 public:
  ControlerSlider(std::unique_ptr<CommandWithValueBase<float>> command,
                  float delimeter = 100, QWidget* parent = nullptr)
      : QSlider(parent), delimeter_(delimeter), command_(std::move(command)) {
    connect(this, &QSlider::valueChanged, this, &ControlerSlider::Execute);
  }
 signals:
  void Executed();
 public slots:
  void Execute(int value) {
    command_->Execute(value / delimeter_);
    emit Executed();
  }

 protected:
  float delimeter_{1};
  std::unique_ptr<CommandWithValueBase<float>> command_;
};
}  // namespace s21

#endif  // CONTROLER_SLIDER_H