void readDH() {

  float tt = dht.readTemperature();
  float hh = dht.readHumidity();

  if (isnan(tt)) {

  } else {
    t = tt;
  }
  if (isnan(hh)) {

  } else {
    h = hh;
  }
}
