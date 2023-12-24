#include <WiFi.h>
#include <WiFiClient.h>
#include <I2SAudioReceiver.h>
#include <Button.h>

Button testbutton(9);

WiFiClient client;
I2SAudioReceiver i2sAudioReceiver;

void setup()
{
  Serial.begin(115200);
  WiFi.begin("공유기 이름", "공유기 비밀번호");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  i2sAudioReceiver.setWifiClient(client);
  i2sAudioReceiver.setServerAddr("192.168.0.200", 33819); // String ip, int port

  i2sAudioReceiver.setI2sBus(1);                  // 0 or 1
  i2sAudioReceiver.setAudioQuality(16000, 16, 1); // int sample_rate, int sample_size(only 16), int channels(only 1)
  i2sAudioReceiver.setI2sPin(18, 17, 16);         // int sck, int sd, int ws
  i2sAudioReceiver.setDmaBuf(1024, 10);           // int len(only 1024 tested), int count
  i2sAudioReceiver.i2sBegin();
}

void loop()
{
  int state = testbutton.checkState();
  if (state == BUTTON_PRESSED)
  {
    String gptmsg = i2sAudioReceiver.startSteam();
    int err = i2sAudioReceiver.playStreamData();
    if (err == 0)
    {
      Serial.println("성공");
    }
    else
    {
      Serial.println("실패 : 로그 확인");
    }
  }
}
