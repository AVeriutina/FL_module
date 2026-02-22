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
  using CFingerLayoutObservable =
      NSLibrary::CObservableData<CFingerLayoutState>;
  using CFingerLayoutObserver = NSLibrary::CObserver<CFingerLayoutState>;

public:
  CFingerLayout();

  // нужны за пределами FL модуля
  CFingerLayout getLayout() const;
  CFinger find(CKeyPosition Position) const;

  // нужны только для view, возможно сделать protected?
  void changeCurrentFinger(CFinger NewFinger);
  void changeButton(CKeyPosition ButtonForChange);

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

  CLayoutContainer Layout_;
  CFinger CurrentFinger_;
  CFingerLayoutObservable FingerLayoutOutput_;
};
} // namespace NSFingerLayout
} // namespace NSApplication
