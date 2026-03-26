#include "FLModule.h"

#include <QApplication>

int main(int argc, char** argv) {
  QApplication qt_runtime(argc, argv);
  try {
    NSApplication::NSFingerLayout::CFLModule app;
    return qt_runtime.exec();
  } catch (...) {
    // Except::React();
  }
  return 0;
}

