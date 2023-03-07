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

#ifdef __has_include // 检查 __has_include 宏是否可用
#if __has_include(<libinput.h>)
#include <libinput.h>
#define HAS_LIBINPUT true
#endif
#else
#define HAS_LIBINPUT false
#endif

#include "rm_msgs/DbusData.h"

class KeyboardButton : public QRadioButton {
  Q_OBJECT

public:
  explicit KeyboardButton(QWidget *parent = nullptr);
  ~KeyboardButton();

  void setDbusData(rm_msgs::DbusData *data) { dbus_data_ = data; }
  void updateState();
  void focusButton();

protected:
  void keyPressEvent(QKeyEvent *ev) override;
  void keyReleaseEvent(QKeyEvent *ev) override;
  void resizeEvent(QResizeEvent *event) override;

private:
  bool has_libinput_;
  bool read_keyboard_ = false;
  rm_msgs::DbusData *dbus_data_;
  QTimer *focus_timer_;
};
