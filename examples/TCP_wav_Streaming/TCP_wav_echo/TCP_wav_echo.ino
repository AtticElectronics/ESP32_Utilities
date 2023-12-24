#include <WiFi.h>
#include <WiFiClient.h>
#include <I2SAudioReceiver.h>
#include <I2SAudioSender.h>
#include <Button.h>

Button testbutton(9);

WiFiClient client;
I2SAudioSender sendVoice;
I2SAudioReceiver recvVoice;

void setup()
{
    Serial.begin(115200);
    WiFi.begin("공유기 이름", "공유기 비번");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    sendVoice.setWifiClient(client);
    sendVoice.setServerAddr("192.168.0.200", 33823); // String ip, int port
    sendVoice.setI2sBus(1);                          // 0 or 1
    sendVoice.setAudioQulity(16000, 16, 1);          // int sample_rate, int sample_size, int channels(only 1 tested)
    sendVoice.setI2sPin(8, 19, 20);                  // int sck, int sd, int ws
    sendVoice.setDmaBuf(1024, 6);                    // int len(only 1024 tested), int count
    sendVoice.i2sBegin();

    recvVoice.setWifiClient(client);
    recvVoice.setServerAddr("192.168.0.200", 33819); // String ip, int port
  
    recvVoice.setI2sBus(0);                  // 0 or 1
    recvVoice.setAudioQuality(16000, 16, 1); // int sample_rate, int sample_size(only 16), int channels(only 1)
    recvVoice.setI2sPin(18, 17, 16);         // int sck, int sd, int ws
    recvVoice.setDmaBuf(1024, 10);           // int len(only 1024 tested), int count
    recvVoice.i2sBegin();
}

void loop()
{
    int state = testbutton.checkState();
    if (state == 1)
    {
        sendVoice.openFile();
    }
    else if (state == 2)
    {
        sendVoice.writeData();
        
    }
    else if (state == 3)
    {
        sendVoice.closeFile();
        delay(1000);
        String gptmsg = recvVoice.startSteam();
        int err = recvVoice.playStreamData();
    }
}
