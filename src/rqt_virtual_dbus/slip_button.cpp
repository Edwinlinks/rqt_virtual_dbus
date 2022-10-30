//
// Created by luotinkai on 2022/10/21.
//

#include "rqt_virtual_dbus/slip_button.h"

SlipButton::SlipButton(QWidget *parent) : QWidget(parent) {
  connect(&timer, &QTimer::timeout, this, &SlipButton::onTimer);
  timer.setInterval(40);

  QTimer::singleShot(100, [this] {
    QRect rect = this->rect();
    QRect outRoundRect = rect.adjusted(3, 3, -3, -3);
    x = outRoundRect.x() + 2;
    this->update();
  });
}

SlipButton::~SlipButton() {}

void SlipButton::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    isOn = !isOn;
    timer.start();
  }
  return QWidget::mousePressEvent(event);
}

void SlipButton::mouseReleaseEvent(QMouseEvent *event) {
  return QWidget::mouseReleaseEvent(event);
}

void SlipButton::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.save();
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
  painter.setRenderHint(QPainter::TextAntialiasing, true);
  painter.setPen(Qt::transparent);

  QRect rect = this->rect();
  QRect outRoundRect = rect.adjusted(3, 3, -3, -3);

  if (x > outRoundRect.x() + outRoundRect.width() * 0.45 - 2) {
    x = outRoundRect.x() + outRoundRect.width() * 0.45 - 2;
    if (runing) {
      timer.stop();
      runing = false;
    }
  }
  if (x < outRoundRect.x() + 2) {
    x = outRoundRect.x() + 2;
    if (runing) {
      timer.stop();
      runing = false;
    }
  }
  if (isOn) {
    if (runing)
      painter.setBrush(QColor("#E7E7E7"));
    else
      painter.setBrush(QColor("#90EE90"));

    painter.drawRoundRect(outRoundRect, 6, 6);
    painter.setBrush(Qt::white);

    QRect innerRect;
    if (runing)
      innerRect = QRect(x, outRoundRect.y() + 2, outRoundRect.width() * 0.55,
                        outRoundRect.height() - 4);
    else
      innerRect = QRect(outRoundRect.x() + outRoundRect.width() * 0.45 - 2,
                        outRoundRect.y() + 2, outRoundRect.width() * 0.55,
                        outRoundRect.height() - 4);
    painter.drawRoundRect(innerRect, 8, 8);
  } else {
    if (runing)
      painter.setBrush(QColor("#90EE90"));
    else
      painter.setBrush(QColor("#E7E7E7"));

    painter.drawRoundRect(outRoundRect, 6, 6);
    painter.setBrush(Qt::white);

    QRect innerRect;
    if (runing)
      innerRect = QRect(x, outRoundRect.y() + 2, outRoundRect.width() * 0.55,
                        outRoundRect.height() - 4);
    else
      innerRect = QRect(outRoundRect.x() + 2, outRoundRect.y() + 2,
                        outRoundRect.width() * 0.55, outRoundRect.height() - 4);
    painter.drawRoundRect(innerRect, 8, 8);
  }
  painter.restore();
}

void SlipButton::onTimer() {
  runing = true;
  QRect rect = this->rect();
  if (isOn)
    x += rect.width() * 0.072;
  else
    x -= rect.width() * 0.072;
  update();
}