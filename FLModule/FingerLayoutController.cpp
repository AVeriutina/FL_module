#include "FingerLayoutController.h"

#include <cassert>

namespace {

template<class T>
T* validated(T* ptr) {
  assert(ptr);
  return ptr;
}

} // namespace

namespace NSApplication {
namespace NSFingers {

CFingerLayoutController::CFingerLayoutController(CFingerLayoutModule* Model)
    : FingerLayout_(validated(Model)), KeyPressInput_([this](CKeyPosition pos) {
        FingerLayout_->changeButton(pos);
      }),
      FingerInput_(
          [this](CFinger f) { FingerLayout_->changeCurrentFinger(f); }),
      KeyboardTypeInput_(
          [this](KeyboardType t) { FingerLayout_->setKeyboardType(t); }),
      ActionInput_([this](EFingerLayoutAction a) { handleAction(a); }) {
}

CFingerLayoutController::CKeyPressObserver*
CFingerLayoutController::keyPressInput() {
  return &KeyPressInput_;
}

CFingerLayoutController::CFingerObserver*
CFingerLayoutController::fingerChangeInput() {
  return &FingerInput_;
}

CFingerLayoutController::CKeyboardTypeObserver*
CFingerLayoutController::keyboardTypeInput() {
  return &KeyboardTypeInput_;
}

CFingerLayoutController::CActionObserver*
CFingerLayoutController::actionInput() {
  return &ActionInput_;
}

void CFingerLayoutController::handleAction(EFingerLayoutAction action) {
  switch (action) {
  case EFingerLayoutAction::Ok:
    FingerLayout_->sendLayout();
    break;
  case EFingerLayoutAction::Reset:
    FingerLayout_->resetLayout();
    break;
  }
}

} // namespace NSFingers
} // namespace NSApplication
