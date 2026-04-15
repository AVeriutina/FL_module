#pragma once

#include "FingerLayoutState.h"
#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyPosition.h"
#include "Library/Observer2/Observer.h"

#include <map>
#include <set>

namespace NSApplication {
namespace NSFingers {

class CFingerLayoutModule {
  using CFinger = NSKernel::CFinger;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPositionContainer = std::set<CKeyPosition>;
  using CLayoutContainer =
      std::map<CFinger, CKeyPositionContainer, CFinger::CStandardOrder>;
  using CFingerLayoutOutput = NSLibrary::CObservableData<CFingerLayoutState>;
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayoutState>;

public:
  CFingerLayoutModule();

  void subscribeToFingerLayout(CFingerLayoutObserver* Observer);

  void changeCurrentFinger(CFinger NewFinger);
  void changeButton(CKeyPosition ButtonForChange);
  void resetLayout();
  void sendLayout();
  void setKeyboardType(KeyboardType type);

private:
  CLayoutContainer Layout_;
  CLayoutContainer InitialLayout_;
  CFinger CurrentFinger_;
  KeyboardType CurrentKeyboardType_ = KeyboardType::ANSI;
  CFingerLayoutOutput FingerLayoutOutput_;
};
} // namespace NSFingers
} // namespace NSApplication

