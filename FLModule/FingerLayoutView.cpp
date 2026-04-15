#include "FingerLayoutView.h"
#include "LShapeButton.h"
#include "StyleSheet.h"

#include <qcolor.h>

#include <cassert>

namespace NSApplication {
namespace NSFingers {

namespace {

using CFinger = NSKernel::CFinger;
using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

std::unordered_map<CKeyPosEnum::CType, const char*> keyLabels() {
  return {{CKeyPosEnum::BKSP, "Back"},  {CKeyPosEnum::TAB, "Tab"},
          {CKeyPosEnum::CAPS, "Caps"},  {CKeyPosEnum::RTRN, "Enter"},
          {CKeyPosEnum::LFSH, "Shift"}, {CKeyPosEnum::RTSH, "Shift"},
          {CKeyPosEnum::LCTL, "Ctrl"},  {CKeyPosEnum::RCTL, "Ctrl"}};
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

int CFingerLayoutView::fingerPanelBottom() const {
  return CurrentScheme_.bottom_edge + LayoutScheme_.panel_top_offset +
         LayoutScheme_.finger_btn_h_sel;
}

int CFingerLayoutView::fingerBtnTop(int h) const {
  return fingerPanelBottom() - h;
}

int CFingerLayoutView::fingerPanelStartX() const {
  const int totalPanelW = 5 * LayoutScheme_.finger_btn_w +
                          LayoutScheme_.hand_gap +
                          5 * LayoutScheme_.finger_btn_w;
  const int kbdCenterX =
      (CurrentScheme_.start_x + CurrentScheme_.right_edge) / 2;
  return kbdCenterX - totalPanelW / 2;
}

int CFingerLayoutView::actionRowY() const {
  return fingerPanelBottom() + LayoutScheme_.action_row_offset;
}

CFingerLayoutView::CFingerLayoutView(QMainWindow* window)
    : FingerLayoutInput_(
          [this](const CFingerLayoutState& State) { drawState(State); }),
      Window_(window), CentralWidget_(new QWidget(Window_)) {
  assert(Window_);
  assert(CentralWidget_);
  Window_->setWindowTitle("Fingers Layout");
  Window_->setCentralWidget(CentralWidget_);

  applyScheme(KeyboardType::ANSI);
  buildFingerPanel();
  buildActionButtons();
  buildToggleButtons();

  const int panelW = 5 * LayoutScheme_.finger_btn_w + LayoutScheme_.hand_gap +
                     5 * LayoutScheme_.finger_btn_w;
  const int kbdW = CurrentScheme_.right_edge + LayoutScheme_.win_margin;
  const int totalW = std::max(kbdW, panelW + LayoutScheme_.win_margin * 2);
  const int totalH =
      actionRowY() + LayoutScheme_.action_btn_h + LayoutScheme_.win_margin;

  CentralWidget_->setFixedSize(totalW, totalH);
  Window_->adjustSize();
  Window_->setFixedSize(Window_->size());
  Window_->show();
}

CFingerLayoutView::CViewObserver* CFingerLayoutView::FingerLayoutInput() {
  return &FingerLayoutInput_;
}

void CFingerLayoutView::subscribeToKeyPress(CKeyPressObserver* observer) {
  KeyPressOutput_.subscribe(observer);
}

void CFingerLayoutView::subscribeToFingerChange(CFingerObserver* observer) {
  FingerChangeOutput_.subscribe(observer);
}

void CFingerLayoutView::subscribeToAction(CActionObserver* observer) {
  ActionOutput_.subscribe(observer);
}

void CFingerLayoutView::subscribeToKeyboardType(
    CKeyboardTypeObserver* observer) {
  KeyboardTypeOutput_.subscribe(observer);
}

void CFingerLayoutView::colorKeyButton(CKeyPosition pos, const QColor& color) {
  auto it = ButtonsContainer_.find(pos);
  if (it == ButtonsContainer_.end())
    return;
  if (auto* lbtn = qobject_cast<CLShapeButton*>(it->second))
    lbtn->setBaseColor(color);
  else
    it->second->setStyleSheet(
        NSViewDetails::keyButtonStyle(color).toStyleSheet());
}

void CFingerLayoutView::switchTo(KeyboardType type) {
  applyScheme(type);
  updateToggleButtons();
}

void CFingerLayoutView::updateToggleButtons() {
  const bool iso = (LastState_.keyboard_type == KeyboardType::ISO);
  ANSIButton_->setStyleSheet(
      (!iso ? NSViewDetails::activeLayoutToggleStyle(
                  Palette_.ToggleActiveBg, Palette_.ToggleActiveBorder,
                  Palette_.ToggleActiveText)
            : NSViewDetails::inactiveLayoutToggleStyle(
                  Palette_.ToggleInactiveBg, Palette_.ToggleInactiveBorder,
                  Palette_.ToggleInactiveText))
          .toStyleSheet());
  ISOButton_->setStyleSheet(
      (iso ? NSViewDetails::activeLayoutToggleStyle(Palette_.ToggleActiveBg,
                                                    Palette_.ToggleActiveBorder,
                                                    Palette_.ToggleActiveText)
           : NSViewDetails::inactiveLayoutToggleStyle(
                 Palette_.ToggleInactiveBg, Palette_.ToggleInactiveBorder,
                 Palette_.ToggleInactiveText))
          .toStyleSheet());
}

void CFingerLayoutView::drawLayout(const CLayoutContainer& layout) {
  for (const auto& [finger, keys] : layout) {
    auto colorIt = Palette_.Fingers.find(finger);
    if (colorIt == Palette_.Fingers.end())
      continue;
    for (CKeyPosition pos : keys)
      colorKeyButton(pos, colorIt->second);
  }
}

void CFingerLayoutView::drawState(const CFingerLayoutState& State) {
  const bool layoutChanged = (State.keyboard_type != LastState_.keyboard_type);
  LastState_ = State;
  if (layoutChanged) {
    switchTo(State.keyboard_type);
    for (auto& [pos, btn] : ButtonsContainer_)
      btn->show();
  }
  drawLayout(State.layout);
  updateFingerPanel(State.current_finger);
}

QPushButton* CFingerLayoutView::createKeyButton(CKeyPosEnum::CType keyPos,
                                                const QRect& rect) {
  if (keyPos == CKeyPosEnum::RTRN &&
      CurrentKeyboardType_ == KeyboardType::ISO) {
    auto* lbtn = new CLShapeButton("Enter", CentralWidget_);
    lbtn->setGeometry(rect);
    lbtn->setShape(CurrentScheme_.enter_offset_x, CurrentScheme_.enter_mid_y);
    lbtn->setBaseColor(Palette_.UnassignedKey);
    lbtn->setBorderColor(Palette_.KeyBorder);
    lbtn->setTextColor(Palette_.ButtonText);
    QObject::connect(lbtn, &QPushButton::clicked,
                     [this, keyPos]() { KeyPressOutput_.set(keyPos); });
    return lbtn;
  }

  auto* btn = new QPushButton(CentralWidget_);
  assert(btn);
  btn->setGeometry(rect);

  const auto labels = keyLabels();
  if (auto it = labels.find(keyPos); it != labels.end())
    btn->setText(QString::fromUtf8(it->second));

  if (kSkippedButtons.contains(keyPos)) {
    btn->setDisabled(true);
  } else {
    QObject::connect(btn, &QPushButton::clicked,
                     [this, keyPos]() { KeyPressOutput_.set(keyPos); });
  }
  btn->setStyleSheet(
      NSViewDetails::keyButtonStyle(Palette_.UnassignedKey).toStyleSheet());
  return btn;
}

void CFingerLayoutView::applyScheme(KeyboardType newType) {
  const CKeyboardScheme newScheme =
      (newType == KeyboardType::ISO) ? makeISOScheme() : makeANSIScheme();

  for (auto it = ButtonsContainer_.begin(); it != ButtonsContainer_.end();) {
    if (!newScheme.keys.contains(it->first)) {
      delete it->second;
      it = ButtonsContainer_.erase(it);
    } else {
      ++it;
    }
  }

  const bool rtrnTypeChanged = (CurrentKeyboardType_ != newType);
  CurrentKeyboardType_ = newType;
  CurrentScheme_ = newScheme;

  for (const auto& [keyPos, rect] : CurrentScheme_.keys) {
    auto it = ButtonsContainer_.find(keyPos);
    if (it == ButtonsContainer_.end()) {
      ButtonsContainer_[keyPos] = createKeyButton(keyPos, rect);
      continue;
    }
    if (keyPos == CKeyPosEnum::RTRN && rtrnTypeChanged) {
      delete it->second;
      ButtonsContainer_[keyPos] = createKeyButton(keyPos, rect);
    } else if (it->second->geometry() != rect) {
      it->second->setGeometry(rect);
    }
  }
}

void CFingerLayoutView::buildToggleButtons() {
  constexpr int W = 90;
  constexpr int H = 40;
  const int x = CurrentScheme_.start_x;
  constexpr int y = 10;
  constexpr int gap = 4;

  ANSIButton_ = new QPushButton("ANSI", CentralWidget_);
  ANSIButton_->setGeometry(x, y, W, H);
  ANSIButton_->setStyleSheet(
      NSViewDetails::activeLayoutToggleStyle(Palette_.ToggleActiveBg,
                                             Palette_.ToggleActiveBorder,
                                             Palette_.ToggleActiveText)
          .toStyleSheet());

  ISOButton_ = new QPushButton("ISO", CentralWidget_);
  ISOButton_->setGeometry(x + W + gap, y, W, H);
  ISOButton_->setStyleSheet(
      NSViewDetails::inactiveLayoutToggleStyle(Palette_.ToggleInactiveBg,
                                               Palette_.ToggleInactiveBorder,
                                               Palette_.ToggleInactiveText)
          .toStyleSheet());

  QObject::connect(ANSIButton_, &QPushButton::clicked,
                   [this]() { KeyboardTypeOutput_.set(KeyboardType::ANSI); });
  QObject::connect(ISOButton_, &QPushButton::clicked,
                   [this]() { KeyboardTypeOutput_.set(KeyboardType::ISO); });
}

int CFingerLayoutView::placeFingerGroup(
    const std::vector<CFinger>& fingers, int x, int y,
    const CFingerLayoutPalette::CFingerColorMap& colorMap) {
  for (const CFinger& f : fingers) {
    const QColor color =
        colorMap.count(f) ? colorMap.at(f) : Palette_.UnassignedKey;
    auto* btn = new QPushButton(CentralWidget_);
    assert(btn);
    btn->setGeometry(x, y, LayoutScheme_.finger_btn_w,
                     LayoutScheme_.finger_btn_h);
    btn->setStyleSheet(NSViewDetails::fingerButtonStyle(
                           color, Palette_.FingerBorderInactive, 1, false)
                           .toStyleSheet());
    QObject::connect(btn, &QPushButton::clicked,
                     [this, f]() { FingerChangeOutput_.set(f); });
    FingersContainer_[f] = btn;
    x += LayoutScheme_.finger_btn_w;
  }
  return x;
}

void CFingerLayoutView::buildFingerPanel() {
  const int y = fingerBtnTop(LayoutScheme_.finger_btn_h);

  int x = fingerPanelStartX();
  x = placeFingerGroup(leftFingers(), x, y, Palette_.Fingers);
  x += LayoutScheme_.hand_gap;
  placeFingerGroup(rightFingers(), x, y, Palette_.Fingers);
}

void CFingerLayoutView::updateFingerPanel(CFinger currentFinger) {
  auto updateFingerGroup = [&](const std::vector<CFinger>& fingers, int x) {
    for (const CFinger& f : fingers) {
      auto it = FingersContainer_.find(f);
      if (it == FingersContainer_.end()) {
        x += LayoutScheme_.finger_btn_w;
        continue;
      }
      const bool isCurrent = (f.id() == currentFinger.id());
      const int h = isCurrent ? LayoutScheme_.finger_btn_h_sel
                              : LayoutScheme_.finger_btn_h;
      const QColor color = Palette_.Fingers.count(f) ? Palette_.Fingers.at(f)
                                                     : Palette_.UnassignedKey;
      const QColor border = isCurrent ? Palette_.FingerBorderActive
                                      : Palette_.FingerBorderInactive;
      const int bw = isCurrent ? 2 : 1;

      it->second->setGeometry(x, fingerBtnTop(h), LayoutScheme_.finger_btn_w,
                              h);
      it->second->setStyleSheet(
          NSViewDetails::fingerButtonStyle(color, border, bw, isCurrent)
              .toStyleSheet());

      x += LayoutScheme_.finger_btn_w;
    }
    return x;
  };

  int x = fingerPanelStartX();
  x = updateFingerGroup(leftFingers(), x);
  x += LayoutScheme_.hand_gap;
  updateFingerGroup(rightFingers(), x);
}

void CFingerLayoutView::buildActionButtons() {
  const int y = actionRowY();
  const int rightEdge = CurrentScheme_.right_edge;
  const int cancelX = rightEdge - LayoutScheme_.action_btn_w;
  const int resetX =
      cancelX - LayoutScheme_.action_btn_gap - LayoutScheme_.action_btn_w;
  const int okX =
      resetX - LayoutScheme_.action_btn_gap - LayoutScheme_.action_btn_w;

  OkButton_ = makeActionButton("OK", okX, y, Palette_.UnassignedKey);
  ResetButton_ = makeActionButton("Reset", resetX, y, Palette_.UnassignedKey);
  CancelButton_ =
      makeActionButton("Cancel", cancelX, y, Palette_.UnassignedKey);

  QObject::connect(OkButton_, &QPushButton::clicked,
                   [this]() { ActionOutput_.set(EFingerLayoutAction::Ok); });
  QObject::connect(ResetButton_, &QPushButton::clicked,
                   [this]() { ActionOutput_.set(EFingerLayoutAction::Reset); });
  QObject::connect(CancelButton_, &QPushButton::clicked, Window_,
                   &QMainWindow::close);
}

QPushButton* CFingerLayoutView::makeActionButton(const char* label, int x,
                                                 int y, const QColor& bg) {
  auto* btn = new QPushButton(label, CentralWidget_);
  assert(btn);
  btn->setGeometry(x, y, LayoutScheme_.action_btn_w,
                   LayoutScheme_.action_btn_h);
  btn->setStyleSheet(NSViewDetails::actionButtonStyle(bg, Palette_.ActionBorder)
                         .toStyleSheet());
  return btn;
}

} // namespace NSFingers
} // namespace NSApplication
