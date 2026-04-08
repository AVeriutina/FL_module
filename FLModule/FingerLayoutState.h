#pragma once

#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyPosition.h"

#include <map>
#include <set>

namespace NSApplication {
namespace NSFingers {

struct CFingerLayoutState {
  using CFinger = NSKernel::CFinger;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CStandardOrder = CFinger::CStandardOrder;

  std::map<CFinger, std::set<CKeyPosition>, CStandardOrder> layout;
  CFinger current_finger;
};

} // namespace NSFingers
} // namespace NSApplication

