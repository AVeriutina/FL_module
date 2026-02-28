#pragma once

#include "Finger.h"
#include "FingerLayoutState.h"
#include "Keyboard/KeyPosition.h"
#include "Library/Observer2/Observer.h"

#include <QColor>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <map>
#include <set>

namespace NSApplication {
namespace NSFingerLayout {

class CFingerLayoutView {
  using CFinger = NSKernel::CFinger;
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
  using CKeyPosition = NSKeyboard::CKeyPosition;
  using CKeyPositionContainer = std::set<CKeyPosition>;
  using CLayoutContainer =
      std::map<CFinger, CKeyPositionContainer, CFinger::CStandardOrder>;

  using CFingerLayoutInput = NSLibrary::CHotInput<CFingerLayoutState>;
  using CViewObserver = NSLibrary::CObserver<CFingerLayoutState>;

  using CButtonsContainer = std::unordered_map<CKeyPosition, QPushButton*>;
  using CFingersContainer =
      std::map<CFinger, QPushButton*, CFinger::CStandardOrder>;

public:
  explicit CFingerLayoutView(QWidget* parent);

  CViewObserver* getFingerLayoutInput();

  const CButtonsContainer& getButtonsContainer() const;
  const CFingersContainer& getFingersContainer() const;

  QPushButton* getOkButton() const;
  QPushButton* getResetButton() const;
  QPushButton* getCancelButton() const;

  void closeWindow();

private:
  void drawState(const CFingerLayoutState& State);
  void buildLayout();
  void buildFingerPanel();
  void updateFingerPanel(CFinger currentFinger);
  void buildActionButtons();

  QMainWindow* Window_;
  QWidget* CentralWidget_;

  CFingerLayoutInput FingerLayoutInput_;
  CButtonsContainer ButtonsContainer_;
  CFingersContainer FingersContainer_;

  QPushButton* OkButton_;
  QPushButton* ResetButton_;
  QPushButton* CancelButton_;
};

} // namespace NSFingerLayout
} // namespace NSApplication
