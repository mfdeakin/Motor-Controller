
void writeByte(byte b);
void writeString(char *str);

void setup()
{
  while(!Serial);
  Serial.begin(9600);
  Serial1.begin(9600);
  writeString("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
  writeString("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
  writeString("\r\r\r\r\r\r\r\r\r\r");
  writeString("\r\r\r\r\r\r\r\r\r\r");
  writeString("\r\r\r\r\r\r\r\r\r\r");
}

void loop()
{
  if(Serial1.available() > 0) {
    while(Serial1.available() > 0) {
      char in = Serial1.read();
      in &= 0x7F;
      Serial.print(in);
    }
    Serial.println("");
  }
  static int state = 0;
  if(state) {
    writeString("!A7F\r\n");
  }
  else {
    writeString("!A40\r\n");
  }
  delay(100);
  readOutput();
  writeString("?a\r\n");
  delay(100);
  readOutput();
  writeString("?v\r\n");
  delay(100);
  readOutput();
  writeString("?e\r\n");
  delay(200);
  readOutput();
  state = !state;
}

/* Black Magic */
void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
        pmc_set_writeprotect(false);
        pmc_enable_periph_clk((uint32_t)irq);
        TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
        uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
        TC_SetRA(tc, channel, rc/2); //50% high, 50% low
        TC_SetRC(tc, channel, rc);
        TC_Start(tc, channel);
        tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
        tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
        NVIC_EnableIRQ(irq);
}

void readOutput()
{
  if(Serial1.available() > 0) {
    while(Serial1.available() > 0) {
      char in = Serial1.read();
      in &= 0x7F;
      Serial.print(in);
    }
    Serial.println("");
  }
}

void writeString(char *str)
{
  for(int i = 0; str[i]; i++) {
    writeByte(str[i]);
  }
}

void writeByte(byte b)
{
  b <<= 1;
  byte parity = 0;
  byte temp = b;
  while(temp) {
    parity ^= temp & 0x80;
    temp <<= 1;
  }
  b = (b >> 1) | parity;
  Serial1.write(b);
}
