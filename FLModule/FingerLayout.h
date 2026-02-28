#pragma once

#include <map>
#include <set>

#include "FingerLayoutState.h"
#include "Kernel/Finger.h"
#include "Keyboard/KeyPosition.h"
#include "Library/Observer2/Observer.h"

namespace NSApplication {
namespace NSFingerLayout {

class CFingerLayout {
  using CFinger = NSKernel::CFinger;
  using EFingerEnum = CFinger::EFingerEnum;
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPositionContainer = std::set<CKeyPosition>;
  using CLayoutContainer =
      std::map<CFinger, CKeyPositionContainer, CFinger::CStandardOrder>;
  using CFingerLayoutOutput = NSLibrary::CObservableData<CFingerLayoutState>;
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayoutState>;

public:
  CFingerLayout();

  // нужны за пределами FL модуля
  CFingerLayout getLayout() const;
  CFinger find(CKeyPosition Position) const;

  // нужны только для view, возможно сделать protected?
  // или разнести логику модели и layout?
  void changeCurrentFinger(CFinger NewFinger);
  void changeButton(CKeyPosition ButtonForChange);
  void resetLayout();
  void sendLayout();

  void subscribeToFingerLayout(CFingerLayoutObserver* Observer);

private:
  CFingerLayout(CLayoutContainer Layout);

  static CLayoutContainer getDefaultLayout();

  static CKeyPositionContainer getDefaultLeftThumb();
  static CKeyPositionContainer getDefaultLeftIndex();
  static CKeyPositionContainer getDefaultLeftMiddle();
  static CKeyPositionContainer getDefaultLeftRing();
  static CKeyPositionContainer getDefaultLeftPinky();
  static CKeyPositionContainer getDefaultRightThumb();
  static CKeyPositionContainer getDefaultRightIndex();
  static CKeyPositionContainer getDefaultRightMiddle();
  static CKeyPositionContainer getDefaultRightRing();
  static CKeyPositionContainer getDefaultRightPinky();

  CFinger getDefaultCurrentFinger();

  CLayoutContainer Layout_;
  CFinger CurrentFinger_;
  CFingerLayoutOutput FingerLayoutOutput_;
};
} // namespace NSFingerLayout
} // namespace NSApplication

