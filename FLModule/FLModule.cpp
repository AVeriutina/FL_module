#include "FLModule.h"

namespace NSApplication {
namespace NSFingers {

CFLModule::CFLModule()
    : MainWindow_(std::make_unique<QMainWindow>()), FingerLayout_(),
      FingerLayoutView_(MainWindow_.get()),
      FingerLayoutController_(&FingerLayout_) {

  FingerLayout_.subscribeToFingerLayout(FingerLayoutView_.FingerLayoutInput());
  FingerLayoutView_.subscribeToKeyPress(
      FingerLayoutController_.keyPressInput());
  FingerLayoutView_.subscribeToFingerChange(
      FingerLayoutController_.fingerChangeInput());
  FingerLayoutView_.subscribeToKeyboardType(
      FingerLayoutController_.keyboardTypeInput());
  FingerLayoutView_.subscribeToAction(FingerLayoutController_.actionInput());
}

} // namespace NSFingers
} // namespace NSApplication
