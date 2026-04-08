#pragma once

#include "Keyboard/KeyPosition.h"

#include <QRect>

#include <unordered_map>

namespace NSApplication {
namespace NSFingers {
namespace NSCoordinates {

using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

namespace KeyboardConstants {

constexpr int KEY_WIDTH = 95;
constexpr int KEY_HEIGHT = 95;
constexpr int KEY_SPACING = 2;
constexpr int KEY_STEP = KEY_WIDTH + KEY_SPACING;

constexpr int START_X = 10;
constexpr int ROW1_Y = 10;
constexpr int ROW_SPACING = KEY_HEIGHT + KEY_SPACING;

constexpr int ROW2_Y = ROW1_Y + ROW_SPACING;
constexpr int ROW3_Y = ROW2_Y + ROW_SPACING;
constexpr int ROW4_Y = ROW3_Y + ROW_SPACING;
constexpr int ROW5_Y = ROW4_Y + ROW_SPACING;

constexpr int TAB_WIDTH = 140;
constexpr int CAPS_WIDTH = 165;
constexpr int LSHIFT_WIDTH = 213;
constexpr int BACKSPACE_WIDTH = 188;
constexpr int BACKSLASH_WIDTH = 140;
constexpr int ENTER_WIDTH = LSHIFT_WIDTH;
constexpr int RSHIFT_WIDTH = 262;
constexpr int CTRL_WIDTH = 116;
constexpr int WIN_WIDTH = CTRL_WIDTH;
constexpr int ALT_WIDTH = CTRL_WIDTH;
constexpr int MENU_WIDTH = CTRL_WIDTH;
constexpr int SPACE_WIDTH = 623;

} // namespace KeyboardConstants

namespace LayoutConstants {

constexpr int WIN_MARGIN = 30;

constexpr int PANEL_TOP_OFFSET = 20;
constexpr int FINGER_BTN_W = 110;
constexpr int FINGER_BTN_H = 55;
constexpr int FINGER_BTN_H_SEL = 70;
constexpr int HAND_GAP = 16;

constexpr int ACTION_BTN_W = 130;
constexpr int ACTION_BTN_H = 44;
constexpr int ACTION_BTN_GAP = 10;
constexpr int ACTION_ROW_OFFSET = 16;

} // namespace LayoutConstants

inline int keyboardRightEdge() {
  using namespace KeyboardConstants;
  return START_X + CTRL_WIDTH + KEY_SPACING + WIN_WIDTH + KEY_SPACING +
         ALT_WIDTH + KEY_SPACING + SPACE_WIDTH + KEY_SPACING + ALT_WIDTH +
         KEY_SPACING + WIN_WIDTH + KEY_SPACING + MENU_WIDTH + KEY_SPACING +
         CTRL_WIDTH;
}

inline int keyboardBottomEdge() {
  using namespace KeyboardConstants;
  return ROW5_Y + KEY_HEIGHT;
}

inline std::unordered_map<CKeyPosEnum::CType, QRect> createKeyboardLayout() {
  using namespace KeyboardConstants;

  std::unordered_map<CKeyPosEnum::CType, QRect> layout;

  int x = START_X;
  int y = ROW1_Y;

  layout[CKeyPosEnum::TLDE] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AE12] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::BKSP] = QRect(x, y, BACKSPACE_WIDTH, KEY_HEIGHT);

  x = START_X;
  y = ROW2_Y;

  layout[CKeyPosEnum::TAB] = QRect(x, y, TAB_WIDTH, KEY_HEIGHT);
  x += TAB_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::AD01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AD12] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::BKSL] = QRect(x, y, BACKSLASH_WIDTH, KEY_HEIGHT);

  x = START_X;
  y = ROW3_Y;

  layout[CKeyPosEnum::CAPS] = QRect(x, y, CAPS_WIDTH, KEY_HEIGHT);
  x += CAPS_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::AC01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AC11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::RTRN] = QRect(x, y, ENTER_WIDTH, KEY_HEIGHT);

  x = START_X;
  y = ROW4_Y;

  layout[CKeyPosEnum::LFSH] = QRect(x, y, LSHIFT_WIDTH, KEY_HEIGHT);
  x += LSHIFT_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::AB01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::AB10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;
  layout[CKeyPosEnum::RTSH] = QRect(x, y, RSHIFT_WIDTH, KEY_HEIGHT);

  x = START_X;
  y = ROW5_Y;

  layout[CKeyPosEnum::LCTL] = QRect(x, y, CTRL_WIDTH, KEY_HEIGHT);
  x += CTRL_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::LWIN] = QRect(x, y, WIN_WIDTH, KEY_HEIGHT);
  x += WIN_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::LALT] = QRect(x, y, ALT_WIDTH, KEY_HEIGHT);
  x += ALT_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::SPCE] = QRect(x, y, SPACE_WIDTH, KEY_HEIGHT);
  x += SPACE_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::RALT] = QRect(x, y, ALT_WIDTH, KEY_HEIGHT);
  x += ALT_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::RWIN] = QRect(x, y, WIN_WIDTH, KEY_HEIGHT);
  x += WIN_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::MENU] = QRect(x, y, MENU_WIDTH, KEY_HEIGHT);
  x += MENU_WIDTH + KEY_SPACING;
  layout[CKeyPosEnum::RCTL] = QRect(x, y, CTRL_WIDTH, KEY_HEIGHT);

  return layout;
}

} // namespace NSCoordinates
} // namespace NSFingers
} // namespace NSApplication
