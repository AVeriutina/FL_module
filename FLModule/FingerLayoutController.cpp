#include "FingerLayoutController.h"

#include <cassert>

namespace NSApplication {
namespace NSFingers {

CFingerLayoutController::CFingerLayoutController(CFingerLayoutModule* Model,
                                                 CFingerLayoutView* View)
    : FingerLayout_(Model), FingerLayoutView_(View) {
  assert(FingerLayout_);
  assert(FingerLayoutView_);
  connectKeyButtons();
  connectFingerButtons();
  connectActionButtons();
}

void CFingerLayoutController::connectKeyButtons() {
  const auto& buttons = FingerLayoutView_->getButtonsContainer();
  for (auto& [keyPos, button] : buttons) {
    connect(button, &QPushButton::clicked, this,
            [this, keyPos]() { FingerLayout_->changeButton(keyPos); });
  }
}

void CFingerLayoutController::connectFingerButtons() {
  const auto& fingers = FingerLayoutView_->getFingersContainer();
  for (auto& [finger, button] : fingers) {
    connect(button, &QPushButton::clicked, this,
            [this, finger]() { FingerLayout_->changeCurrentFinger(finger); });
  }
}

void CFingerLayoutController::connectActionButtons() {
  connect(FingerLayoutView_->getOkButton(), &QPushButton::clicked, this,
          &CFingerLayoutController::accept);

  connect(FingerLayoutView_->getResetButton(), &QPushButton::clicked, this,
          &CFingerLayoutController::reset);
}

void CFingerLayoutController::accept() {
  FingerLayout_->sendLayout();
}

void CFingerLayoutController::reset() {
  FingerLayout_->resetLayout();
}

} // namespace NSFingers
} // namespace NSApplication
