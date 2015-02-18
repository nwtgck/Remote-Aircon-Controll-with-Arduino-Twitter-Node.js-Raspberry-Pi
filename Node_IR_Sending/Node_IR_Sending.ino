#define SIGNAL_LEN 265

#define LEADER_HIGH 3450
#define LEADER_LOW 1580
#define DATA_HEAD 466
#define DATA_TAIL_HIGH 360
#define DATA_TAIL_LOW 1200

#define IR_OUT 2
#define LED 10

bool signal[SIGNAL_LEN];
 
// セットアップ
void setup() {
  pinMode(IR_OUT, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // シグナルが来るまで待機
   receiveSignal();
   // シグナルを送信
   digitalWrite(LED, HIGH);
   sendSignal();
   digitalWrite(LED, LOW);
}

/*
  dataからリモコン信号を送信
*/
void sendSignal() {
  // leader部
  on(LEADER_HIGH);
  PORTD &= ~_BV(IR_OUT);
  delayMicroseconds(LEADER_LOW);
  
  for (int cnt = 0; cnt < SIGNAL_LEN; cnt++) {
    on(DATA_HEAD);
    PORTD &= ~_BV(IR_OUT);
    if(signal[cnt] == 1){
      delayMicroseconds(DATA_TAIL_HIGH); 
    } else {
     delayMicroseconds(DATA_TAIL_LOW); 
    }
  }
  
  Serial.println("sent");
}

/*
  38kHzでon, offを切り替える
*/
void on(unsigned long len){
    unsigned long us = micros();
    do {
      PORTD |= _BV(IR_OUT); // 高速なdigitalWrite()
      delayMicroseconds(13);  // キャリア周波数38kHzでON/OFFするよう時間調整
      PORTD &= ~_BV(IR_OUT);
      delayMicroseconds(13);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
} 
 
/*
  シリアルポートからシグナルを読み取りsignal配列に格納する
*/
void receiveSignal(){
   int signal_cnt = 0;
   // シグナルがすべて読み込まれるまで待ち続ける
   while(signal_cnt < SIGNAL_LEN){
     // 1バイトのデータが届いて時
     if(Serial.available() > 0){
       unsigned char c = Serial.read();
       // 1バイトのデータを1bitごとに分けて、signal配列に格納
       for(int i = 0; i < 8 && signal_cnt < SIGNAL_LEN; i++){
         signal[signal_cnt++] = (c & 128) != 0;
         c <<= 1;
       }
     }
   }
}

