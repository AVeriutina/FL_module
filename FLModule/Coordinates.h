#pragma once

#include "Keyboard/KeyPosition.h"
#include <QRect>

namespace NSApplication {
namespace NSFingerLayout {

namespace NSViewDetails {
using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

namespace KeyboardConstants {
constexpr int KEY_WIDTH = 38; // Стандартная ширина клавиши
constexpr int KEY_HEIGHT = 38; // Стандартная высота клавиши
constexpr int KEY_SPACING = 2;
constexpr int KEY_STEP = KEY_WIDTH + KEY_SPACING;

constexpr int START_X = 91;
constexpr int ROW1_Y = 101;
constexpr int ROW_SPACING = KEY_HEIGHT + KEY_SPACING;

constexpr int ROW2_Y = ROW1_Y + ROW_SPACING; // 141
constexpr int ROW3_Y = ROW2_Y + ROW_SPACING; // 181
constexpr int ROW4_Y = ROW3_Y + ROW_SPACING; // 221
constexpr int ROW5_Y = ROW4_Y + ROW_SPACING; // 261

// Специальные размеры клавиш
constexpr int TAB_WIDTH = 58;
constexpr int CAPS_WIDTH = 68;
constexpr int LSHIFT_WIDTH = 88;
constexpr int BACKSPACE_WIDTH = 78;
constexpr int BACKSLASH_WIDTH = 58;
constexpr int ENTER_WIDTH = LSHIFT_WIDTH;
constexpr int RSHIFT_WIDTH = 108;
constexpr int CTRL_WIDTH = 48;
constexpr int WIN_WIDTH = CTRL_WIDTH;
constexpr int ALT_WIDTH = CTRL_WIDTH;
constexpr int MENU_WIDTH = CTRL_WIDTH;
constexpr int SPACE_WIDTH = 248;
} // namespace KeyboardConstants

// Функция для создания карты расположения клавиш
inline std::unordered_map<CKeyPosEnum::CType, QRect>
createCoordinatesKeyboardLayout() {
  using namespace KeyboardConstants;

  std::unordered_map<CKeyPosEnum::CType, QRect> layout;

  // ========== Ряд 1: Цифры ==========
  int x = START_X;
  int y = ROW1_Y;

  layout[CKeyPosEnum::TLDE] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // ~`
  layout[CKeyPosEnum::AE01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 1
  layout[CKeyPosEnum::AE02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 2
  layout[CKeyPosEnum::AE03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 3
  layout[CKeyPosEnum::AE04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 4
  layout[CKeyPosEnum::AE05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 5
  layout[CKeyPosEnum::AE06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 6
  layout[CKeyPosEnum::AE07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 7
  layout[CKeyPosEnum::AE08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 8
  layout[CKeyPosEnum::AE09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 9
  layout[CKeyPosEnum::AE10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // 0
  layout[CKeyPosEnum::AE11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // -
  layout[CKeyPosEnum::AE12] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // =
  layout[CKeyPosEnum::BKSP] =
      QRect(x, y, BACKSPACE_WIDTH, KEY_HEIGHT); // Backspace

  // ========== Ряд 2: QWERTY ==========
  x = START_X;
  y = ROW2_Y;

  layout[CKeyPosEnum::TAB] = QRect(x, y, TAB_WIDTH, KEY_HEIGHT);
  x += TAB_WIDTH + KEY_SPACING; // Tab
  layout[CKeyPosEnum::AD01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // Q
  layout[CKeyPosEnum::AD02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // W
  layout[CKeyPosEnum::AD03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // E
  layout[CKeyPosEnum::AD04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // R
  layout[CKeyPosEnum::AD05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // T
  layout[CKeyPosEnum::AD06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // Y
  layout[CKeyPosEnum::AD07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // U
  layout[CKeyPosEnum::AD08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // I
  layout[CKeyPosEnum::AD09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // O
  layout[CKeyPosEnum::AD10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // P
  layout[CKeyPosEnum::AD11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // [
  layout[CKeyPosEnum::AD12] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // ]
  layout[CKeyPosEnum::BKSL] =
      QRect(x, y, BACKSLASH_WIDTH, KEY_HEIGHT); // \ (backslash)

  // ========== Ряд 3: ASDFG ==========
  x = START_X;
  y = ROW3_Y;

  layout[CKeyPosEnum::CAPS] = QRect(x, y, CAPS_WIDTH, KEY_HEIGHT);
  x += CAPS_WIDTH + KEY_SPACING; // Caps Lock
  layout[CKeyPosEnum::AC01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // A
  layout[CKeyPosEnum::AC02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // S
  layout[CKeyPosEnum::AC03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // D
  layout[CKeyPosEnum::AC04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // F
  layout[CKeyPosEnum::AC05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // G
  layout[CKeyPosEnum::AC06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // H
  layout[CKeyPosEnum::AC07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // J
  layout[CKeyPosEnum::AC08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // K
  layout[CKeyPosEnum::AC09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // L
  layout[CKeyPosEnum::AC10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // ;
  layout[CKeyPosEnum::AC11] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP;                                                    // '
  layout[CKeyPosEnum::RTRN] = QRect(x, y, ENTER_WIDTH, KEY_HEIGHT); // Enter

  // ========== Ряд 4: ZXCVB ==========
  x = START_X;
  y = ROW4_Y;

  layout[CKeyPosEnum::LFSH] = QRect(x, y, LSHIFT_WIDTH, KEY_HEIGHT);
  x += LSHIFT_WIDTH + KEY_SPACING; // Left Shift
  layout[CKeyPosEnum::AB01] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // Z
  layout[CKeyPosEnum::AB02] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // X
  layout[CKeyPosEnum::AB03] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // C
  layout[CKeyPosEnum::AB04] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // V
  layout[CKeyPosEnum::AB05] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // B
  layout[CKeyPosEnum::AB06] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // N
  layout[CKeyPosEnum::AB07] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // M
  layout[CKeyPosEnum::AB08] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // ,
  layout[CKeyPosEnum::AB09] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // .
  layout[CKeyPosEnum::AB10] = QRect(x, y, KEY_WIDTH, KEY_HEIGHT);
  x += KEY_STEP; // /
  layout[CKeyPosEnum::RTSH] =
      QRect(x, y, RSHIFT_WIDTH, KEY_HEIGHT); // Right Shift

  // ========== Ряд 5: Пробел и модификаторы ==========
  x = START_X;
  y = ROW5_Y;

  layout[CKeyPosEnum::LCTL] = QRect(x, y, CTRL_WIDTH, KEY_HEIGHT);
  x += CTRL_WIDTH + KEY_SPACING; // Left Ctrl
  layout[CKeyPosEnum::LWIN] = QRect(x, y, WIN_WIDTH, KEY_HEIGHT);
  x += WIN_WIDTH + KEY_SPACING; // Left Win
  layout[CKeyPosEnum::LALT] = QRect(x, y, ALT_WIDTH, KEY_HEIGHT);
  x += ALT_WIDTH + KEY_SPACING; // Left Alt
  layout[CKeyPosEnum::SPCE] = QRect(x, y, SPACE_WIDTH, KEY_HEIGHT);
  x += SPACE_WIDTH + KEY_SPACING; // Space
  layout[CKeyPosEnum::RALT] = QRect(x, y, ALT_WIDTH, KEY_HEIGHT);
  x += ALT_WIDTH + KEY_SPACING; // Right Alt
  layout[CKeyPosEnum::RWIN] = QRect(x, y, WIN_WIDTH, KEY_HEIGHT);
  x += WIN_WIDTH + KEY_SPACING; // Right Win
  layout[CKeyPosEnum::MENU] = QRect(x, y, MENU_WIDTH, KEY_HEIGHT);
  x += MENU_WIDTH + KEY_SPACING;                                   // Menu
  layout[CKeyPosEnum::RCTL] = QRect(x, y, CTRL_WIDTH, KEY_HEIGHT); // Right Ctrl

  return layout;
}
} // namespace NSViewDetails
} // namespace NSFingerLayout
} // namespace NSApplication
