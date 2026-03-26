#pragma once

#include "FingerLayoutController.h"
#include "FingerLayoutModule.h"
#include "FingerLayoutView.h"

#include <QMainWindow>

#include <memory>

namespace NSApplication {
namespace NSFingerLayout {

class CFLModule {
public:
  CFLModule();
  ~CFLModule() = default;

private:
  std::unique_ptr<QMainWindow> MainWindow_;
  CFingerLayoutModule FingerLayout_;
  CFingerLayoutView FingerLayoutView_;
  CFingerLayoutController FingerLayoutController_;
};
} // namespace NSFingerLayout
} // namespace NSApplication

