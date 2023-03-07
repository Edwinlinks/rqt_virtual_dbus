//
// Created by yuchen on 2023/3/7.
//

#include "rqt_virtual_dbus/key_button.h"

KeyboardButton::KeyboardButton(QWidget *parent) : QRadioButton(parent) {
  resize(parent->width(), parent->height());
  this->setText("Use keyboard");

  has_libinput_ = HAS_LIBINPUT;

  focus_timer_ = new QTimer(this);
  connect(this, &QRadioButton::clicked, this, &KeyboardButton::updateState);
  connect(this->focus_timer_, &QTimer::timeout, this,
          &KeyboardButton::focusButton);
}

KeyboardButton::~KeyboardButton() {}

void KeyboardButton::updateState() {
  read_keyboard_ = this->isChecked();
  if (read_keyboard_)
    focus_timer_->start(20);
  else
    focus_timer_->stop();
}

void KeyboardButton::focusButton() {
  if (read_keyboard_)
    this->setFocus();
  else
    focus_timer_->stop();
}

void KeyboardButton::resizeEvent(QResizeEvent *event) {
  resize(this->parentWidget()->width(), this->parentWidget()->height());
}

void KeyboardButton::keyPressEvent(QKeyEvent *ev) {
  switch (ev->key()) {
  case Qt::Key_W:
    dbus_data_->key_w = true;
    break;
  case Qt::Key_S:
    dbus_data_->key_s = true;
    break;
  case Qt::Key_A:
    dbus_data_->key_a = true;
    break;
  case Qt::Key_D:
    dbus_data_->key_d = true;
    break;
  case Qt::Key_Shift:
    dbus_data_->key_shift = true;
    break;
  case Qt::Key_Control:
    dbus_data_->key_ctrl = true;
    break;
  case Qt::Key_Q:
    dbus_data_->key_q = true;
    break;
  case Qt::Key_E:
    dbus_data_->key_e = true;
    break;
  case Qt::Key_R:
    dbus_data_->key_r = true;
    break;
  case Qt::Key_F:
    dbus_data_->key_f = true;
    break;
  case Qt::Key_G:
    dbus_data_->key_g = true;
    break;
  case Qt::Key_Z:
    dbus_data_->key_z = true;
    break;
  case Qt::Key_X:
    dbus_data_->key_x = true;
    break;
  case Qt::Key_C:
    dbus_data_->key_c = true;
    break;
  case Qt::Key_V:
    dbus_data_->key_v = true;
    break;
  case Qt::Key_B:
    dbus_data_->key_b = true;
    break;
  }
}

void KeyboardButton::keyReleaseEvent(QKeyEvent *ev) {
  switch (ev->key()) {
  case Qt::Key_W:
    dbus_data_->key_w = false;
    break;
  case Qt::Key_S:
    dbus_data_->key_s = false;
    break;
  case Qt::Key_A:
    dbus_data_->key_a = false;
    break;
  case Qt::Key_D:
    dbus_data_->key_d = false;
    break;
  case Qt::Key_Shift:
    dbus_data_->key_shift = false;
    break;
  case Qt::Key_Control:
    dbus_data_->key_ctrl = false;
    break;
  case Qt::Key_Q:
    dbus_data_->key_q = false;
    break;
  case Qt::Key_E:
    dbus_data_->key_e = false;
    break;
  case Qt::Key_R:
    dbus_data_->key_r = false;
    break;
  case Qt::Key_F:
    dbus_data_->key_f = false;
    break;
  case Qt::Key_G:
    dbus_data_->key_g = false;
    break;
  case Qt::Key_Z:
    dbus_data_->key_z = false;
    break;
  case Qt::Key_X:
    dbus_data_->key_x = false;
    break;
  case Qt::Key_C:
    dbus_data_->key_c = false;
    break;
  case Qt::Key_V:
    dbus_data_->key_v = false;
    break;
  case Qt::Key_B:
    dbus_data_->key_b = false;
    break;
  }
}