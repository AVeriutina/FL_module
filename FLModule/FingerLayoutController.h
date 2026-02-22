#pragma once

#include "FingerLayout.h"
#include "FingerLayoutView.h"
#include "KeyPosition.h"
#include <QObject>

namespace NSApplication {
namespace NSFingerLayout {

class CFingerLayoutController : public QObject {
  Q_OBJECT

  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  CFingerLayoutController(CFingerLayout& Model, CFingerLayoutView& View);

  CFingerLayoutController(const CFingerLayoutController&) = delete;
  CFingerLayoutController(CFingerLayoutController&&) = delete;
  CFingerLayoutController& operator=(const CFingerLayoutController&) = delete;
  CFingerLayoutController& operator=(CFingerLayoutController&&) = delete;
  ~CFingerLayoutController() = default;

private:
  void connectButtons();

  CFingerLayout& Model_;
  CFingerLayoutView& View_;
};

} // namespace NSFingerLayout
} // namespace NSApplication

