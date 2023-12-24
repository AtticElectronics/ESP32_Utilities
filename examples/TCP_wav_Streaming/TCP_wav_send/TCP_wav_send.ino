#include <WiFi.h>
#include <WiFiClient.h>
#include <I2SAudioSender.h>
#include <Button.h>

Button testbutton(9);

WiFiClient client;
I2SAudioSender sendVoice;

void setup()
{
    Serial.begin(115200);
    WiFi.begin("와이파이ssid", "와이파이 비번");
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
    }
}
