
// ---------------- motor movement -----------------
// movement {"stop","forward","back","right","left","fright","fleft","bright","bleft"}
void MoveRobot(uint8_t speed, uint8_t dir) {
  switch (dir) {
    case 0:
      stopMotors();
      break;
    case 1:
      if (!warning) {
        forward(speed);
      } else {
        stopMotors();
      }

      break;
    case 2:
      back(speed);
      break;
    case 3:
      Right(speed);
      break;
    case 4:
      left(speed);
      break;
    case 5:
      if (!warning) {
        FRight(speed);
      } else {
        stopMotors();
      }
      break;
    case 6:
      if (!warning) {
        FLeft(speed);
      } else {
        stopMotors();
      }
      break;
    case 7:
      BRight(speed);
      break;
    case 8:
      BLeft(speed);
      break;
  }
}


//=====================================================
void stopMotors() {
  analogWrite(IN3, 0);  // F-W
  analogWrite(IN4, 0);  // F-W
  analogWrite(IN1, 0);  // B-W
  analogWrite(IN2, 0);  // B-W
}

void forward(int speed) {

  analogWrite(IN3, speed);  // F-W
  analogWrite(IN4, 0);      // F-W
  analogWrite(IN1, speed);  // B-W
  analogWrite(IN2, 0);      // B-W
}

void back(int speed) {
  analogWrite(IN3, 0);      // F-W
  analogWrite(IN4, speed);  // F-W
  analogWrite(IN1, 0);      // B-W
  analogWrite(IN2, speed);  // B-W
}

void Right(int speed) {


  analogWrite(IN3, speed);  // F-W
  analogWrite(IN4, 0);      // F-W

  analogWrite(IN1, 0);      // B-W
  analogWrite(IN2, speed);  // B-W
}

void left(int speed) {


  analogWrite(IN3, 0);      // F-W
  analogWrite(IN4, speed);  // F-W
  analogWrite(IN1, speed);  // B-W
  analogWrite(IN2, 0);      // B-W
}

void FRight(int speed) {
  analogWrite(IN3, speed);  // F-W
  analogWrite(IN4, 0);      // F-W
  analogWrite(IN1, 0);      // B-W
  analogWrite(IN2, 0);      // B-W
}

void FLeft(int speed) {

  analogWrite(IN3, 0);      // F-W
  analogWrite(IN4, 0);      // F-W
  analogWrite(IN1, speed);  // B-W
  analogWrite(IN2, 0);      // B-W
}

void BRight(int speed) {
  analogWrite(IN3, 0);      // F-W
  analogWrite(IN4, 0);      // F-W
  analogWrite(IN1, 0);      // B-W
  analogWrite(IN2, speed);  // B-W
}

void BLeft(int speed) {
  analogWrite(IN3, 0);      // F-W
  analogWrite(IN4, speed);  // F-W
  analogWrite(IN1, 0);      // B-W
  analogWrite(IN2, 0);      // B-W
}
