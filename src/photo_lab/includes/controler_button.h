#ifndef CONTROLER_BUTTON_H
#define CONTROLER_BUTTON_H
#include <QColor>
#include <QColorDialog>
#include <QPushButton>

#include "controler_commands.h"
namespace s21 {

class ControlerPushButton : public QPushButton, public ControlerCommandHolder {
  Q_OBJECT
 public:
  ControlerPushButton(std::unique_ptr<CommandBase> command, const QString& text,
                      QWidget* parent = nullptr)
      : QPushButton(text, parent), ControlerCommandHolder(std::move(command)) {
    QPushButton::connect(this, &QPushButton::clicked, this,
                         &ControlerPushButton::Execute);
  }
 signals:
  void Executed();
 public slots:
  void Execute() {
    command_->Execute();
    emit Executed();
  }
};
}  // namespace s21

#endif  // CONTROLER_BUTTON_H
