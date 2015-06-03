#define boti 2
#define botd 10
#define bot 11
#define topi 4
#define topd 5
#define top 7
#define mid 8
#define point 12

#define testlet "abcdefghijklmnopqrstuvwxyz"
#define testnum "0123456789"

int numero[10][7] = {
  {top, topi, topd, bot, botd, boti}, // 0
  {topd, botd}, // 1
  {top, topd, mid, boti, bot}, // 2
  {top, bot, mid, topd, botd}, // 3
  {topi, topd, mid, botd}, // 4
  {bot, top, botd, mid, topi}, // 5
  {top, bot, mid, boti, botd, topi}, // 6
  {top, topd, botd}, // 7
  {top, topi, topd, bot, botd, boti, mid}, // 8
  {top, topi, topd, bot, botd, mid}, // 9
};

int letra[26][7] = {
  {top, topi, topd, mid, boti, botd}, // a
  {bot, boti, botd, mid, topi}, // b
  {bot, top, boti, topi}, // c
  {bot, boti, botd, mid, topd}, // d
  {top, mid, bot, topi, boti}, // e
  {boti, topi, top, mid}, // f
  {top, bot, boti, botd, topi, mid}, // g
  {topi, boti, mid, botd}, // h
  {topi, boti}, // i
  {bot, botd, topd}, // j
  
  {topd, boti, mid, botd, top}, // k
  {topi, boti, bot}, // l
  {top, topd, topi, bot}, // m
  {boti, mid, botd}, // n
  {bot, mid, botd, boti}, // o
  {boti, topi, mid, top, topd}, // p
  {top, mid, topd, topi, botd}, // q
  {boti, mid}, // r
  {bot, top, mid, botd, topi}, // s
  {topi, boti, mid, bot}, // t
  
  {topi, boti, bot, topd, botd}, // u
  {topi, topd, bot}, // v
  {topi, topd, mid, bot}, // w
  {topi, topd, boti, botd, mid}, // x
  {topi, topd, mid, bot, botd}, // y
  {top, topd, mid, boti, bot}, // z
};

void writenum (int num){
  for (int i=0; i < sizeof(numero[num])/sizeof(int); i++){
    digitalWrite(numero[num][i], HIGH);
  }
    
}

void writelet (int let, bool mayus){
  if (mayus == false)
    let = let - 'a';
  else
    let = let - 'A';
  
  for (int i=0; i < sizeof(letra[let])/sizeof(int); i++){
    digitalWrite(letra[let][i], HIGH);
  }
    
}

void writestring(String text){
  for (int i=0; i < text.length(); i++){
    clear();
    digitalWrite(point, HIGH);
      if (text[i] >= '0' && text[i] <= '9')
        writenum(text[i] - '0');
      else if (text[i] >= 'A' && text[i] <= 'Z')
        writelet(text[i], true);
      else if (text[i] >= 'a' && text[i] <= 'z')
        writelet(text[i], false);
      
      delay(1000);
  }
  digitalWrite(point, LOW);
}

void clear(){
  for (int i=2; i<14; i++){
    digitalWrite(i, LOW);
  } 

}

void setup() {
  Serial.begin(9600);
  
  pinMode(boti, OUTPUT);
  pinMode(botd, OUTPUT);
  pinMode(bot, OUTPUT);
  pinMode(topi, OUTPUT);
  pinMode(topd, OUTPUT);
  pinMode(top, OUTPUT);
  pinMode(mid, OUTPUT);
  pinMode(point, OUTPUT);

  writenum(0);

}

void loop() { 
  
  String input;
  
  if (Serial.available() > 0){
    input = Serial.readString();
    
    if (input[0] == '/'){
      input.remove(0, 1);
      if (input == "testnum"){
        Serial.println("Running the testnum mode (Printing \"0123456789\" on the display).");
        writestring(testnum);
      }
      else if (input == "testlet"){
        Serial.println("Running the testlet mode (Printing \"abcdefghijklmnopqrstuvwxyz\" on the display).");
        writestring(testlet);
      }
      else if (input == "testall"){
        Serial.println("Running the testall mode (Printing \"0123456789abcdefghijklmnopqrstuvwxyz\" on the display).");
        writestring(testnum);
        writestring(testlet);
      }
      else if (input == "author"){
        Serial.println("Author: Franco Profeti 2do BD");
        writestring("franco profeti 2bd");
      }
      else if (input == "clear"){
        Serial.println("Cleaning screen.");
        clear();
      }
      else if (input == "badmind"){
        Serial.println("Running \"badmind\".");
        clear();
        digitalWrite(mid, HIGH);
        digitalWrite(topd, HIGH);
        digitalWrite(botd, HIGH);        
      }
      else if (input == "snake"){
        Serial.println("Running \"snake demo\".");
        clear();
        int sn[6] = {bot, boti, topi, top, topd, botd};
        for (int a=0; a<4; a++){
          for (int i=0; i<sizeof(sn)/sizeof(int); i++){
          digitalWrite(point, HIGH);
          digitalWrite(sn[i], HIGH);
          delay(300);
          digitalWrite(sn[i], LOW);
          }
        }
        digitalWrite(point, LOW);
      }
      else if (input == "help"){
        Serial.println("### AVAILABLE COMMANDS ###\n\ntestnum\ntestlet\ntestall\nbadmind\nsnake\nauthor\nclear\nhelp\n\n### END ###");
      }
      else{
        Serial.print("Command \""); Serial.print(input); Serial.println("\" not found.");
      }
    }else{
      Serial.print("Printing \""); Serial.print(input); Serial.println("\" on de display.");
      
      writestring(input);
    }
  }
}
