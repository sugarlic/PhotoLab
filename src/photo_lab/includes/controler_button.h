#ifndef CONTROLER_BUTTON_H
#define CONTROLER_BUTTON_H
#include <QColor>
#include <QColorDialog>
#include <QPushButton>

#include "controler_commands.h"
namespace s21 {
class ContolerButton : public QPushButton {
  Q_OBJECT
 public:
  ContolerButton(std::unique_ptr<CommandBase> command, const QString& text,
                 QWidget* parent = nullptr)
      : QPushButton(text, parent), command_(std::move(command)) {
    if (!parent) return;
    connect(this, &ContolerButton::clicked, this, &ContolerButton::Execute);
  }
 signals:
  void Executed();
 public slots:
  virtual void Execute() {
    command_->Execute();
    emit Executed();
  }

 protected:
  std::unique_ptr<CommandBase> command_;
};
class ChannelSelectionButton : public ContolerButton {
  Q_OBJECT
 public:
  ChannelSelectionButton(std::unique_ptr<CommandChannelSelection> command,
                         std::shared_ptr<QColor> color_storage,
                         const QString& text, QWidget* parent = nullptr)
      : ContolerButton(std::move(command), text, parent),
        color_storage_(color_storage) {
    if (!parent) return;
    connect(this, &ChannelSelectionButton::clicked, this,
            &ChannelSelectionButton::Execute);
  }
 public slots:
  virtual void Execute() override {
    *color_storage_ =
        QColorDialog::getColor(*color_storage_, this, "Select color channel");
    command_->Execute();
    emit Executed();
  }

 private:
  std::shared_ptr<QColor> color_storage_;
};
}  // namespace s21

#endif  // CONTROLER_BUTTON_H