#include "FLModule.h"

namespace NSApplication {
namespace NSFingerLayout {

CFLModule::CFLModule(QWidget* parent)
    : FingerLayout_(), FingerLayoutView_(parent),
      FingerLayoutController_(FingerLayout_, FingerLayoutView_) {
  FingerLayout_.subscribeToFingerLayout(
      FingerLayoutView_.getFingerLayoutInput());
}

} // namespace NSFingerLayout
} // namespace NSApplication
