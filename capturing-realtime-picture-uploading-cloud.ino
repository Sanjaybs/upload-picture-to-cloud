 
#include <Bridge.h>
#include <Process.h>

Process picture;

String filename;

const int analogPin = A0;    // pin that the sensor is attached to
const int threshold = 555;
//const int pir_pin = 13;

String path = "/mnt/sda1/";
void setup() {

  Bridge.begin();

  //pinMode(pir_pin, OUTPUT);
  Serial.begin(9600);
}
void loop(void)
{ int analogValue = analogRead(analogPin);
  Serial.println(analogValue);
  if (analogValue < threshold) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

  Serial.println(analogValue);
  delay(1000);
  if (digitalRead(13) == true) {

    filename = "";
    picture.runShellCommand("date +%s");
    while (picture.running());
    while (picture.available() > 0) {
      char c = picture.read();
      filename += c;
    }
    filename.trim();
    filename += ".png";
    // Take picture
    picture.runShellCommand("fswebcam " + path + filename + " -r 320x200");
    while (picture.running());
    String cmd = "curl -k <add your url here> -F file=@" + path + filename; // -k allows https without certificate checking
    while (!Serial);

    Serial.println(cmd);
    picture.runShellCommand(cmd);
    while (picture.running());
    Serial.println(picture.exitValue());
  }
  delay(1000);
}
