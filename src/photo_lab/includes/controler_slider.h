#ifndef CONTROLER_SLIDER_H
#define CONTROLER_SLIDER_H
#include <QSlider>
#include <array>

#include "controler_commands.h"
namespace s21 {
template <size_t group_size = 1>
class ControlerSlider : public QSlider {
 public:
  ControlerSlider(
      std::unique_ptr<CommandWithValueBase<float[group_size]>> command,
      std::shared_ptr<std::array<float, group_size>> data, size_t index,
      QWidget* parent = nullptr)
      : QSlider(parent),
        command_(std::move(command)),
        data_(data),
        index_(index) {}
 signals:
  void Executed();
 public slots:
  void Execute() {
    if (!data_) return;
    command_->Execute(data_->data());
    emit Executed();
  }

 protected:
  std::shared_ptr<std::array<float, group_size>> data_;
  const size_t index_;
  std::unique_ptr<CommandWithValueBase<float[group_size]>> command_;
};
}  // namespace s21

#endif  // CONTROLER_SLIDER_H