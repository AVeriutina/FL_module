#include "FingerLayoutModule.h"
#include "KeyboardScheme.h"

#include <cassert>
#include <limits>

namespace {

using CFinger = NSApplication::NSKernel::CFinger;
using CKeyPosition = NSApplication::NSKeyboard::CKeyPosition;
using CLayoutContainer =
    std::map<CFinger, std::set<CKeyPosition>, CFinger::CStandardOrder>;

// думаю тебе это не понравиться, но пока функционал
// NSApplication::NSKernel::CFingerLayout такой, я не вижу как это более красиво
// сделать
CLayoutContainer getDefaultLayout() {
  const auto kernelLayout =
      NSApplication::NSKernel::CFingerLayout::getDefault();
  CLayoutContainer result;
  // TODO добавить в Keyboard (NSKeyboard::CKeyPosition /
  // CFingerLayout::getDefault)
  result[CFinger().LeftPinky()] = {
      NSApplication::NSFingers::CKeyboardScheme::kISO102Key};
  for (CKeyPosition pos = 0;; ++pos) {
    const CFinger finger = kernelLayout.find(pos);
    if (finger.id() != CFinger::EFingerEnum::Undefined)
      result[finger].insert(pos);
    if (pos == std::numeric_limits<CKeyPosition>::max())
      break;
  }
  return result;
}

} // namespace

namespace NSApplication {
namespace NSFingers {

CFingerLayoutModule::CFingerLayoutModule()
    : Layout_(getDefaultLayout()), InitialLayout_(Layout_),
      CurrentFinger_(CFinger::LeftPinky()) {
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::changeCurrentFinger(CFinger new_finger) {
  CurrentFinger_ = new_finger;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::changeButton(CKeyPosition button_for_change) {
  for (auto& [_, buttons_for_finger] : Layout_) {
    if (!buttons_for_finger.contains(button_for_change)) {
      continue;
    }
    buttons_for_finger.erase(button_for_change);
    Layout_[CurrentFinger_].insert(button_for_change);

    FingerLayoutOutput_.set(
        CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
    return;
  }
}

void CFingerLayoutModule::resetLayout() {
  Layout_ = InitialLayout_;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::sendLayout() {
  // TODO integration
  //  send layout to app
}

void CFingerLayoutModule::setKeyboardType(KeyboardType type) {
  CurrentKeyboardType_ = type;
  FingerLayoutOutput_.set(
      CFingerLayoutState{Layout_, CurrentFinger_, CurrentKeyboardType_});
}

void CFingerLayoutModule::subscribeToFingerLayout(
    CFingerLayoutObserver* observer) {
  assert(observer);
  FingerLayoutOutput_.subscribe(observer);
}

} // namespace NSFingers
} // namespace NSApplication
