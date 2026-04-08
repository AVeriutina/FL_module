#pragma once

#include <QColor>
#include <QString>

namespace NSApplication {
namespace NSFingers {
namespace NSViewDetails {

struct CButtonStyle {
  QColor background;
  QColor border = QColor("#888888");
  int borderWidth = 1;
  int borderRadius = 4;
  int fontSize = 16;
  bool bold = false;

  QString toStyleSheet() const {

    return QString("QPushButton {"
                   "  background-color: %1;"
                   "  border: %2px solid %3;"
                   "  border-radius: %4px;"
                   "  font-size: %5px;"
                   "  font-weight: %6;"
                   "}"
                   "QPushButton:hover   { background-color: %7; }"
                   "QPushButton:pressed { background-color: %8; }")
        .arg(background.name())
        .arg(borderWidth)
        .arg(border.name())
        .arg(borderRadius)
        .arg(fontSize)
        .arg(bold ? "bold" : "normal")
        .arg(background.darker(115).name())
        .arg(background.darker(115).name());
  }
};

inline CButtonStyle keyButtonStyle(const QColor& bg) {
  return CButtonStyle{
      .background = bg,
      .border = QColor("#888888"),
      .borderWidth = 1,
      .borderRadius = 4,
      .fontSize = 22,
      .bold = false,
  };
}

inline CButtonStyle fingerButtonStyle(const QColor& bg, bool isCurrent) {
  return CButtonStyle{
      .background = bg,
      .border = isCurrent ? QColor("#222222") : QColor("#888888"),
      .borderWidth = isCurrent ? 2 : 1,
      .borderRadius = 0,
      .fontSize = 18,
      .bold = isCurrent,
  };
}

inline CButtonStyle actionButtonStyle(const QColor& bg) {
  return CButtonStyle{
      .background = bg,
      .border = QColor("#999999"),
      .borderWidth = 1,
      .borderRadius = 6,
      .fontSize = 16,
      .bold = true,
  };
}

} // namespace NSViewDetails
} // namespace NSFingers
} // namespace NSApplication

