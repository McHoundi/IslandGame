#include <QtTest>
#include <gamestate.hh>
#include <player.hh>
#include <iostream>

class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();
    ~GameStateTest();

private slots:
    void initTestCase();
    void test_changeGamePhase();
    void test_falseGamePhaseOrder();
    void test_changeCurrentPlayer();
    void test_NonExistentPlayer();
private:
    std::shared_ptr<GameState> state_;
    std::vector<std::shared_ptr<Common::IPlayer>> testPlayervector_;

};

GameStateTest::GameStateTest()
{
    std::shared_ptr<Common::IPlayer> IPelaaja;
    IPelaaja = std::make_shared<Player>(1001);
    testPlayervector_.push_back(IPelaaja);
    IPelaaja = std::make_shared<Player>(1002);
    testPlayervector_.push_back(IPelaaja);
}

GameStateTest::~GameStateTest()
{

}

void GameStateTest::initTestCase()
{
    state_ = std::make_shared<GameState>();
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::MOVEMENT);
    state_.reset();
}

void GameStateTest::test_changeGamePhase()
{
    state_ = std::make_shared<GameState>();
    state_->changeGamePhase(Common::GamePhase::SINKING);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::SINKING);
    state_->changeGamePhase(Common::GamePhase::SPINNING);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::SPINNING);
    state_->changeGamePhase(Common::GamePhase::MOVEMENT);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::MOVEMENT);
    state_.reset();
}

void GameStateTest::test_falseGamePhaseOrder()
{
    state_ = std::make_shared<GameState>();
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::MOVEMENT);

    state_->changeGamePhase(Common::GamePhase::SPINNING);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::MOVEMENT);

    state_->changeGamePhase(Common::GamePhase::SINKING);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::SINKING);

    state_->changeGamePhase(Common::GamePhase::MOVEMENT);
    QVERIFY(state_->currentGamePhase()==Common::GamePhase::SINKING);

    state_.reset();
}

void GameStateTest::test_changeCurrentPlayer()
{
    auto end = testPlayervector_.end();
    state_ = std::make_shared<GameState>();
    for (auto iter = testPlayervector_.begin(); iter != end; ++iter) {
        state_->addPlayer( (*iter)->getPlayerId() );
        state_->changePlayerTurn( (*iter)->getPlayerId() );
        QVERIFY( state_->currentPlayer() == (*iter)->getPlayerId() );
    }
    state_.reset();
}

void GameStateTest::test_NonExistentPlayer()
{
    int UnknownPlayer = 9999;
    state_ = std::make_shared<GameState>();
    auto end = testPlayervector_.end();
    for (auto iter = testPlayervector_.begin(); iter != end; ++iter) {
        state_->addPlayer( (*iter)->getPlayerId() );
    }
    state_->changePlayerTurn(UnknownPlayer);
    QVERIFY(state_->currentPlayer() != UnknownPlayer);
    state_.reset();
}




QTEST_APPLESS_MAIN(GameStateTest)

#include "tst_gamestatetest.moc"
