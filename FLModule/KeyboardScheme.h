#pragma once

#include "Keyboard/KeyPosition.h"

#include <QRect>

#include <unordered_map>

namespace NSApplication {
namespace NSFingers {

struct CKeyboardScheme {
  using CKeyPosEnum = NSKeyboard::CKeyPosEnum;
  using CKeyMap = std::unordered_map<CKeyPosEnum::CType, QRect>;

  // TODO перенести в KeyPosition.h
  // ISO 102 key code (LSGT key, between LShift and Z — xkb scancode 94).
  static constexpr CKeyPosEnum::CType kISO102Key = 94;

  CKeyMap keys;
  int start_x = 0;
  int right_edge = 0;
  int bottom_edge = 0;

  int enter_offset_x = 0;
  int enter_mid_y = 0;
};

struct CFingerLayoutScheme {
  int win_margin = 30;
  int panel_top_offset = 20;
  int finger_btn_w = 110;
  int finger_btn_h = 55;
  int finger_btn_h_sel = 70;
  int hand_gap = 16;
  int action_btn_w = 130;
  int action_btn_h = 44;
  int action_btn_gap = 10;
  int action_row_offset = 16;
};

namespace NSKeyboardSchemeDetail {

using CKeyPosEnum = NSKeyboard::CKeyPosEnum;

inline constexpr int kKeyWidth = 95;
inline constexpr int kKeyHeight = 95;
inline constexpr int kKeySpacing = 2;
inline constexpr int kKeyStep = kKeyWidth + kKeySpacing;

inline constexpr int kStartX = 10;
inline constexpr int kRow1Y = 60;
inline constexpr int kRowSpacing = kKeyHeight + kKeySpacing;

inline constexpr int kRow2Y = kRow1Y + kRowSpacing;
inline constexpr int kRow3Y = kRow2Y + kRowSpacing;
inline constexpr int kRow4Y = kRow3Y + kRowSpacing;
inline constexpr int kRow5Y = kRow4Y + kRowSpacing;

inline constexpr int kTabWidth = 140;
inline constexpr int kCapsWidth = 165;
inline constexpr int kLShiftWidth = 213;
inline constexpr int kBackspaceWidth = 188;
inline constexpr int kBackslashWidth = 140;
inline constexpr int kEnterWidth = kLShiftWidth;
inline constexpr int kRShiftWidth = 262;
inline constexpr int kCtrlWidth = 116;
inline constexpr int kWinWidth = kCtrlWidth;
inline constexpr int kAltWidth = kCtrlWidth;
inline constexpr int kMenuWidth = kCtrlWidth;
inline constexpr int kSpaceWidth = 623;

inline constexpr int kISOLShiftWidth = kCtrlWidth;
inline constexpr int kISOEnterTopWidth = kBackslashWidth;
inline constexpr int kISOEnterTotalHeight = kKeyHeight * 2 + kKeySpacing;
inline constexpr int kISOEnterOffsetX = 25;
inline constexpr int kISOEnterMidY = kKeyHeight;

inline constexpr int kRightEdge =
    kStartX + kCtrlWidth + kKeySpacing + kWinWidth + kKeySpacing + kAltWidth +
    kKeySpacing + kSpaceWidth + kKeySpacing + kAltWidth + kKeySpacing +
    kWinWidth + kKeySpacing + kMenuWidth + kKeySpacing + kCtrlWidth;

inline constexpr int kBottomEdge = kRow5Y + kKeyHeight;

inline std::unordered_map<CKeyPosEnum::CType, QRect> createCommonKeys() {
  std::unordered_map<CKeyPosEnum::CType, QRect> layout;

  // ── Row 1 ─────────────────────────────────────────────────────────────────
  int x = kStartX;
  int y = kRow1Y;

  layout[CKeyPosEnum::TLDE] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE01] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE02] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE03] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE04] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE05] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE06] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE07] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE08] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE09] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE10] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE11] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AE12] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::BKSP] = QRect(x, y, kBackspaceWidth, kKeyHeight);

  // ── Row 2: TAB + QWERTY (no BKSL, no RTRN) ───────────────────────────────
  x = kStartX;
  y = kRow2Y;

  layout[CKeyPosEnum::TAB] = QRect(x, y, kTabWidth, kKeyHeight);
  x += kTabWidth + kKeySpacing;
  layout[CKeyPosEnum::AD01] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD02] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD03] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD04] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD05] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD06] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD07] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD08] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD09] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD10] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD11] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AD12] = QRect(x, y, kKeyWidth, kKeyHeight);

  // ── Row 3: home row (no BKSL, no RTRN) ───────────────────────────────────
  x = kStartX;
  y = kRow3Y;

  layout[CKeyPosEnum::CAPS] = QRect(x, y, kCapsWidth, kKeyHeight);
  x += kCapsWidth + kKeySpacing;
  layout[CKeyPosEnum::AC01] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC02] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC03] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC04] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC05] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC06] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC07] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC08] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC09] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC10] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AC11] = QRect(x, y, kKeyWidth, kKeyHeight);

  // ── Row 4: bottom row (no LFSH, no ISO_102) ──────────────────────────────
  x = kStartX + kLShiftWidth + kKeySpacing;
  y = kRow4Y;

  layout[CKeyPosEnum::AB01] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB02] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB03] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB04] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB05] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB06] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB07] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB08] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB09] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::AB10] = QRect(x, y, kKeyWidth, kKeyHeight);
  x += kKeyStep;
  layout[CKeyPosEnum::RTSH] = QRect(x, y, kRShiftWidth, kKeyHeight);

  // ── Row 5 ─────────────────────────────────────────────────────────────────
  x = kStartX;
  y = kRow5Y;

  layout[CKeyPosEnum::LCTL] = QRect(x, y, kCtrlWidth, kKeyHeight);
  x += kCtrlWidth + kKeySpacing;
  layout[CKeyPosEnum::LWIN] = QRect(x, y, kWinWidth, kKeyHeight);
  x += kWinWidth + kKeySpacing;
  layout[CKeyPosEnum::LALT] = QRect(x, y, kAltWidth, kKeyHeight);
  x += kAltWidth + kKeySpacing;
  layout[CKeyPosEnum::SPCE] = QRect(x, y, kSpaceWidth, kKeyHeight);
  x += kSpaceWidth + kKeySpacing;
  layout[CKeyPosEnum::RALT] = QRect(x, y, kAltWidth, kKeyHeight);
  x += kAltWidth + kKeySpacing;
  layout[CKeyPosEnum::RWIN] = QRect(x, y, kWinWidth, kKeyHeight);
  x += kWinWidth + kKeySpacing;
  layout[CKeyPosEnum::MENU] = QRect(x, y, kMenuWidth, kKeyHeight);
  x += kMenuWidth + kKeySpacing;
  layout[CKeyPosEnum::RCTL] = QRect(x, y, kCtrlWidth, kKeyHeight);

  return layout;
}

// ANSI-specific keys: BKSL (row 2), RTRN (row 3 standard rect), LFSH (wide).
inline std::unordered_map<CKeyPosEnum::CType, QRect> createANSISpecificKeys() {
  const int bkslX = kStartX + kTabWidth + kKeySpacing + 12 * kKeyStep;
  const int rtrnX = kStartX + kCapsWidth + kKeySpacing + 11 * kKeyStep;

  return {
      {CKeyPosEnum::BKSL, QRect(bkslX, kRow2Y, kBackslashWidth, kKeyHeight)},
      {CKeyPosEnum::RTRN, QRect(rtrnX, kRow3Y, kEnterWidth, kKeyHeight)},
      {CKeyPosEnum::LFSH, QRect(kStartX, kRow4Y, kLShiftWidth, kKeyHeight)},
  };
}

// ISO-specific keys: RTRN (L-shape bounding rect), BKSL (row 3 # key),
// LFSH (narrow), ISO_102.
inline std::unordered_map<CKeyPosEnum::CType, QRect> createISOSpecificKeys() {
  const int rtrnX = kStartX + kTabWidth + kKeySpacing + 12 * kKeyStep;
  const int bkslX = kStartX + kCapsWidth + kKeySpacing + 11 * kKeyStep;
  const int iso102X = kStartX + kISOLShiftWidth + kKeySpacing;

  return {
      {CKeyPosEnum::RTRN,
       QRect(rtrnX, kRow2Y, kISOEnterTopWidth, kISOEnterTotalHeight)},
      {CKeyPosEnum::BKSL, QRect(bkslX, kRow3Y, kKeyWidth, kKeyHeight)},
      {CKeyPosEnum::LFSH, QRect(kStartX, kRow4Y, kISOLShiftWidth, kKeyHeight)},
      {CKeyboardScheme::kISO102Key,
       QRect(iso102X, kRow4Y, kKeyWidth, kKeyHeight)},
  };
}

} // namespace NSKeyboardSchemeDetail

inline CKeyboardScheme makeANSIScheme() {
  using namespace NSKeyboardSchemeDetail;
  CKeyboardScheme s;
  s.keys = createCommonKeys();
  for (auto& [k, v] : createANSISpecificKeys())
    s.keys[k] = v;
  s.start_x = kStartX;
  s.right_edge = kRightEdge;
  s.bottom_edge = kBottomEdge;
  return s;
}

inline CKeyboardScheme makeISOScheme() {
  using namespace NSKeyboardSchemeDetail;
  CKeyboardScheme s;
  s.keys = createCommonKeys();
  for (auto& [k, v] : createISOSpecificKeys())
    s.keys[k] = v;
  s.start_x = kStartX;
  s.right_edge = kRightEdge;
  s.bottom_edge = kBottomEdge;
  s.enter_offset_x = kISOEnterOffsetX;
  s.enter_mid_y = kISOEnterMidY;
  return s;
}

} // namespace NSFingers
} // namespace NSApplication
