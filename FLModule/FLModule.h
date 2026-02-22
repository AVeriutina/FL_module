#pragma once

#include "FingerLayout.h"
#include "FingerLayoutController.h"
#include "FingerLayoutView.h"

namespace NSApplication {
namespace NSFingerLayout {

class CFLModule {
public:
  CFLModule(QWidget* parent);

private:
  CFingerLayout FingerLayout_;
  CFingerLayoutView FingerLayoutView_;
  CFingerLayoutController FingerLayoutController_;
};
} // namespace NSFingerLayout
} // namespace NSApplication

