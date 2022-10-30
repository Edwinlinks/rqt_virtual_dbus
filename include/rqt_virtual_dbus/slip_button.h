//
// Created by luotinkai on 2022/10/21.
//
#pragma
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <cmath>

class SlipButton : public QWidget {
  Q_OBJECT

public:
  explicit SlipButton(QWidget *parent = nullptr);
  ~SlipButton();

private:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void onTimer();

  bool isOn{false};
  bool runing{false};
  int x;
  QTimer timer;
};