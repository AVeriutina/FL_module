#pragma once

#include "FingerLayoutState.h"
#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyPosition.h"
#include "Library/Observer2/Observer.h"

#include <QColor>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include <map>
#include <set>
#include <vector>

namespace NSApplication {
namespace NSFingers {

struct CFingerPalette {
  using CFinger = NSKernel::CFinger;
  using CFingerColorMap = std::map<CFinger, QColor, CFinger::CStandardOrder>;

  CFingerColorMap Fingers{
      {CFinger::LeftPinky(), QColor("#F4B8C1")},
      {CFinger::LeftRing(), QColor("#F9D4A0")},
      {CFinger::LeftMiddle(), QColor("#FAF0A0")},
      {CFinger::LeftIndex(), QColor("#B8EAB8")},
      {CFinger::LeftThumb(), QColor("#A8D8EA")},
      {CFinger::RightThumb(), QColor("#C3B8EA")},
      {CFinger::RightIndex(), QColor("#B8D4EA")},
      {CFinger::RightMiddle(), QColor("#A8EAD8")},
      {CFinger::RightRing(), QColor("#D4EAA8")},
      {CFinger::RightPinky(), QColor("#EAC8A8")},
      {CFinger(), QColor("#d6d6d6")}, // Unassigned
  };

  QColor Default = QColor("#d6d6d6");
};

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
  explicit CFingerLayoutView(QMainWindow* window);

  CViewObserver* FingerLayoutInput();

  const CButtonsContainer& getButtonsContainer() const;
  const CFingersContainer& getFingersContainer() const;

  QPushButton* getOkButton() const;
  QPushButton* getResetButton() const;
  QPushButton* getCancelButton() const;

private:
  void drawLayout(const CLayoutContainer& layout);
  void drawState(const CFingerLayoutState& State);
  void buildLayout();
  int placeFingerGroup(const std::vector<CFinger>& fingers, int x, int y,
                       const CFingerPalette::CFingerColorMap& colorMap);
  void buildFingerPanel();
  void updateFingerPanel(CFinger currentFinger);
  void buildActionButtons();
  QPushButton* makeButton(const char* label, int x, int y, const QColor& bg);

  CFingerLayoutInput FingerLayoutInput_;

  CFingerPalette Palette_;

  CButtonsContainer ButtonsContainer_;
  CFingersContainer FingersContainer_;

  QMainWindow* Window_;
  QWidget* CentralWidget_;
  QPushButton* OkButton_;
  QPushButton* ResetButton_;
  QPushButton* CancelButton_;
};

} // namespace NSFingers
} // namespace NSApplication
