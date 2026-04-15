#pragma once

#include <QColor>
#include <QPolygon>
#include <QPushButton>

namespace NSApplication {
namespace NSFingers {

//   (0,0)────────────(W,0)
//     │   top bar       │
//   (0,midY)─(offX,midY)│
//               │ bot bar│
//            (offX,H)──(W,H)
class CLShapeButton : public QPushButton {
  Q_OBJECT

public:
  explicit CLShapeButton(const QString& text, QWidget* parent = nullptr);

  void setShape(int offX, int midY);
  void setBaseColor(const QColor& color);
  void setBorderColor(const QColor& color);
  void setTextColor(const QColor& color);

protected:
  void resizeEvent(QResizeEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  bool hitButton(const QPoint& pos) const override;

private:
  void rebuildShape();

  int OffX_ = 0;
  int MidY_ = 0;
  QColor BaseColor_;
  QColor BorderColor_;
  QColor TextColor_;
  QPolygon Shape_;
};

} // namespace NSFingers
} // namespace NSApplication
