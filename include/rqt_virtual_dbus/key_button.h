//
// Created by yuchen on 2023/3/7.
//

#pragma

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QRadioButton>
#include <QTimer>
#include <QWidget>
#include <ros/ros.h>

#include "rm_msgs/DbusData.h"

class KeyboardButton : public QRadioButton {
  Q_OBJECT

public:
  explicit KeyboardButton(QWidget *parent = nullptr);
  ~KeyboardButton();

  void setDbusData(rm_msgs::DbusData *data) { dbus_data_ = data; }
  void updateSlip(bool state) { slip_state_ = state; }
  void updateState();
  void focusButton();

protected:
  void keyPressEvent(QKeyEvent *ev) override;
  void keyReleaseEvent(QKeyEvent *ev) override;
  void resizeEvent(QResizeEvent *ev) override;
  void focusOutEvent(QFocusEvent *ev) override;
  void mouseMoveEvent(QMouseEvent *ev) override;

private:
  bool slip_state_, read_keyboard_ = false;
  rm_msgs::DbusData *dbus_data_;
  QTimer *focus_timer_;
};
