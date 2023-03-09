/*
  Copyright 2016 Lucas Walter
*/
#pragma

#include <QMessageBox>
#include <QScrollBar>
#include <QTextBrowser>
#include <rqt_gui_cpp/plugin.h>
#include <rqt_virtual_dbus/ui_VirtualJoy.h>

#include "rm_msgs/DbusData.h"
#include "rqt_virtual_dbus/joy_stick.h"
#include "rqt_virtual_dbus/key_button.h"
#include "rqt_virtual_dbus/slip_button.h"

namespace rqt_virtual_dbus {

class MyPlugin : public rqt_gui_cpp::Plugin {
  Q_OBJECT
public:
  enum SwitchState { UP = 0, MID = 50, DOWN = 99 };
  enum ControlMode { IDLE, RC, PC };

  MyPlugin();
  void initPlugin(qt_gui_cpp::PluginContext &context) override;
  void shutdownPlugin() override;
  void saveSettings(qt_gui_cpp::Settings &plugin_settings,
                    qt_gui_cpp::Settings &instance_settings) const override;
  void restoreSettings(const qt_gui_cpp::Settings &plugin_settings,
                       const qt_gui_cpp::Settings &instance_settings) override;

  void getLeftJoyValue();
  void getRightJoyValue();
  void getJoyValue(JoyStick *joy, QLabel *joyPosLabel);

  void topicNameUpdated();
  void updatePublisher();
  void startIntervalTimer();
  void slipButtonChanged();
  void publishRateSpinBoxChanged();
  void updateROSPublishState();
  void updateSwitchState();
  void startWheelResetTimer();
  void updateWheelState();
  // Comment in to signal that the plugin has a way to configure it
  // bool hasConfiguration() const;
  // void triggerConfiguration();
signals:
  void slipChange(bool);

private:
  Ui::Form ui_{};
  JoyStick *joy_stick_left_{}, *joy_stick_right_{};
  SlipButton *slip_button_;
  KeyboardButton *key_button_;
  QWidget *widget_;

  rm_msgs::DbusData dbus_pub_data_;
  ros::Publisher dbus_pub_;
  QTimer *pub_timer_, *wheel_timer_;
  QString topic_name_;
  int pub_rate_, state_ = ControlMode::IDLE;
};
} // namespace rqt_virtual_dbus