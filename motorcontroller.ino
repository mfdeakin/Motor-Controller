
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
  if(Serial.available() > 0) {
    byte in = Serial.read();
    Serial.print("Recieved from S: ");
    Serial.println(in, DEC);
  }
  if(Serial1.available() > 0) {
    byte in = Serial1.read();
    Serial.print("Recieved from S1: ");
    Serial.println(in, DEC);
  }
  if(Serial2.available() > 0) {
    byte in = Serial2.read();
    Serial.print("Recieved from S2: ");
    Serial.println(in, DEC);
  }
  if(Serial3.available() > 0) {
    byte in = Serial3.read();
    Serial.print("Recieved from S3: ");
    Serial.println(in, DEC);
  }
  static int state = 0;
//  Serial.write('a');
  if(state) {
    writeString("!A7F\r\n");
  }
  else {
    writeString("!A40\r\n");
  }
  delay(500);
  state = !state;
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
