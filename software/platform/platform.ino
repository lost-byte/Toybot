#include <AFMotor.h>
#include <string.h>

#define BUTTON 19

AF_DCMotor motorL(1);
AF_DCMotor motorR(2);

// Программа состоит из инструкций. Каждая инструкция это код+аргумент.
// Коды: f,b,r,l - вперед, назад, вправо, влево

// Область программы
#define PRG_SIZE 100
unsigned short prg[PRG_SIZE];
char prgLen = 0;
char prgCursor = 0;

const char prgDict[][16]={
  "",
  "вперед",
  "назад",
  "налево",
  "направо"
};

bool cmdEntered = false;
bool argEntered = false;
char argBuf[4] = {0,0,0,0};
char argBufPtr = 0;
char prgCode = 0;

const char delStrSeq[] = {0x1B,(char)0x9B,'2','K',0x0D,0x0A};
//PROGMEM const char clrScrSeq[] = {0x1B,(char)0x9B,'2','J',0x0A};
//PROGMEM const char curDown[] = {0x1B,'F'};



void delStr(){
  Serial.write(delStrSeq,strlen(delStrSeq));
}

void delSym(){
  Serial.write(0x08);
}

/*
void clrScr(){
  Serial.write(clrScrSeq,sizeof(clrScrSeq));
  Serial.write(curDown,sizeof(curDown));
}
*/

void printPrompt(){
  Serial.print(">:");
}

void printHelp() {
  Serial.println("Редактирование:");
  Serial.println("p - напечатать программу");
  Serial.println("d - удалить строку за курсором");
  Serial.println("i - вставить строку после курсора");
  Serial.println("Справочник инструкций:");
  Serial.println("f NN(0-255) - движение вперед NN шагов");
  Serial.println("b NN(0-255) - движение назад NN шагов");
  Serial.println("r NN(1-3) - разворот по часовой на 90,180,270 градусов");
  Serial.println("l NN(1-3) - разворот против часовой на 90,180,270 градусов");
}

void clearPrg(){
  memset(prg,0,PRG_SIZE*2);
}

void printPrg(){
  char pC;
  char pA;
  Serial.print("Текст програмы:");
  Serial.write(0x0D);
  Serial.write(0x0A);
  for (int i=0; i<prgLen; i++){
    pC = (byte) prg[i];
    pA = (byte) (prg[i]>>8);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(prgDict[pC]);
    Serial.print(" ");
    Serial.print(pA,DEC);
    Serial.println(""); 
  }
}

void insertCodeStr(){
  short argI = (byte)atoi(argBuf);
  short prgLine = (prgCode|(argI<<8));
  if (prgLen == prgCursor){
    // Дописывание в конец
    prg[prgCursor] = prgLine;
    prgCursor++;
  }
  prgLen++;
}

bool prgRun = false;
unsigned char prgCnt = 0;

void forward(char times){
  motorL.run(FORWARD);
  motorR.run(FORWARD);
  delay(1000*times);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void backward(char times){
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
  delay(1000*times);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void left(char times){
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
  delay(500*times);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void right(char times){
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
  delay(500*times);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void prgRunStep(){
  char pC = prg[prgCnt];
  char pA = (prg[prgCnt]>>8);
  switch(pC){
    case 1:
      forward(pA);
      break;
    case 2:
      backward(pA);
      break;
    case 3:
      left(pA);
      break;
    case 4:
      right(pA);
      break;
  }
  prgCnt++;
  if (prgCnt>prgLen){
    prgCnt = 0;
    prgRun = false;
  }
}

void setup() {
  pinMode(BUTTON,INPUT_PULLUP);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  //clrScr();
  printHelp();
  printPrompt();

  motorR.setSpeed(200);
  motorR.run(RELEASE);
  motorL.setSpeed(200);
  motorL.run(RELEASE);
}


void loop() {
  char key;
  if (!prgRun){
    // Командный процессор
    if(Serial.available() > 0)
    {
      key = Serial.read();
      switch(key)
      {
      case 'h':    
        printHelp();
        printPrompt();
        break;
      case 'p':
        printPrg();
        printPrompt();
        break;    
      case 'f':
        Serial.print("вперед ");
        cmdEntered = true;
        prgCode = 1;
        break;
      case 'b':
        Serial.print("назад ");
        cmdEntered = true;
        prgCode = 2;
        break;
      case 'r':
        Serial.print("направо ");
        cmdEntered = true;
        prgCode = 4;
        break;
      case 'l':
        Serial.print("налево ");
        cmdEntered = true;
        prgCode = 3;
        break;
      case 'g':
        prgRun = true;
        break;
      case 0xD:
        //Enter
        if (argEntered){
          insertCodeStr();
          argBufPtr = 0;
          prgCode = 0;
          argBufPtr = 0;
          cmdEntered = false;
          argEntered = false;
          Serial.println("");
          printPrg();
          Serial.println("");
          printPrompt();
        }
        break;
      case 0x7F:
        // BackSpace
        Serial.write(delStrSeq,strlen(delStrSeq));
        printPrompt();
        cmdEntered = false;
        argEntered = false;
        break;
      case 0x41:
        //up
        break;
      case 0x42:
        //down
        break;
      default:
        if ((0x30<key)&&(0x39>key)){
          // вводится число. 
          if (cmdEntered){
             argBuf[argBufPtr] = key;
             argBufPtr++;
             Serial.print(key);
             argEntered = true;
          }
        }else{
          //Serial.print("KeyCode:");
          //Serial.println(key,HEX);
        }
        
      } 
    }
    if (digitalRead(BUTTON)==0){
      prgRun = true;
    }
  }else{
    /// Исполнение программы
    prgRunStep();
    if(Serial.available() > 0){
      //key = Serial.read();
      // При любом нажатии остановить
      prgCnt = 0;
      prgRun = false;
    }

        
        
  }
}
