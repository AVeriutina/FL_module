#include "LShapeButton.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

namespace NSApplication {
namespace NSFingers {

CLShapeButton::CLShapeButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent) {
  setAttribute(Qt::WA_TranslucentBackground);
}

void CLShapeButton::setShape(int offX, int midY) {
  OffX_ = offX;
  MidY_ = midY;
  rebuildShape();
  update();
}

void CLShapeButton::setBaseColor(const QColor& color) {
  BaseColor_ = color;
  update();
}

void CLShapeButton::setBorderColor(const QColor& color) {
  BorderColor_ = color;
  update();
}

void CLShapeButton::setTextColor(const QColor& color) {
  TextColor_ = color;
  update();
}

void CLShapeButton::resizeEvent(QResizeEvent* event) {
  QPushButton::resizeEvent(event);
  rebuildShape();
}

void CLShapeButton::rebuildShape() {
  const int W = width();
  const int H = height();
  const int offX = (OffX_ > 0) ? OffX_ : W / 2;
  const int midY = (MidY_ > 0) ? MidY_ : H / 2;

  Shape_ = QPolygon({
      {0, 0},
      {W, 0},
      {W, H},
      {offX, H},
      {offX, midY},
      {0, midY},
  });

  setMask(QRegion(Shape_));
}

bool CLShapeButton::hitButton(const QPoint& pos) const {
  return Shape_.containsPoint(pos, Qt::OddEvenFill);
}

void CLShapeButton::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  const int W = width();
  const int H = height();
  const int offX = (OffX_ > 0) ? OffX_ : W / 2;
  const int midY = (MidY_ > 0) ? MidY_ : H / 2;

  QColor base = BaseColor_;
  const QColor& border = BorderColor_;

  if (isDown())
    base = base.darker(115);
  else if (underMouse())
    base = base.darker(110);

  const qreal r = 4.0;
  QPainterPath topBar, bottomBar;
  topBar.addRoundedRect(QRectF(0, 0, W, midY + r), r, r);
  bottomBar.addRoundedRect(QRectF(offX, midY - r, W - offX, H - midY + r), r,
                           r);
  QPainterPath path = topBar.united(bottomBar);

  p.setPen(QPen(border, 1.0));
  p.setBrush(base);
  p.drawPath(path);

  QFont f = font();
  f.setPixelSize(22);
  p.setFont(f);
  p.setPen(TextColor_);
  p.drawText(QRect(offX, midY, W - offX, H - midY), Qt::AlignCenter, text());
}

} // namespace NSFingers
} // namespace NSApplication
