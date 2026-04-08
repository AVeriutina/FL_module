#include "FLModule.h"

#include <QPushButton>

namespace NSApplication {
namespace NSFingers {

CFLModule::CFLModule()
    : MainWindow_(std::make_unique<QMainWindow>()), FingerLayout_(),
      FingerLayoutView_(MainWindow_.get()),
      FingerLayoutController_(&FingerLayout_, &FingerLayoutView_) {
  FingerLayout_.subscribeToFingerLayout(FingerLayoutView_.FingerLayoutInput());
  QObject::connect(FingerLayoutView_.getCancelButton(), &QPushButton::clicked,
                   MainWindow_.get(), &QMainWindow::close);
}

} // namespace NSFingers
} // namespace NSApplication

