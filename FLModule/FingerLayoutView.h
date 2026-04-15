#pragma once

#include "FingerLayoutState.h"
#include "Kernel/FingerLayout.h"
#include "Keyboard/KeyPosition.h"
#include "KeyboardScheme.h"
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

struct CFingerLayoutPalette {
  using CFinger = NSKernel::CFinger;
  using CFingerColorMap = std::map<CFinger, QColor, CFinger::CStandardOrder>;

  CFingerColorMap Fingers{{
      {CFinger::LeftPinky(), QColor(244, 184, 193)},
      {CFinger::LeftRing(), QColor(249, 212, 160)},
      {CFinger::LeftMiddle(), QColor(250, 240, 160)},
      {CFinger::LeftIndex(), QColor(184, 234, 184)},
      {CFinger::LeftThumb(), QColor(168, 216, 234)},
      {CFinger::RightThumb(), QColor(195, 184, 234)},
      {CFinger::RightIndex(), QColor(184, 212, 234)},
      {CFinger::RightMiddle(), QColor(168, 234, 216)},
      {CFinger::RightRing(), QColor(212, 234, 168)},
      {CFinger::RightPinky(), QColor(234, 200, 168)},
  }};

  QColor UnassignedKey = QColor(214, 214, 214);

  // Key and button structural colors
  QColor KeyBorder = QColor(136, 136, 136);
  QColor ButtonText = QColor(40, 40, 40);
  QColor FingerBorderActive = QColor(34, 34, 34);
  QColor FingerBorderInactive = QColor(136, 136, 136);
  QColor ActionBorder = QColor(153, 153, 153);

  // Layout toggle colors
  QColor ToggleActiveBg = QColor(21, 101, 192);
  QColor ToggleActiveBorder = QColor(13, 71, 161);
  QColor ToggleActiveText = QColor(255, 255, 255);
  QColor ToggleInactiveBg = QColor(227, 242, 253);
  QColor ToggleInactiveBorder = QColor(144, 202, 249);
  QColor ToggleInactiveText = QColor(21, 101, 192);
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

  using CKeyPositionObservable = NSLibrary::CObservableData<CKeyPosition>;
  using CKeyPressObserver = NSLibrary::CObserver<CKeyPosition>;

  using CFingerObservable = NSLibrary::CObservableData<CFinger>;
  using CFingerObserver = NSLibrary::CObserver<CFinger>;
  using CActionObservable = NSLibrary::CObservableData<EFingerLayoutAction>;
  using CActionObserver = NSLibrary::CObserver<EFingerLayoutAction>;
  using CKeyboardTypeObservable = NSLibrary::CObservableData<KeyboardType>;
  using CKeyboardTypeObserver = NSLibrary::CObserver<KeyboardType>;

  using CButtonsContainer = std::unordered_map<CKeyPosition, QPushButton*>;
  using CFingersContainer =
      std::map<CFinger, QPushButton*, CFinger::CStandardOrder>;

public:
  explicit CFingerLayoutView(QMainWindow* window);

  CViewObserver* FingerLayoutInput();
  void subscribeToKeyPress(CKeyPressObserver* observer);
  void subscribeToFingerChange(CFingerObserver* observer);
  void subscribeToAction(CActionObserver* observer);
  void subscribeToKeyboardType(CKeyboardTypeObserver* observer);

private:
  void switchTo(KeyboardType type);
  void drawLayout(const CLayoutContainer& layout);
  void drawState(const CFingerLayoutState& State);
  void applyScheme(KeyboardType newType);
  QPushButton* createKeyButton(CKeyPosEnum::CType keyPos, const QRect& rect);
  void colorKeyButton(CKeyPosition pos, const QColor& color);
  void updateToggleButtons();
  int placeFingerGroup(const std::vector<CFinger>& fingers, int x, int y,
                       const CFingerLayoutPalette::CFingerColorMap& colorMap);
  void buildFingerPanel();
  void updateFingerPanel(CFinger currentFinger);
  void buildActionButtons();
  void buildToggleButtons();
  QPushButton* makeActionButton(const char* label, int x, int y,
                                const QColor& bg);

  int fingerPanelBottom() const;
  int fingerBtnTop(int h) const;
  int fingerPanelStartX() const;
  int actionRowY() const;

  CFingerLayoutInput FingerLayoutInput_;
  CKeyPositionObservable KeyPressOutput_;
  CFingerObservable FingerChangeOutput_;
  CActionObservable ActionOutput_;
  CKeyboardTypeObservable KeyboardTypeOutput_;

  CFingerLayoutPalette Palette_;
  KeyboardType CurrentKeyboardType_ = KeyboardType::ANSI;
  CKeyboardScheme CurrentScheme_;
  CFingerLayoutScheme LayoutScheme_;

  CButtonsContainer ButtonsContainer_;
  CFingersContainer FingersContainer_;

  QMainWindow* Window_;
  QWidget* CentralWidget_;
  QPushButton* OkButton_;
  QPushButton* ResetButton_;
  QPushButton* CancelButton_;
  QPushButton* ANSIButton_;
  QPushButton* ISOButton_;

  CFingerLayoutState LastState_;
};

} // namespace NSFingers
} // namespace NSApplication
