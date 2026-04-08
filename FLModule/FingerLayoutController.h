#pragma once

#include "FingerLayoutModule.h"
#include "FingerLayoutView.h"
#include "Keyboard/KeyPosition.h"

#include <QObject>

namespace NSApplication {
namespace NSFingers {

class CFingerLayoutController : public QObject {
  Q_OBJECT

  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CFinger = NSKernel::CFinger;

public:
  CFingerLayoutController(CFingerLayoutModule* Model, CFingerLayoutView* View);

  CFingerLayoutController(const CFingerLayoutController&) = delete;
  CFingerLayoutController(CFingerLayoutController&&) = delete;
  CFingerLayoutController& operator=(const CFingerLayoutController&) = delete;
  CFingerLayoutController& operator=(CFingerLayoutController&&) = delete;
  ~CFingerLayoutController() = default;

private:
  void connectKeyButtons();
  void connectFingerButtons();
  void connectActionButtons();

  void accept();
  void reset();

  CFingerLayoutModule* FingerLayout_;
  CFingerLayoutView* FingerLayoutView_;
};

} // namespace NSFingers
} // namespace NSApplication

