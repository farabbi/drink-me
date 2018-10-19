/* Drink Me
 *  by Jiuxin Zhu and Edanur Kuntman, Oct 19, 2018
 */

import processing.serial.*;
import processing.sound.*;

Serial myPort;

// soundfiles
SoundFile f1;
SoundFile f2;
SoundFile f3;
SoundFile f4;
SoundFile f5;
SoundFile f6;
SoundFile f7;
SoundFile f8;
SoundFile theme;

int soundfile = 1;
int xpos = 0;
float val = 0;
boolean is_playing = false;
long finish_time = 0;

void setup() {
  size(400, 300);
  
  // set the serial port
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  // don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('\n');
  
  // load soundfiles from the data folder
  f1 = new SoundFile(this, "f1.wav");
  f2 = new SoundFile(this, "f2.wav");
  f3 = new SoundFile(this, "f3.wav");
  f4 = new SoundFile(this, "f4.wav");
  f5 = new SoundFile(this, "f5.wav");
  f6 = new SoundFile(this, "f6.wav");
  f7 = new SoundFile(this, "f7.wav");
  f8 = new SoundFile(this, "f8.wav");
  theme = new SoundFile(this, "theme.wav");
  theme.loop();
  
  background(255);
}

void draw() {
  stroke(0);
  line(xpos, map(val, 0, 1000, 300, 0), xpos, 300);
  xpos = xpos + 1;
  if (xpos >= 400) {
    xpos = 0;
    background(255);
  }
}

void serialEvent(Serial myPort) {
  // get sensor values
  String str = myPort.readStringUntil('\n');
  val = float(str);
  println(val);
  
  // deal with sensor values
  if (val >= 200 || is_playing) {
    theme.stop();
  } else if (!theme.isPlaying()) {
    theme.loop();
  }
  
  if (val >= 1000 && !is_playing) {
    if (soundfile == 1) {
      f1.play();
      finish_time = millis() + (long)(f1.duration() * 1000);
    } else if (soundfile == 2) {
      f2.play();
      finish_time = millis() + (long)(f2.duration() * 1000);
    } else if (soundfile == 3) {
      f3.play();
      finish_time = millis() + (long)(f3.duration() * 1000);
    } else if (soundfile == 4) {
      f4.play();
      finish_time = millis() + (long)(f4.duration() * 1000);
    } else if (soundfile == 5) {
      f5.play();
      finish_time = millis() + (long)(f5.duration() * 1000);
    } else if (soundfile == 6) {
      f6.play();
      finish_time = millis() + (long)(f6.duration() * 1000);
    } else if (soundfile == 7) {
      f7.play();
      finish_time = millis() + (long)(f7.duration() * 1000);
    } else {
      f8.play();
      finish_time = millis() + (long)(f8.duration() * 1000);
    }
    soundfile = soundfile + 1;
    if (soundfile > 8) {
      soundfile = 1;
    }
    is_playing = true;
  }
  
  if (is_playing) {
    if (millis() > finish_time) {
      is_playing = false;
    }
  }
}
