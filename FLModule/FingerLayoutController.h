#pragma once

#include "FingerLayoutModule.h"
#include "FingerLayoutState.h"
#include "Keyboard/KeyPosition.h"

namespace NSApplication {
namespace NSFingers {

class CFingerLayoutController {
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CFinger = NSKernel::CFinger;

  using CKeyPressInput = NSLibrary::CColdInput<CKeyPosition>;
  using CFingerInput = NSLibrary::CColdInput<CFinger>;
  using CKeyboardTypeInput = NSLibrary::CColdInput<KeyboardType>;
  using CActionInput = NSLibrary::CColdInput<EFingerLayoutAction>;

  using CKeyPressObserver = NSLibrary::CObserver<CKeyPosition>;
  using CFingerObserver = NSLibrary::CObserver<CFinger>;
  using CKeyboardTypeObserver = NSLibrary::CObserver<KeyboardType>;
  using CActionObserver = NSLibrary::CObserver<EFingerLayoutAction>;

public:
  explicit CFingerLayoutController(CFingerLayoutModule* Model);

  CFingerLayoutController(const CFingerLayoutController&) = delete;
  CFingerLayoutController(CFingerLayoutController&&) = delete;
  CFingerLayoutController& operator=(const CFingerLayoutController&) = delete;
  CFingerLayoutController& operator=(CFingerLayoutController&&) = delete;
  ~CFingerLayoutController() = default;

  CKeyPressObserver* keyPressInput();
  CFingerObserver* fingerChangeInput();
  CKeyboardTypeObserver* keyboardTypeInput();
  CActionObserver* actionInput();

private:
  void handleAction(EFingerLayoutAction action);

  CFingerLayoutModule* FingerLayout_;
  CKeyPressInput KeyPressInput_;
  CFingerInput FingerInput_;
  CKeyboardTypeInput KeyboardTypeInput_;
  CActionInput ActionInput_;
};

} // namespace NSFingers
} // namespace NSApplication
