#include "Kernel/Finger.h"

#include <algorithm>
#include <cassert>

namespace NSApplication {
namespace NSKernel {

CFinger CFinger::LeftThumb() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Thumb);
}

CFinger CFinger::LeftIndex() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Index);
}

CFinger CFinger::LeftMiddle() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Middle);
}

CFinger CFinger::LeftRing() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Ring);
}

CFinger CFinger::LeftPinky() {
  return CFinger(EFingerEnum::Left | EFingerEnum::Pinky);
}

CFinger CFinger::RightThumb() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Thumb);
}

CFinger CFinger::RightIndex() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Index);
}

CFinger CFinger::RightMiddle() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Middle);
}

CFinger CFinger::RightRing() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Ring);
}

CFinger CFinger::RightPinky() {
  return CFinger(EFingerEnum::Right | EFingerEnum::Pinky);
}

bool CFinger::isLeftHand() const {
  return (Finger_ & EFingerEnum::HandMask) == EFingerEnum::Left;
}

bool CFinger::isRightHand() const {
  return (Finger_ & EFingerEnum::HandMask) == EFingerEnum::Right;
}

CFinger::EFinger CFinger::id() const {
  return Finger_;
}

CFinger::CFinger(EFinger Finger) : Finger_(Finger) {
}

int CFinger::CLeftHandFirst::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::HandMask) -
         (lhs.Finger_ & EFingerEnum::HandMask);
}

bool CFinger::CLeftHandFirst::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CThumbFirst::cmp(CFinger lhs, CFinger rhs) {
  return std::min((rhs.Finger_ & EFingerEnum::FingerMask), 1) -
         std::min((lhs.Finger_ & EFingerEnum::FingerMask), 1);
}

bool CFinger::CThumbFirst::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CDirectOrder::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::FingerMask) -
         (lhs.Finger_ & EFingerEnum::FingerMask);
}

bool CFinger::CDirectOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CReverseOrder::cmp(CFinger lhs, CFinger rhs) {
  return CDirectOrder::cmp(rhs, lhs);
}

bool CFinger::CReverseOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CUndefinedLast::cmp(CFinger lhs, CFinger rhs) {
  return (rhs.Finger_ & EFingerEnum::Undefined) -
         (lhs.Finger_ & EFingerEnum::Undefined);
}

bool CFinger::CUndefinedLast::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CLeftReverseRightDirect::cmp(CFinger lhs, CFinger rhs) {
  if (CLeftHandFirst::cmp(lhs, rhs) != 0)
    return CLeftHandFirst::cmp(lhs, rhs);
  assert(lhs.isLeftHand() == rhs.isLeftHand());
  assert(lhs.isRightHand() == rhs.isRightHand());
  if (lhs.isLeftHand()) {
    return CReverseOrder::cmp(lhs, rhs);
  } else {
    return CDirectOrder::cmp(lhs, rhs);
  }
}

bool CFinger::CLeftReverseRightDirect::operator()(CFinger lhs,
                                                  CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

int CFinger::CStandardOrder::cmp(CFinger lhs, CFinger rhs) {
  if (CUndefinedLast::cmp(lhs, rhs) != 0)
    return CUndefinedLast::cmp(lhs, rhs);
  if (CThumbFirst::cmp(lhs, rhs) != 0)
    return CThumbFirst::cmp(lhs, rhs);
  if (CLeftHandFirst::cmp(lhs, rhs) != 0)
    return CLeftHandFirst::cmp(lhs, rhs);
  return CLeftReverseRightDirect::cmp(lhs, rhs);
}

bool CFinger::CStandardOrder::operator()(CFinger lhs, CFinger rhs) const {
  return cmp(lhs, rhs) > 0;
}

} // namespace NSKernel
} // namespace NSApplication
