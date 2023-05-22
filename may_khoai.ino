#include <avr/interrupt.h>
long unsigned int count, d = 40, dem = 0;  //d: v, d phải chia hết cho 4 => CHỈNH VẬN TỐC

void setup() {
  DDRH |= 1 << 3;     //6  //PUL
  DDRH &= ~(1 << 4);  //7   //INPUT
  DDRC |= 1 << 7;     //30  //XILANH

  digitalWrite(30, 1);

  // put your setup code here, to run once:
  count = 65535 - d / 4;
  cli();  //tắt ngắt toàn cục

  /* Reset Timer/Counter1 */
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;

  /* Setup Timer/Counter1 */
  // 64/16MHz = 4us
  // T/C1 đếm từ 0 đến 65535
  TCCR1B |= (1 << CS11) | (1 << CS10);  // prescale = 64
  TCNT1 = count;
  TIMSK1 = (1 << TOIE1);  // Overflow interrupt enable
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(7) == 0) {
    digitalWrite(30, 0);
    delay(100);
    digitalWrite(30, 1);
  }
  delay(180);  //delay ngăn đọc liên tiếp - chỉnh chiều dài cắt
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = count;
  PORTH ^= (1 << 3);
}
