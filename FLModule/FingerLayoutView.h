#pragma once

#include "Finger.h"
#include "FingerLayoutState.h"
#include "Keyboard/KeyPosition.h"
#include "Library/Observer2/Observer.h"

#include <QColor>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

namespace NSApplication {
namespace NSFingerLayout {

class CFingerLayoutView {
  using CFinger = NSKernel::CFinger;
  using EFingerEnum = CFinger::EFingerEnum;
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPositionContainer = std::set<CKeyPosition>;
  using CLayoutContainer =
      std::map<CFinger, CKeyPositionContainer, CFinger::CStandardOrder>;

  using CFingerLayoutInput = NSLibrary::CColdInput<CFingerLayoutState>;
  using CViewObserver = NSLibrary::CObserver<CFingerLayoutState>;

  using CButtonsContainer = std::unordered_map<CKeyPosition, QPushButton*>;
  using CFingersContainer =
      std::map<CFinger, QPushButton*, CFinger::CStandardOrder>;

public:
  CFingerLayoutView(QWidget* parent);
  CViewObserver* getFingerLayoutInput();
  const CButtonsContainer& getButtonsContainer() const;

private:
  void drawState(const CFingerLayoutState& State);
  void buildLayout();
  void resetButtonColor(CKeyPosition pos);

  QMainWindow* Window_;
  QWidget* CentralWidget_;

  CFingerLayoutInput FingerLayoutInput_;
  CButtonsContainer ButtonsContainer_;
  CFingersContainer FingersContainer_;
};

} // namespace NSFingerLayout
} // namespace NSApplication

