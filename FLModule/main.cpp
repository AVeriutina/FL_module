#include <QApplication>

#include "FLModule.h"

int main(int argc, char** argv) {
  QApplication qt_runtime(argc, argv);
  try {
    auto prnt = new QMainWindow();
    prnt->show();
    NSApplication::NSFingerLayout::CFLModule app(prnt);
    return qt_runtime.exec();
  } catch (...) {
    // Except::React();
  }
  return 0;
}

