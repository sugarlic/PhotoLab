#ifndef CONTROLER_BUTTON_H
#define CONTROLER_BUTTON_H
#include <QPushButton>

#include "controler_commands.h"
namespace s21 {
class ContolerButton : public QPushButton {
 public:
  ContolerButton(std::unique_ptr<CommandBase> command, const QString& text,
                 QWidget* parent = nullptr)
      : QPushButton(text, parent), command_(std::move(command)) {
    if (!parent) return;
    connect(this, &ContolerButton::clicked, this, &ContolerButton::Execute);
  }
 public slots:
  void Execute() {
    qDebug() << "Click";
    command_->Execute();
  }

 protected:
  std::unique_ptr<CommandBase> command_;
};
}  // namespace s21

#endif  // CONTROLER_BUTTON_H