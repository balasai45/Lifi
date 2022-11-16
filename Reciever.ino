/*LI-FI Receiver Code 
   Written By Bala Sai
*/
#include <LiquidCrystal.h>
#define SolarCell A0 //To define the input pin of the solarcell
int StCursor = 0; // To control the lcd Cursor
int A[] = {1, 1, 1, 1, 0}, B[] = {0, 0, 0, 1, 0}, C[] = {0, 0, 0, 1, 1}, D[] = {0, 0, 1, 0, 0}, E[] = {0, 0, 1, 0, 1}, F[] = {0, 0, 1, 1, 0}, G[] = {0, 0, 1, 1, 1}, H[] = {0, 1, 0, 0, 0};
int I[] = {0, 1, 0, 0, 1}, J[] = {0, 1, 0, 1, 0}, K[] = {0, 1, 0, 1, 1}, L[] = {0, 1, 1, 0, 0}, M[] = {0, 1, 1, 0, 1}, N[] = {0, 1, 1, 1, 0}, O[] = {0, 1, 1, 1, 1}, P[] = {1, 0, 0, 0, 0};
int Q[] = {1, 0, 0, 0, 1}, R[] = {1, 0, 0, 1, 0}, S[] = {1, 0, 0, 1, 1}, T[] = {1, 0, 1, 0, 0}, U[] = {1, 0, 1, 0, 1}, V[] = {1, 0, 1, 1, 0}, W[] = {1, 0, 1, 1, 1}, X[] = {1, 1, 0, 0, 0};
int Y[] = {1, 1, 0, 0, 1}, Z[] = {1, 1, 0, 1, 0}, SPACE[] = {1, 1, 1, 1, 1};

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int Cell_Input; // The input of the Solar-Cell
int Threshold;
int info[5]; //The received DATA

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  Threshold = analogRead(SolarCell) + 10;
  lcd.print("READY TO RECEIVE");
  delay(5000);
  lcd.clear();

}

void BufferClear() { // The clear the buffer
  for (int i = 0; i < 5; i++) {
    info[i] = 0;
  }
}

void check_condition(int received_bits[5], int Binaryalpha[5], char Lcdalpha) {//To compare the received bits With the data base
  if (received_bits[0] == Binaryalpha[0] && received_bits[1] == Binaryalpha[1] && received_bits[2] == Binaryalpha[2] && received_bits[3] == Binaryalpha[3] && received_bits[4] == Binaryalpha[4]) {
    lcd.print(Lcdalpha);
    CursorControler();
  }
}

void CursorControler() { // To control the cursor
  StCursor++;
  if (StCursor == 16)
    lcd.setCursor(0, 1);
}

void loop() {
  Cell_Input = analogRead(SolarCell);
  if (Cell_Input > Threshold) { // the start bit detection
    delay(10); // timing
    for (int i = 0; i < 5; i++) { // save data
      if (analogRead(SolarCell) > Threshold) {
        info[i] = 1;
      }
      else {
        info[i] = 0;
      }
      delay(10);
    }

    check_condition(info, A, 'A'); check_condition(info, B, 'B'); check_condition(info, C, 'C'); check_condition(info, D, 'D');
    check_condition(info, E, 'E'); check_condition(info, F, 'F'); check_condition(info, G, 'G'); check_condition(info, H, 'H');
    check_condition(info, I, 'I'); check_condition(info, J, 'J'); check_condition(info, K, 'K'); check_condition(info, L, 'L');
    check_condition(info, M, 'M'); check_condition(info, N, 'N'); check_condition(info, O, 'O'); check_condition(info, P, 'P');
    check_condition(info, Q, 'Q'); check_condition(info, R, 'R'); check_condition(info, S, 'S'); check_condition(info, T, 'T');
    check_condition(info, U, 'U'); check_condition(info, V, 'V'); check_condition(info, W, 'W'); check_condition(info, X, 'X');
    check_condition(info, Y, 'Y'); check_condition(info, Z, 'Z'); check_condition(info, SPACE, ' ');
    BufferClear();
  }
}
