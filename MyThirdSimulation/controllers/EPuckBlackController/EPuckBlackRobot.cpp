#include "EPuckBlackRobot.hpp"

EPuckBlackRobot::EPuckBlackRobot() : mState {State::roam} {}

void EPuckBlackRobot::backward() {
  const double speedScale {0.5};
  mLeftSpeed = -speedScale * MAX_SPEED;
  mRightSpeed = -speedScale * MAX_SPEED;
  mLeftMotor->setVelocity(mLeftSpeed);
  mRightMotor->setVelocity(mRightSpeed);
}

void EPuckBlackRobot::run() {
  while(step(TIME_STEP) != -1) {
    std::string msg {receiveMessage()};
    if(msg == "Backward") {
      // change state to move backward
      mState = State::backward;
    } else if(msg == "Roam") {
      // change state to roam
      mState = State::roam;
    }
    
    if(mState == State::backward) {
      // move backward
      backward();
    } else if(mState == State::roam) {
      // roam
      roam();
    }
  }
}