#pragma once

namespace NSApplication {
namespace NSKernel {

class CFinger {
public:
  struct EFingerEnum {
    using CType = unsigned char;
    enum : CType {
      Left = 0,
      Right = 8,
      Thumb = 0,
      Index = 1,
      Middle = 2,
      Ring = 3,
      Pinky = 4,
      Undefined = 128,
      HandMask = 8,
      FingerMask = 7,
    };
  };
  using EFinger = EFingerEnum::CType;

  CFinger() = default;

  static CFinger LeftThumb();
  static CFinger LeftIndex();
  static CFinger LeftMiddle();
  static CFinger LeftRing();
  static CFinger LeftPinky();
  static CFinger RightThumb();
  static CFinger RightIndex();
  static CFinger RightMiddle();
  static CFinger RightRing();
  static CFinger RightPinky();

  bool isLeftHand() const;
  bool isRightHand() const;

  EFinger id() const;

  struct CLeftHandFirst {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CThumbFirst {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CDirectOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CReverseOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };
  struct CUndefinedLast {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

  struct CLeftReverseRightDirect {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

  struct CStandardOrder {
    static int cmp(CFinger lhs, CFinger rhs);
    bool operator()(CFinger lhs, CFinger rhs) const;
  };

private:
  CFinger(EFinger Finger);

  EFinger Finger_ = EFingerEnum::Undefined;
};

} // namespace NSKernel
} // namespace NSApplication

