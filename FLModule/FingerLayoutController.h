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
  using CFinger = NSKernel::CFinger;

public:
  CFingerLayoutController(CFingerLayout& Model, CFingerLayoutView& View);

  CFingerLayoutController(const CFingerLayoutController&) = delete;
  CFingerLayoutController(CFingerLayoutController&&) = delete;
  CFingerLayoutController& operator=(const CFingerLayoutController&) = delete;
  CFingerLayoutController& operator=(CFingerLayoutController&&) = delete;
  ~CFingerLayoutController() = default;

private:
  void connectKeyButtons();
  void connectFingerButtons();
  void connectActionButtons();

  CFingerLayout& FingerLayout_;
  CFingerLayoutView& FingerLayoutView_;
};

} // namespace NSFingerLayout
} // namespace NSApplication

