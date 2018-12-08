#include "gamestate.hh"
#include <QString>
#include <QtTest/QtTest>

class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();

private Q_SLOTS:
    void init();
    void setGamePhase();
    void gamephaseOrder();

};

void GameStateTest::setGamePhase() {
    GameState state;
    state.changeGamePhase(Common::GamePhase::SINKING);
    QVERIFY(state.currentGamePhase() == Common::GamePhase::SINKING);
    state.changeGamePhase(Common::GamePhase::SPINNING);
    QVERIFY(state.currentGamePhase() == Common::GamePhase::SPINNING);
    state.changeGamePhase(Common::GamePhase::MOVEMENT);
    QVERIFY(state.currentGamePhase() == Common::GamePhase::MOVEMENT);
}

void GameStateTest::gamephaseOrder() {

}
