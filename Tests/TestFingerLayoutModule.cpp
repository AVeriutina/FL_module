#include "FingerLayoutModule.h"
#include "Library/Observer2/Observer.h"

#include <QtTest>

using namespace NSApplication::NSFingers;
using CFinger = NSApplication::NSKernel::CFinger;
using CKeyPosition = NSApplication::NSKeyboard::CKeyPosition;

class FingerLayoutModuleTest : public QObject {
  Q_OBJECT

private slots:
  void testDefaultLayoutInitialState();
  void testSubscribeImmediatelyReceivesState();
  void testChangeCurrentFingerUpdatesState();
  void testChangeButtonMovesKeyToCurrentFinger();
  void testResetRestoresInitialLayout();
  void testObserverNotifiedOnEachStateChange();
};

void FingerLayoutModuleTest::testDefaultLayoutInitialState() {
  CFingerLayoutModule module;
  CFingerLayoutState lastState;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&lastState](const CFingerLayoutState& state) { lastState = state; });
  module.subscribeToFingerLayout(&observer);

  const auto& layout = lastState.layout;
  const std::vector<CFinger> expectedFingers = {
      CFinger::LeftPinky(),  CFinger::LeftRing(),    CFinger::LeftMiddle(),
      CFinger::LeftIndex(),  CFinger::RightThumb(),  CFinger::RightIndex(),
      CFinger::RightMiddle(), CFinger::RightRing(),  CFinger::RightPinky(),
  };
  for (const CFinger& f : expectedFingers) {
    auto it = layout.find(f);
    QVERIFY(it != layout.end());
    QVERIFY(!it->second.empty());
  }
  QCOMPARE(lastState.current_finger.id(), CFinger::LeftPinky().id());
}

void FingerLayoutModuleTest::testSubscribeImmediatelyReceivesState() {
  CFingerLayoutModule module;
  int callCount = 0;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&callCount](const CFingerLayoutState&) { ++callCount; });
  module.subscribeToFingerLayout(&observer);
  QCOMPARE(callCount, 1);
}

void FingerLayoutModuleTest::testChangeCurrentFingerUpdatesState() {
  CFingerLayoutModule module;
  CFingerLayoutState lastState;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&lastState](const CFingerLayoutState& state) { lastState = state; });
  module.subscribeToFingerLayout(&observer);

  module.changeCurrentFinger(CFinger::RightIndex());
  QCOMPARE(lastState.current_finger.id(), CFinger::RightIndex().id());
}

void FingerLayoutModuleTest::testChangeButtonMovesKeyToCurrentFinger() {
  CFingerLayoutModule module;
  CFingerLayoutState lastState;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&lastState](const CFingerLayoutState& state) { lastState = state; });
  module.subscribeToFingerLayout(&observer);

  auto rightIndexIt = lastState.layout.find(CFinger::RightIndex());
  QVERIFY(rightIndexIt != lastState.layout.end());
  QVERIFY(!rightIndexIt->second.empty());
  const CKeyPosition testKey = *rightIndexIt->second.begin();

  module.changeButton(testKey);

  const auto& layout = lastState.layout;
  auto leftPinkyIt = layout.find(CFinger::LeftPinky());
  QVERIFY(leftPinkyIt != layout.end());
  QVERIFY(leftPinkyIt->second.contains(testKey));

  auto rightMiddleIt = layout.find(CFinger::RightMiddle());
  QVERIFY(rightMiddleIt != layout.end());
  QVERIFY(!rightMiddleIt->second.contains(testKey));
}

void FingerLayoutModuleTest::testResetRestoresInitialLayout() {
  CFingerLayoutModule module;
  CFingerLayoutState lastState;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&lastState](const CFingerLayoutState& state) { lastState = state; });
  module.subscribeToFingerLayout(&observer);

  const auto initialLayout = lastState.layout;

  module.changeCurrentFinger(CFinger::RightIndex());
  {
    auto it = lastState.layout.find(CFinger::RightMiddle());
    QVERIFY(it != lastState.layout.end() && !it->second.empty());
    module.changeButton(*it->second.begin());
  }
  {
    auto it = lastState.layout.find(CFinger::RightRing());
    QVERIFY(it != lastState.layout.end() && !it->second.empty());
    module.changeButton(*it->second.begin());
  }

  module.resetLayout();

  QCOMPARE(lastState.layout.size(), initialLayout.size());
  for (const auto& [finger, keys] : initialLayout) {
    auto it = lastState.layout.find(finger);
    QVERIFY(it != lastState.layout.end());
    QVERIFY(it->second == keys);
  }
}

void FingerLayoutModuleTest::testObserverNotifiedOnEachStateChange() {
  CFingerLayoutModule module;
  int callCount = 0;
  CFingerLayoutState lastState;
  NSLibrary::CHotInput<CFingerLayoutState> observer(
      [&callCount, &lastState](const CFingerLayoutState& state) {
        ++callCount;
        lastState = state;
      });
  module.subscribeToFingerLayout(&observer);
  QCOMPARE(callCount, 1);

  module.changeCurrentFinger(CFinger::RightIndex());
  QCOMPARE(callCount, 2);

  auto it = lastState.layout.find(CFinger::RightMiddle());
  QVERIFY(it != lastState.layout.end() && !it->second.empty());
  module.changeButton(*it->second.begin());
  QCOMPARE(callCount, 3);

  module.resetLayout();
  QCOMPARE(callCount, 4);
}

QTEST_GUILESS_MAIN(FingerLayoutModuleTest)
#include "TestFingerLayoutModule.moc"
