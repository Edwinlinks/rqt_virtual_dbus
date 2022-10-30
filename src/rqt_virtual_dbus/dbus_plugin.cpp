/*
  Copyright 2016 Lucas Walter
*/

#include "rqt_virtual_dbus/dbus_plugin.h"
#include <QStringList>
#include <pluginlib/class_list_macros.h>

namespace rqt_virtual_dbus {

MyPlugin::MyPlugin() : rqt_gui_cpp::Plugin(), widget_(nullptr) {
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("MyPlugin");
}

void MyPlugin::initPlugin(qt_gui_cpp::PluginContext &context) {
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  if (context.serialNumber() > 1)
    widget_->setWindowTitle(widget_->windowTitle() +
                            (' (%d)' % context.serialNumber()));
  context.addWidget(widget_);

  ui_.topicLineEdit->setText("/");
  joy_stick_left_ = new JoyStick(ui_.joy);
  joy_stick_right_ = new JoyStick(ui_.joy_3);
  slip_button_ = new SlipButton(ui_.slipButton);

  connect(this->joy_stick_left_, &JoyStick::pointMoved, this,
          &MyPlugin::getLeftJoyValue);
  connect(this->joy_stick_right_, &JoyStick::pointMoved, this,
          &MyPlugin::getRightJoyValue);
}

void MyPlugin::shutdownPlugin() {
  // unregister all publishers here
}

void MyPlugin::saveSettings(qt_gui_cpp::Settings &plugin_settings,
                            qt_gui_cpp::Settings &instance_settings) const {
  // instance_settings.setValue(k, v)
}

void MyPlugin::restoreSettings(const qt_gui_cpp::Settings &plugin_settings,
                               const qt_gui_cpp::Settings &instance_settings) {
  // v = instance_settings.value(k)
}

void MyPlugin::getLeftJoyValue() {
  getJoyValue(joy_stick_left_, ui_.joyPosLabel);
}

void MyPlugin::getRightJoyValue() {
  getJoyValue(joy_stick_right_, ui_.joyPosLabel_3);
}

void MyPlugin::getJoyValue(JoyStick *joy, QLabel *joyPosLabel) {
  QString text = "(" + QString::number(joy->x_display_) + "," +
                 QString::number(joy->y_display_) + ")";
  joyPosLabel->setText(text);
}

} // namespace rqt_virtual_dbus
PLUGINLIB_EXPORT_CLASS(rqt_virtual_dbus::MyPlugin, rqt_gui_cpp::Plugin)
