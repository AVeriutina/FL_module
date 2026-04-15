#pragma once

#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyPosition.h"

#include <map>
#include <set>

namespace NSApplication {
namespace NSFingers {

enum class KeyboardType { ANSI, ISO };
enum class EFingerLayoutAction { Ok, Reset };

struct CFingerLayoutState {
  using CFinger = NSKernel::CFinger;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CStandardOrder = CFinger::CStandardOrder;

  std::map<CFinger, std::set<CKeyPosition>, CStandardOrder> layout;
  CFinger current_finger;
  KeyboardType keyboard_type = KeyboardType::ANSI;
};

} // namespace NSFingers
} // namespace NSApplication

