#include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define PARSE_AMOUNT 5       // число значений в массиве, который хотим получить
#define INPUT_AMOUNT 80      // максимальное количество символов в пакете, который идёт в сериал
char inputData[INPUT_AMOUNT];  // массив входных значений (СИМВОЛЫ)
int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
boolean getStarted;
byte index;
String string_convert;

void setup() 
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);
}


void parsing() {
  while (Serial.available() > 0) {
    char incomingByte = Serial.read();      // обязательно ЧИТАЕМ входящий символ
    if (incomingByte == '$') {              // если это $
      getStarted = true;                    // поднимаем флаг, что можно парсить
    } else if (incomingByte != ';' && getStarted) { // пока это не ;
      // в общем происходит всякая магия, парсинг осуществляется функцией strtok_r
      inputData[index] = incomingByte;
      index++;
      inputData[index] = NULL;
    } else {
      if (getStarted) {
        char *p = inputData;
        char *str;
        index = 0;
        String value = "";
        while ((str = strtok_r(p, " ", & p)) != NULL) {
          string_convert = str;
          intData[index] = string_convert.toInt();
          index++;
        }
        index = 0;
      }
    }
    if (incomingByte == ';') {        // если таки приняли ; - конец парсинга
      getStarted = false;
      recievedFlag = true;
    }
  }
}

void loop() {
  parsing();       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;

    motor1.setSpeed(abs(intData[1]));
    motor2.setSpeed(abs(intData[2]));
    motor3.setSpeed(abs(intData[3]));
    motor4.setSpeed(abs(intData[4]));

    if (intData[1] > 0) { motor1.run(FORWARD); } else if (intData[1] < 0) { motor1.run(BACKWARD); } else { motor1.run(RELEASE); }
    if (intData[2] > 0) { motor2.run(FORWARD); } else if (intData[2] < 0) { motor2.run(BACKWARD); } else { motor2.run(RELEASE); }
    if (intData[3] > 0) { motor3.run(FORWARD); } else if (intData[3] < 0) { motor3.run(BACKWARD); } else { motor3.run(RELEASE); }
    if (intData[4] > 0) { motor4.run(FORWARD); } else if (intData[4] < 0) { motor4.run(BACKWARD); } else { motor4.run(RELEASE); }

  }
}
  
// uint8_t i;
  
//  Serial.print("tick");
//  
//  motor1.run(FORWARD);
//  motor2.run(FORWARD);
//  motor3.run(FORWARD);
//  motor4.run(FORWARD);
//  for (i=0; i<255; i++) {
//    motor1.setSpeed(i);
//    motor2.setSpeed(i); 
//    motor3.setSpeed(i); 
//    motor4.setSpeed(i); 
//    delay(10);
// }
//
//  Serial.print("tech");
//  motor1.run(RELEASE);
//  motor2.run(RELEASE);
//  motor3.run(RELEASE);
//  motor4.run(RELEASE);
//  delay(1000);
// }
