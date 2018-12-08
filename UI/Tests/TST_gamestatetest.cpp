#include "gamestate.hh"
#include <QString>
#include <QtTest/QtTest>
#include <memory>


class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();

private Q_SLOTS:
    void init();
    void setGamePhase();
    void gamephaseOrder();

    std::shared_ptr<GameState> state_;
};

GameStateTest::GameStateTest(){

}

void GameStateTest::setGamePhase() {
    state_ = std::make_shared<GameState>();
    state_->changeGamePhase(Common::GamePhase::SINKING);
    QVERIFY(state_->currentGamePhase() == Common::GamePhase::SINKING);
    state_->changeGamePhase(Common::GamePhase::SPINNING);
    QVERIFY(state_->currentGamePhase() == Common::GamePhase::SPINNING);
    state_->changeGamePhase(Common::GamePhase::MOVEMENT);
    QVERIFY(state_->currentGamePhase() == Common::GamePhase::MOVEMENT);
}

void GameStateTest::gamephaseOrder() {

}

QTEST_APPLESS_MAIN(GameStateTest)

