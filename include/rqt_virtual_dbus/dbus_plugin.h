/*
  Copyright 2016 Lucas Walter
*/
#pragma

#include "rm_msgs/DbusData.h"
#include "rqt_virtual_dbus/joy_stick.h"
#include "rqt_virtual_dbus/slip_button.h"
#include <QMessageBox>
#include <rqt_gui_cpp/plugin.h>
#include <rqt_virtual_dbus/ui_VirtualJoy.h>

namespace rqt_virtual_dbus {

class MyPlugin : public rqt_gui_cpp::Plugin {
  Q_OBJECT
public:
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
  // Comment in to signal that the plugin has a way to configure it
  // bool hasConfiguration() const;
  // void triggerConfiguration();

private:
  Ui::Form ui_{};
  JoyStick *joy_stick_left_{}, *joy_stick_right_{};
  SlipButton *slip_button_;
  QWidget *widget_;

  rm_msgs::DbusData dbus_pub_data_;
  ros::Publisher dbus_pub_;
  QTimer *pub_timer_;
  QString topic_name_;
  bool allow_pub_;
  int pub_rate_;
};
} // namespace rqt_virtual_dbus