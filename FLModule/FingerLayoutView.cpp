#include "FingerLayoutView.h"
#include "Coordinates.h"
#include <cassert>

namespace NSApplication {
namespace NSFingerLayout {

namespace NSViewDetails {
using CFinger = NSKernel::CFinger;

inline std::map<CFinger, QColor, CFinger::CStandardOrder>
createDefaultFingerColors() {
  return {
      {CFinger().LeftPinky(), QColor("#FFB3BA")}, // Светло-розовый
      {CFinger().LeftRing(), QColor("#FFDFBA")}, // Светло-персиковый
      {CFinger().LeftMiddle(), QColor("#FFFFBA")}, // Светло-жёлтый
      {CFinger().LeftIndex(), QColor("#BAFFC9")}, // Светло-зелёный
      {CFinger().LeftThumb(), QColor("#BAE1FF")}, // Светло-голубой
      {CFinger().RightThumb(), QColor("#BAE1FF")}, // Светло-голубой
      {CFinger().RightIndex(), QColor("#BAFFC9")}, // Светло-зелёный
      {CFinger().RightMiddle(), QColor("#FFFFBA")}, // Светло-жёлтый
      {CFinger().RightRing(), QColor("#FFDFBA")}, // Светло-персиковый
      {CFinger().RightPinky(), QColor("#FFB3BA")}, // Светло-розовый
  };
}

inline std::unordered_map<CKeyPosEnum::CType, const char*> createKeyLabels() {
  return {
      {CKeyPosEnum::BKSP, "Back"},  {CKeyPosEnum::TAB, "Tab"},
      {CKeyPosEnum::CAPS, "Caps"},  {CKeyPosEnum::RTRN, "Enter"},
      {CKeyPosEnum::LFSH, "Shift"}, {CKeyPosEnum::RTSH, "Shift"},
      {CKeyPosEnum::LCTL, "Ctrl"},  {CKeyPosEnum::LALT, "Alt"},
      {CKeyPosEnum::RALT, "Alt"},   {CKeyPosEnum::RCTL, "Ctrl"},
  };
}

} // namespace NSViewDetails

CFingerLayoutView::CFingerLayoutView(QWidget* parent)
    : FingerLayoutInput_(
          [this](const CFingerLayoutState& State) { drawState(State); }),
      Window_(new QMainWindow(parent)), CentralWidget_(new QWidget(Window_)) {

  Window_->setWindowTitle("Fingers Layout");
  Window_->setCentralWidget(CentralWidget_);

  buildLayout();

  // CentralWidget_->adjustSize();
  // Window_->adjustSize();
  // Window_->setFixedSize(Window_->sizeHint());

  Window_->show();
}

CFingerLayoutView::CViewObserver* CFingerLayoutView::getFingerLayoutInput() {
  return &FingerLayoutInput_;
}

const CFingerLayoutView::CButtonsContainer&
CFingerLayoutView::getButtonsContainer() const {
  return ButtonsContainer_;
}

void CFingerLayoutView::drawState(const CFingerLayoutState& State) {
  // TODO
}

void CFingerLayoutView::buildLayout() {
  const auto coordMap = NSViewDetails::createCoordinatesKeyboardLayout();
  const auto labelMap = NSViewDetails::createKeyLabels();

  for (const auto& [keyPos, rect] : coordMap) {
    auto* button = new QPushButton(CentralWidget_);
    assert(button);
    button->setGeometry(rect);

    auto labelIt = labelMap.find(keyPos);
    if (labelIt != labelMap.end()) {
      button->setText(QString::fromUtf8(labelIt->second));
    }

    button->setStyleSheet("QPushButton {"
                          "  background-color: #d6d6d6;"
                          "  border: 1px solid #888;"
                          "  border-radius: 4px;"
                          "  font-size: 11px;"
                          "}"
                          "QPushButton:hover {"
                          "  background-color: #c0c0c0;"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: #a0a0a0;"
                          "}");

    ButtonsContainer_[keyPos] = button;
  }
}

void CFingerLayoutView::resetButtonColor(CKeyPosition pos) {
  auto* btn = ButtonsContainer_[pos];

  assert(btn);

  btn->setStyleSheet("QPushButton {"
                     "  background-color: #d6d6d6;"
                     "  border: 1px solid #888;"
                     "  border-radius: 4px;"
                     "  font-size: 11px;"
                     "}"
                     "QPushButton:hover {"
                     "  background-color: #c0c0c0;"
                     "}"
                     "QPushButton:pressed {"
                     "  background-color: #a0a0a0;"
                     "}");
}

} // namespace NSFingerLayout
} // namespace NSApplication
