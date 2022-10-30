//
// Created by luotinkai on 2022/10/20.
//

#pragma

#include <QDebug>
#include <QDrag>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtMath>
#include <ros/ros.h>

class JoyStick : public QWidget {
  Q_OBJECT

public:
  explicit JoyStick(QWidget *parent = nullptr);
  ~JoyStick();

  double x_display_, y_display_;
signals:
  void pointMoved();

protected:
  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

  void updateJoyValue(QPoint now_pos, bool pressed);

private:
  int mouseX;
  int mouseY;
  int JoyStickX; //摇杆
  int JoyStickY;
  int JoyStickR;
  int padX; //底盘
  int padY;
  double padR;
  double handPadDis; //两圆圆心距离
  bool mousePressed;
  QTimer *tim;

private:
  static double Pointdis(int a, int b, int x, int y); //两点距离
};
