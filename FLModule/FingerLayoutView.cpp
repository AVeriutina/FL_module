#include "FingerLayoutView.h"
#include "Coordinates.h"
#include "StyleSheet.h"
#include <cassert>
#include <qcolor.h>

namespace NSApplication {
namespace NSFingerLayout {

namespace {

using CFinger = NSKernel::CFinger;
using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
using namespace NSCoordinates::LayoutConstants;

std::map<CFinger, QColor, CFinger::CStandardOrder> defaultFingerColors() {
  return {{CFinger::LeftPinky(), QColor("#F4B8C1")},
          {CFinger::LeftRing(), QColor("#F9D4A0")},
          {CFinger::LeftMiddle(), QColor("#FAF0A0")},
          {CFinger::LeftIndex(), QColor("#B8EAB8")},
          {CFinger::LeftThumb(), QColor("#A8D8EA")},
          {CFinger::RightThumb(), QColor("#C3B8EA")},
          {CFinger::RightIndex(), QColor("#B8D4EA")},
          {CFinger::RightMiddle(), QColor("#A8EAD8")},
          {CFinger::RightRing(), QColor("#D4EAA8")},
          {CFinger::RightPinky(), QColor("#EAC8A8")},
          {CFinger(), QColor("#d6d6d6")}};
}

std::unordered_map<CKeyPosEnum::CType, const char*> keyLabels() {
  return {{CKeyPosEnum::BKSP, "Back"},
          {CKeyPosEnum::TAB, "Tab"},
          {CKeyPosEnum::CAPS, "Caps"},
          {CKeyPosEnum::RTRN, "Enter"},
          {CKeyPosEnum::LFSH, "Shift"},
          {CKeyPosEnum::RTSH, "Shift"},
          {CKeyPosEnum::LCTL, "Ctrl"},
          // {CKeyPosEnum::LALT, "Alt"},
          // {CKeyPosEnum::RALT, "Alt"},
          {CKeyPosEnum::RCTL, "Ctrl"}};
}

const std::set<CKeyPosEnum::CType> kSkippedButtons = {
    CKeyPosEnum::LWIN, CKeyPosEnum::LALT, CKeyPosEnum::RALT, CKeyPosEnum::MENU,
    CKeyPosEnum::RWIN};

const char* fingerLabel(CFinger f) {
  using E = CFinger::EFingerEnum;
  const bool left = f.isLeftHand();
  switch (f.id() & E::FingerMask) {
  case E::Thumb:
    return left ? "L\nThumb" : "R\nThumb";
  case E::Index:
    return left ? "L\nIndex" : "R\nIndex";
  case E::Middle:
    return left ? "L\nMiddle" : "R\nMiddle";
  case E::Ring:
    return left ? "L\nRing" : "R\nRing";
  case E::Pinky:
    return left ? "L\nPinky" : "R\nPinky";
  default:
    return "?";
  }
}

// Y нижнего края панели пальцев (по которому выравниваются все кнопки)
int fingerPanelBottom() {
  return NSCoordinates::keyboardBottomEdge() + PANEL_TOP_OFFSET +
         FINGER_BTN_H_SEL;
}

// Y верхнего края кнопки пальца с заданной высотой (выравнивание по низу)
int fingerBtnTop(int h) {
  return fingerPanelBottom() - h;
}

// X левого края первой кнопки пальца (панель центрирована под клавиатурой)
int fingerPanelStartX() {
  const int totalPanelW = 5 * FINGER_BTN_W + HAND_GAP + 5 * FINGER_BTN_W;
  const int kbdCenterX = (NSCoordinates::KeyboardConstants::START_X +
                          NSCoordinates::keyboardRightEdge()) /
                         2;
  return kbdCenterX - totalPanelW / 2;
}

// Y строки кнопок действий
int actionRowY() {
  return fingerPanelBottom() + ACTION_ROW_OFFSET;
}

// ── Порядок пальцев
// ───────────────────────────────────────────────────────────

const std::vector<CFinger>& leftFingers() {
  static const std::vector<CFinger> fingers = {
      CFinger::LeftPinky(), CFinger::LeftRing(), CFinger::LeftMiddle(),
      CFinger::LeftIndex(), CFinger::LeftThumb()};
  return fingers;
}

const std::vector<CFinger>& rightFingers() {
  static const std::vector<CFinger> fingers = {
      CFinger::RightThumb(), CFinger::RightIndex(), CFinger::RightMiddle(),
      CFinger::RightRing(), CFinger::RightPinky()};
  return fingers;
}

} // anonymous namespace

CFingerLayoutView::CFingerLayoutView(QWidget* parent)
    : FingerLayoutInput_(
          [this](const CFingerLayoutState& State) { drawState(State); }),
      Window_(new QMainWindow(parent)), CentralWidget_(new QWidget(Window_)) {

  Window_->setWindowTitle("Fingers Layout");
  Window_->setCentralWidget(CentralWidget_);

  buildLayout();
  buildFingerPanel();
  buildActionButtons();

  using namespace NSCoordinates::LayoutConstants;

  const int panelW = 5 * FINGER_BTN_W + HAND_GAP + 5 * FINGER_BTN_W;
  const int kbdW = NSCoordinates::keyboardRightEdge() + WIN_MARGIN;
  const int totalW = std::max(kbdW, panelW + WIN_MARGIN * 2);
  const int totalH = actionRowY() + ACTION_BTN_H + WIN_MARGIN;

  CentralWidget_->setFixedSize(totalW, totalH);
  Window_->adjustSize();
  Window_->setFixedSize(Window_->size());
  Window_->show();
}

CFingerLayoutView::CViewObserver* CFingerLayoutView::getFingerLayoutInput() {
  return &FingerLayoutInput_;
}

const CFingerLayoutView::CButtonsContainer&
CFingerLayoutView::getButtonsContainer() const {
  return ButtonsContainer_;
}

const CFingerLayoutView::CFingersContainer&
CFingerLayoutView::getFingersContainer() const {
  return FingersContainer_;
}

QPushButton* CFingerLayoutView::getOkButton() const {
  return OkButton_;
}
QPushButton* CFingerLayoutView::getResetButton() const {
  return ResetButton_;
}
QPushButton* CFingerLayoutView::getCancelButton() const {
  return CancelButton_;
}

void CFingerLayoutView::closeWindow() {
  Window_->close();
}

void CFingerLayoutView::drawState(const CFingerLayoutState& State) {
  const auto colorMap = defaultFingerColors();
  const QColor unassigned("#d6d6d6");

  for (const auto& [finger, keys] : State.layout) {
    auto colorIt = colorMap.find(finger);
    if (colorIt == colorMap.end())
      continue;
    for (CKeyPosition pos : keys) {
      auto btnIt = ButtonsContainer_.find(pos);
      if (btnIt != ButtonsContainer_.end())
        btnIt->second->setStyleSheet(
            NSViewDetails::keyButtonStyle(colorIt->second).toStyleSheet());
    }
  }

  updateFingerPanel(State.current_finger);
}

void CFingerLayoutView::buildLayout() {
  const auto coordMap = NSCoordinates::createKeyboardLayout();
  const auto labelMap = keyLabels();
  const QColor defaultColor("#d6d6d6");

  for (const auto& [keyPos, rect] : coordMap) {
    auto* btn = new QPushButton(CentralWidget_);
    assert(btn);
    btn->setGeometry(rect);

    auto labelIt = labelMap.find(keyPos);
    if (labelIt != labelMap.end())
      btn->setText(QString::fromUtf8(labelIt->second));

    if (kSkippedButtons.contains(keyPos))
      btn->setDisabled(true);

    btn->setStyleSheet(
        NSViewDetails::keyButtonStyle(defaultColor).toStyleSheet());
    ButtonsContainer_[keyPos] = btn;
  }
}

void CFingerLayoutView::buildFingerPanel() {
  using namespace NSCoordinates::LayoutConstants;

  const auto colorMap = defaultFingerColors();
  const int y = fingerBtnTop(FINGER_BTN_H);

  auto placeFingerGroup = [&](const std::vector<CFinger>& fingers, int x) {
    for (const CFinger& f : fingers) {
      const QColor color =
          colorMap.count(f) ? colorMap.at(f) : QColor("#d6d6d6");
      auto* btn =
          new QPushButton(QString::fromUtf8(fingerLabel(f)), CentralWidget_);
      btn->setGeometry(x, y, FINGER_BTN_W, FINGER_BTN_H);
      btn->setStyleSheet(
          NSViewDetails::fingerButtonStyle(color, false).toStyleSheet());
      FingersContainer_[f] = btn;
      x += FINGER_BTN_W;
    }
    return x;
  };

  int x = fingerPanelStartX();
  x = placeFingerGroup(leftFingers(), x);
  x += HAND_GAP;
  placeFingerGroup(rightFingers(), x);
}

void CFingerLayoutView::updateFingerPanel(CFinger currentFinger) {
  using namespace NSCoordinates::LayoutConstants;

  const auto colorMap = defaultFingerColors();

  auto updateFingerGroup = [&](const std::vector<CFinger>& fingers, int x) {
    for (const CFinger& f : fingers) {
      auto it = FingersContainer_.find(f);
      if (it == FingersContainer_.end()) {
        x += FINGER_BTN_W;
        continue;
      }
      const bool isCurrent = (f.id() == currentFinger.id());
      const int h = isCurrent ? FINGER_BTN_H_SEL : FINGER_BTN_H;
      const QColor color =
          colorMap.count(f) ? colorMap.at(f) : QColor("#d6d6d6");

      it->second->setGeometry(x, fingerBtnTop(h), FINGER_BTN_W, h);
      it->second->setStyleSheet(
          NSViewDetails::fingerButtonStyle(color, isCurrent).toStyleSheet());

      x += FINGER_BTN_W;
    }
    return x;
  };

  int x = fingerPanelStartX();
  x = updateFingerGroup(leftFingers(), x);
  x += HAND_GAP;
  updateFingerGroup(rightFingers(), x);
}

void CFingerLayoutView::buildActionButtons() {
  using namespace NSCoordinates::LayoutConstants;

  const int y = actionRowY();
  const int rightEdge = NSCoordinates::keyboardRightEdge();
  const int cancelX = rightEdge - ACTION_BTN_W;
  const int resetX = cancelX - ACTION_BTN_GAP - ACTION_BTN_W;
  const int okX = resetX - ACTION_BTN_GAP - ACTION_BTN_W;

  auto makeButton = [&](const char* label, int x, const QColor& bg) {
    auto* btn = new QPushButton(label, CentralWidget_);
    btn->setGeometry(x, y, ACTION_BTN_W, ACTION_BTN_H);
    btn->setStyleSheet(NSViewDetails::actionButtonStyle(bg).toStyleSheet());
    return btn;
  };

  OkButton_ = makeButton("OK", okX, QColor("#d6d6d6"));
  ResetButton_ = makeButton("Reset", resetX, QColor("#d6d6d6"));
  CancelButton_ = makeButton("Cancel", cancelX, QColor("#d6d6d6"));
}

} // namespace NSFingerLayout
} // namespace NSApplication
