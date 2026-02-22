#include "FingerLayout.h"

#include <cassert>

namespace NSApplication {
namespace NSFingerLayout {

CFingerLayout::CFingerLayout() : Layout_(getDefaultLayout()) {
}

CFingerLayout CFingerLayout::getLayout() const {
  return CFingerLayout(Layout_);
}

CFingerLayout::CFinger CFingerLayout::find(CKeyPosition Position) const {
  for (const auto& FingerPair : Layout_) {
    if (FingerPair.second.count(Position) > 0)
      return FingerPair.first;
  }
  return CFinger();
}

void CFingerLayout::changeCurrentFinger(CFinger new_finger) {
  assert(new_finger.id() != EFingerEnum::Undefined);
  CurrentFinger_ = new_finger;
  FingerLayoutOutput_.set(CFingerLayoutState(Layout_, CurrentFinger_));
}

void CFingerLayout::changeButton(CKeyPosition button_for_change) {
  assert(button_for_change != CKeyPosEnum::UNKN);
  for (auto& [_, buttons_for_finger] : Layout_) {
    if (!buttons_for_finger.contains(button_for_change)) {
      continue;
    }
    buttons_for_finger.erase(button_for_change);
    Layout_[CurrentFinger_].insert(button_for_change);

    FingerLayoutOutput_.set(CFingerLayoutState(Layout_, CurrentFinger_));
    return;
  }
  assert(false);
}

void CFingerLayout::subscribeToFingerLayout(CFingerLayoutObserver* observer) {
  FingerLayoutOutput_.subscribe(observer);
}

CFingerLayout::CFingerLayout(CLayoutContainer Layout)
    : Layout_(std::move(Layout)) {
}

CFingerLayout::CLayoutContainer CFingerLayout::getDefaultLayout() {
  CLayoutContainer Layout{{CFinger::LeftIndex(), getDefaultLeftIndex()},
                          {CFinger::LeftMiddle(), getDefaultLeftMiddle()},
                          {CFinger::LeftRing(), getDefaultLeftRing()},
                          {CFinger::LeftPinky(), getDefaultLeftPinky()},
                          {CFinger::RightThumb(), getDefaultRightThumb()},
                          {CFinger::RightIndex(), getDefaultRightIndex()},
                          {CFinger::RightMiddle(), getDefaultRightMiddle()},
                          {CFinger::RightRing(), getDefaultRightRing()},
                          {CFinger::RightPinky(), getDefaultRightPinky()},
                          {CFinger(), {}}};
  return Layout;
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftThumb() {
  return {};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftIndex() {
  return {CKeyPosEnum::AE05, CKeyPosEnum::AE06, CKeyPosEnum::AD04,
          CKeyPosEnum::AD05, CKeyPosEnum::AC04, CKeyPosEnum::AC05,
          CKeyPosEnum::AB04, CKeyPosEnum::AB05};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftMiddle() {
  return {CKeyPosEnum::AE04, CKeyPosEnum::AD03, CKeyPosEnum::AC03,
          CKeyPosEnum::AB03};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftRing() {
  return {CKeyPosEnum::AE03, CKeyPosEnum::AD02, CKeyPosEnum::AC02,
          CKeyPosEnum::AB02};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultLeftPinky() {
  return {CKeyPosEnum::AE01, CKeyPosEnum::AE02, CKeyPosEnum::AD01,
          CKeyPosEnum::AC01, CKeyPosEnum::AB01, CKeyPosEnum::TLDE,
          CKeyPosEnum::TAB,  CKeyPosEnum::CAPS, CKeyPosEnum::LFSH,
          CKeyPosEnum::LCTL};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightThumb() {
  return {CKeyPosEnum::SPCE};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightIndex() {
  return {CKeyPosEnum::AE07, CKeyPosEnum::AE08, CKeyPosEnum::AD06,
          CKeyPosEnum::AD07, CKeyPosEnum::AC06, CKeyPosEnum::AC07,
          CKeyPosEnum::AB06, CKeyPosEnum::AB07};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightMiddle() {
  return {CKeyPosEnum::AE09, CKeyPosEnum::AD08, CKeyPosEnum::AC08,
          CKeyPosEnum::AB08};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightRing() {
  return {CKeyPosEnum::AE10, CKeyPosEnum::AD09, CKeyPosEnum::AC09,
          CKeyPosEnum::AB09};
}

CFingerLayout::CKeyPositionContainer CFingerLayout::getDefaultRightPinky() {
  return {CKeyPosEnum::AE11, CKeyPosEnum::AE12, CKeyPosEnum::AD10,
          CKeyPosEnum::AD11, CKeyPosEnum::AD12, CKeyPosEnum::AC10,
          CKeyPosEnum::AC11, CKeyPosEnum::AB10, CKeyPosEnum::BKSP,
          CKeyPosEnum::BKSL, CKeyPosEnum::RTRN, CKeyPosEnum::RTSH,
          CKeyPosEnum::RCTL};
}

} // namespace NSFingerLayout
} // namespace NSApplication
