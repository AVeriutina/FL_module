#pragma once

#include "Finger.h"
#include "Keyboard/KeyPosition.h"
#include <map>
#include <set>

namespace NSApplication {
namespace NSFingerLayout {

struct CFingerLayoutState {
private:
  using CFinger = NSKernel::CFinger;
  using CKeyPosition = NSKeyboard::CKeyPosition;

public:
  std::map<CFinger, std::set<CKeyPosition>, CFinger::CStandardOrder> layout;
  CFinger current_finger;
};

} // namespace NSFingerLayout
} // namespace NSApplication

