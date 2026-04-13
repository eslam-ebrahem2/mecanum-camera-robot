// ---------- ultrasonic ---------------
void readDistance() {
  float distance = ultrasonic.read(CM);
  if (distance <= 0) {
    return;
  }


  initdist = distance;
}