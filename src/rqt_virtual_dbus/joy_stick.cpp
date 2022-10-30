//
// Created by luotinkai on 2022/10/20.
//

#include "rqt_virtual_dbus/joy_stick.h"

JoyStick::JoyStick(QWidget *parent) : QWidget(parent) {
  setPalette(QPalette(Qt::white));
  resize(parent->width(), parent->height());
  setMinimumSize(100, 100);
  mouseX = width() / 2;
  mouseY = height() / 2;
  tim = new QTimer(this);
}

JoyStick::~JoyStick() {}

void JoyStick::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  int side = qMin(width(), height());

  padR = side / 2;      //底盘半径
  padX = padR;          //底盘圆心
  padY = padR;          //底盘圆心
  JoyStickR = padR / 4; //摇杆圆半径
  int JoyStickMaxR = padR - JoyStickR;
  QColor JoyStickColor;
  JoyStickColor.setRgb(85, 87, 83);
  //加载底盘图像
  //    painter.save();

  //    painter.scale(side / 400.0, side / 400.0);//坐标会随窗口缩放
  //    painter.drawPixmap(0, 0, QPixmap(":/image/pad.png"));
  //    painter.restore();
  //自绘底盘
  painter.save();
  QRadialGradient RadialGradient(padR, padR, padR * 3, padR,
                                 padR); //圆心2，半径1，焦点2
  //  RadialGradient.setColorAt(0, QColor(255, 253, 253, 255)); //渐变
  //  RadialGradient.setColorAt(1, QColor(255, 240, 245, 190)); //渐变
  RadialGradient.setColorAt(0, QColor(255, 253, 253, 190)); //渐变
  RadialGradient.setColorAt(1, QColor(255, 240, 245, 190)); //渐变
  painter.setBrush(RadialGradient);
  painter.setPen(Qt::NoPen);
  painter.drawEllipse(QPoint(padR, padR), side / 2, side / 2); //大圆盘
  painter.restore();

  if (!mousePressed) { //鼠标没按下则摇杆恢复到底盘中心
    mouseX = padX;
    mouseY = padY;
  }
  handPadDis = Pointdis(padR, padR, mouseX, mouseY);
  if (handPadDis <= JoyStickMaxR) {
    JoyStickX = mouseX;
    JoyStickY = mouseY;

  } else {
    JoyStickX = (int)(JoyStickMaxR * (mouseX - padX) / handPadDis + padX);
    JoyStickY = (int)(JoyStickMaxR * (mouseY - padY) / handPadDis + padY);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(JoyStickColor);
  painter.drawEllipse(QPoint(JoyStickX, JoyStickY), JoyStickR,
                      JoyStickR); //摇杆
}

void JoyStick::mouseMoveEvent(QMouseEvent *event) {
  static bool r = false;
  mouseX = event->pos().x();
  mouseY = event->pos().y();
  QPoint now_pos = QPoint(event->pos().x(), event->pos().y());
  update();
  updateJoyValue(now_pos, true);
}
void JoyStick::mouseReleaseEvent(QMouseEvent *event) {
  QPoint now_pos = QPoint(event->pos().x(), event->pos().y());
  mouseX = width() / 2;
  mouseY = height() / 2;
  tim->stop();
  mousePressed = false;
  update();
  updateJoyValue(now_pos, false);
}

void JoyStick::mousePressEvent(QMouseEvent *event) {
  mouseX = event->pos().x();
  mouseY = event->pos().y();
  tim->start(100);
  mousePressed = true;
  update();
}

double JoyStick::Pointdis(int a, int b, int x, int y) {
  return sqrt((double)((x - a) * (x - a) + (y - b) * (y - b)));
}

void JoyStick::updateJoyValue(QPoint now_pos, bool pressed) {
  if (pressed) {
    QPoint center = QPoint(height() / 2, width() / 2);
    QPoint relative = now_pos - center;
    x_display_ = abs(static_cast<double>(relative.x())) < padR
                     ? (double)(relative.x()) / (double)(padR)
                     : relative.x() / abs(relative.x());
    y_display_ = abs(static_cast<double>(relative.y())) < padR
                     ? (double)(-relative.y()) / (double)(padR)
                     : -relative.y() / abs(relative.y());
  } else {
    x_display_ = 0.0;
    y_display_ = 0.0;
  }
  emit pointMoved();
}
