#include "FingerLayoutController.h"

namespace NSApplication {
namespace NSFingerLayout {

CFingerLayoutController::CFingerLayoutController(CFingerLayout& Model,
                                                 CFingerLayoutView& View)
    : FingerLayout_(Model), FingerLayoutView_(View) {
  connectKeyButtons();
  connectFingerButtons();
  connectActionButtons();
}

void CFingerLayoutController::connectKeyButtons() {
  const auto& buttons = FingerLayoutView_.getButtonsContainer();
  for (auto& [keyPos, button] : buttons) {
    connect(button, &QPushButton::clicked, this,
            [this, keyPos]() { FingerLayout_.changeButton(keyPos); });
  }
}

void CFingerLayoutController::connectFingerButtons() {
  const auto& fingers = FingerLayoutView_.getFingersContainer();
  for (auto& [finger, button] : fingers) {
    connect(button, &QPushButton::clicked, this,
            [this, finger]() { FingerLayout_.changeCurrentFinger(finger); });
  }
}

void CFingerLayoutController::connectActionButtons() {
  connect(FingerLayoutView_.getOkButton(), &QPushButton::clicked, this,
          [this]() {
            FingerLayout_.sendLayout();
            FingerLayoutView_.closeWindow();
          });

  connect(FingerLayoutView_.getResetButton(), &QPushButton::clicked, this,
          [this]() { FingerLayout_.resetLayout(); });

  connect(FingerLayoutView_.getCancelButton(), &QPushButton::clicked, this,
          [this]() { FingerLayoutView_.closeWindow(); });
}

} // namespace NSFingerLayout
} // namespace NSApplication

