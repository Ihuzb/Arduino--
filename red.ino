#include <IRremote.h>
#include <Servo.h>           // 声明调用Servo.h库
Servo myservo;               // 创建一个舵机对象
int pin = 11;
int val = 10;                   //变量val用来存储从模拟口0读到的值
boolean type = false;
IRrecv irrecv(pin);
decode_results results;

void setup() {
  myservo.attach(10);          // 将引脚9上的舵机与声明的舵机对象连接起来
  Serial.begin(9600);
  irrecv.enableIRIn();
  myservo.write(val);               // 给舵机写入角度
}

void loop() {
  //是否接收到解码数据,把接收到的数据存储在变量results中
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xA32AB931) {
      type = !type;
      Serial.println(type);
    }
    if (type) {
      if (val >= 170) {
        val = 170;
      }
      if (val <= 10) {
        val = 10;
      }
      //接收到的数据以16进制的方式在串口输出
      Serial.println(results.value, HEX);
      if (results.value == 0x39D41DC6) {
        val = ++val + 2;
        myservo.write(val);               // 给舵机写入角度
        Serial.println(val);
        delay(15);
      }
      if (results.value == 0xE0984BB6) {
        val = --val - 2;
        myservo.write(val);               // 给舵机写入角度
        Serial.println(val);
        delay(15);
      }
    }
    irrecv.resume();  // 继续等待接收下一组信号
  }
}
