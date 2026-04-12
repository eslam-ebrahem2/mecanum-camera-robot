

// movement {"stop","forward","back","right","left","fright","fleft","bright","bleft","rotateR","rotateL"}

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
    case 9:
      back(speed);
      break;
    case 10:
      forward(speed);
      break;
  }
}



// ================= MOTOR =================





// void stopMotors() {
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, 0);
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, 0);
// }

// void forward(int speed) {
//   ledcWrite(IN1, speed);
//   ledcWrite(IN2, 0);
//   ledcWrite(IN3, speed);
//   ledcWrite(IN4, 0);
// }
// void back(int speed) {
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, speed);
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, speed);
// }

// void Right(int speed) {
//   // w-f-back
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, speed);
//   // w-rr-forward
//   ledcWrite(IN3, speed);
//   ledcWrite(IN4, 0);
// }

// void left(int speed) {
//   // w-f-forward
//   ledcWrite(IN1, speed);
//   ledcWrite(IN2, 0);
//   // w-rr-back
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, speed);
// }

// void FRight(int speed) {
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, 0);
//   ledcWrite(IN3, speed);
//   ledcWrite(IN4, 0);
// }

// void FLeft(int speed) {
//   ledcWrite(IN1, speed);
//   ledcWrite(IN2, 0);
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, 0);
// }

// void BRight(int speed) {
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, speed);
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, 0);
// }

// void BLeft(int speed) {
//   ledcWrite(IN1, 0);
//   ledcWrite(IN2, 0);
//   ledcWrite(IN3, 0);
//   ledcWrite(IN4, speed);
// }

// // ================= SERVO =================
// void setServo(int angle) {
//  angle = constrain(angle, 0, 180);

//   int minDuty = 102;   // 0.5ms
//   int maxDuty = 512;   // 2.5ms

//   int duty = map(angle, 0, 180, minDuty, maxDuty);

//   ledcWriteChannel(SERVO_CHANNEL, duty);
// }


// ================== MOTOR HELPER ==================
void motorWrite(int pinPWM, int channel, int pinLOW, int speed) {
  ledcWriteChannel(channel, speed);
  digitalWrite(pinLOW, LOW);
}

// ================== MOTOR CONTROL ==================
void stopMotors() {
  ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, 0);
  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, 0);
}


void forward(int speed) {
   ledcWriteChannel(CH_IN1, speed);
  ledcWriteChannel(CH_IN2, 0);

  ledcWriteChannel(CH_IN3, speed);
  ledcWriteChannel(CH_IN4, 0);
}

void back(int speed) {
  ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, speed);

  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, speed);
}

void Right(int speed) {
   ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, speed);

  ledcWriteChannel(CH_IN3, speed);
  ledcWriteChannel(CH_IN4, 0);

}

void left(int speed) {
     ledcWriteChannel(CH_IN1, speed);
  ledcWriteChannel(CH_IN2, 0);

  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, speed);

}

void FRight(int speed) {

   ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, 0);

  ledcWriteChannel(CH_IN3, speed);
  ledcWriteChannel(CH_IN4, 0);
}

void FLeft(int speed) {
     ledcWriteChannel(CH_IN1, speed);
  ledcWriteChannel(CH_IN2, 0);

  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, 0);

}

void BRight(int speed) {
     ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, speed);

  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, 0);

}

void BLeft(int speed) {
   ledcWriteChannel(CH_IN1, 0);
  ledcWriteChannel(CH_IN2, 0);

  ledcWriteChannel(CH_IN3, 0);
  ledcWriteChannel(CH_IN4, speed);
}

