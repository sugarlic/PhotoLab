#ifndef CONTROLER_BUTTON_H
#define CONTROLER_BUTTON_H
#include <QColor>
#include <QColorDialog>
#include <QPushButton>

#include "controler_commands.h"
namespace s21 {
class ControlerButton {
 public:
  ControlerButton(std::unique_ptr<CommandBase> command)
      : command_(std::move(command)) {}

 protected:
  std::unique_ptr<CommandBase> command_;
};
class ControlerPushButton : public QPushButton, public ControlerButton {
  Q_OBJECT
 public:
  ControlerPushButton(std::unique_ptr<CommandBase> command, const QString& text,
                      QWidget* parent = nullptr)
      : QPushButton(text, parent), ControlerButton(std::move(command)) {
    QPushButton::connect(this, &QPushButton::clicked, this,
                         &ControlerPushButton::Execute);
  }
 signals:
  void Executed();
 public slots:
  virtual void Execute() {
    command_->Execute();
    emit Executed();
  }
};
class ChannelSelectionButton : public ControlerPushButton {
  Q_OBJECT
 public:
  ChannelSelectionButton(std::unique_ptr<CommandChannelSelection> command,
                         std::shared_ptr<Model::ColorChannel> channel,
                         const QString& text, QWidget* parent = nullptr)
      : ControlerPushButton(std::move(command), text, parent),
        channel_(channel) {
    if (!parent) return;
    QPushButton::connect(this, &ChannelSelectionButton::clicked, this,
                         &ChannelSelectionButton::Execute);
  }

 private:
  std::shared_ptr<Model::ColorChannel> channel_;
};
}  // namespace s21

#endif  // CONTROLER_BUTTON_H
