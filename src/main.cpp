

void setup()
{
// put your setup code here, to run once:
#if (DEBUG_UART == 1)
  Serial.begin(9600);
  DEBUG("start");
#endif
  // епром
  if (EEPROM.read(1000) != 10)
  {
    EEPROM.write(1000, 10);
    EEPROM.put(0, thisVolume);
  }
  EEPROM.EEPROMget(0, thisVolume);

  // тыкаем ленту
  strip.setBrightness(130);
  strip.clear();
  strip.show();
  DEBUG("strip init");

  // настройка пинов помп
  for (byte i = 0; i < PUMP_COUNT; i++)
  {
    pinMode(PUMP_POWER_PINS[i], 1);
  }
  //Настройка пиной для сервопривода
  pinMode(SERVO_POWER, 1);

  for (byte i = 0; i < NUM_SHOTS; i++)
  {
    pinMode(SW_pins[i], INPUT_PULLUP);
  }

  // старт дисплея
  disp.clear();
  disp.brightness(7);
  DEBUG("disp init");

  // настройка серво
  servoON();
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(800);
  servo.setTargetDeg(0);
  servo.setSpeed(60);
  servo.setAccel(0.8);
  servoOFF();

  serviceMode();  // калибровка
  dispMode();     // выводим на дисплей стандартные значения
  timeoutReset(); // сброс таймаута
  TIMEOUTtimer.start();
}

void loop()
{
  // put your main code here, to run repeatedly:

  encTick();
  btnTick();
  flowTick();
  LEDtick();
  timeoutTick();
}