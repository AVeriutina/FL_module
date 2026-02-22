#include "FingerLayoutController.h"

namespace NSApplication {
namespace NSFingerLayout {

CFingerLayoutController::CFingerLayoutController(CFingerLayout& Model,
                                                 CFingerLayoutView& View)
    : Model_(Model), View_(View) {
  connectButtons();
}

void CFingerLayoutController::connectButtons() {
  const auto& buttons = View_.getButtonsContainer();

  for (auto& [keyPos, button] : buttons) {
    CKeyPosition captured = keyPos;
    connect(button, &QPushButton::clicked, this,
            [this, captured]() { Model_.changeButton(captured); });
  }
}

} // namespace NSFingerLayout
} // namespace NSApplication

