#pragma once

#include <QColor>
#include <QString>

namespace NSApplication {
namespace NSFingers {
namespace NSViewDetails {

struct CButtonStyle {
  QColor background;
  QColor border = QColor(136, 136, 136);
  int borderWidth = 1;
  int borderRadius = 4;
  int fontSize = 16;
  bool bold = false;
  QColor textColor = QColor(40, 40, 40);

  QString toStyleSheet() const {
    return QString("QPushButton {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: %3px solid %4;"
                   "  border-radius: %5px;"
                   "  font-size: %6px;"
                   "  font-weight: %7;"
                   "}"
                   "QPushButton:hover   { background-color: %8; }"
                   "QPushButton:pressed { background-color: %9; }")
        .arg(background.name())
        .arg(textColor.name())
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
      .border = QColor(136, 136, 136),
      .borderWidth = 1,
      .borderRadius = 4,
      .fontSize = 22,
      .bold = false,
  };
}

inline CButtonStyle fingerButtonStyle(const QColor& bg, const QColor& border,
                                      int borderWidth, bool bold) {
  return CButtonStyle{
      .background = bg,
      .border = border,
      .borderWidth = borderWidth,
      .borderRadius = 0,
      .fontSize = 18,
      .bold = bold,
  };
}

inline CButtonStyle activeLayoutToggleStyle(const QColor& bg,
                                            const QColor& border,
                                            const QColor& text) {
  return CButtonStyle{
      .background = bg,
      .border = border,
      .borderWidth = 2,
      .borderRadius = 4,
      .fontSize = 15,
      .bold = true,
      .textColor = text,
  };
}

inline CButtonStyle inactiveLayoutToggleStyle(const QColor& bg,
                                              const QColor& border,
                                              const QColor& text) {
  return CButtonStyle{
      .background = bg,
      .border = border,
      .borderWidth = 1,
      .borderRadius = 4,
      .fontSize = 15,
      .bold = false,
      .textColor = text,
  };
}

inline CButtonStyle actionButtonStyle(const QColor& bg, const QColor& border) {
  return CButtonStyle{
      .background = bg,
      .border = border,
      .borderWidth = 1,
      .borderRadius = 6,
      .fontSize = 16,
      .bold = true,
  };
}

} // namespace NSViewDetails
} // namespace NSFingers
} // namespace NSApplication
