// lock ui

#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button ke1,ke2,ke3,ke4,ke5,ke6,ke7,ke8,ke9,ke0,ke_,ken;

int pixel_x, pixel_y, dig = 0;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void setcurs(int x){
  
while(dig<4){
  if(dig == 0) {tft.setCursor(90,110); return 0;}
  if(dig == 1) {tft.setCursor(112,110); return 0;}
  if(dig == 2) {tft.setCursor(134,110); return 0;}
  if(dig == 3) {tft.setCursor(156,110); return 0;}
}
if(dig>=4){
  tft.fillRect(75, 95, 170, 50, CYAN);
  tft.setCursor(90, 110);
  tft.setTextColor(RED);
  tft.print("LIMIT"); return 0;}
}

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    ke1.initButton(&tft,  100, 190, 50, 50, WHITE, WHITE, BLACK, "1", 2);
    ke2.initButton(&tft,  160, 190, 50, 50, WHITE, WHITE, BLACK, "2", 2);
    ke3.initButton(&tft,  220, 190, 50, 50, WHITE, WHITE, BLACK, "3", 2);
    ke4.initButton(&tft,  100, 250, 50, 50, WHITE, WHITE, BLACK, "4", 2);
    ke5.initButton(&tft,  160, 250, 50, 50, WHITE, WHITE, BLACK, "5", 2);
    ke6.initButton(&tft,  220, 250, 50, 50, WHITE, WHITE, BLACK, "6", 2);
    ke7.initButton(&tft,  100, 310, 50, 50, WHITE, WHITE, BLACK, "7", 2);
    ke8.initButton(&tft,  160, 310, 50, 50, WHITE, WHITE, BLACK, "8", 2);
    ke9.initButton(&tft,  220, 310, 50, 50, WHITE, WHITE, BLACK, "9", 2);
    ken.initButton(&tft,  100, 370, 50, 50, WHITE, WHITE, BLACK, "<", 2);
    ke0.initButton(&tft,  160, 370, 50, 50, WHITE, WHITE, BLACK, "0", 2);
    ke_.initButton(&tft,  220, 370, 50, 50, WHITE, WHITE, BLACK, ">", 2);
    ke1.drawButton(false);
    ke2.drawButton(false);
    ke3.drawButton(false);
    ke4.drawButton(false);
    ke5.drawButton(false);
    ke6.drawButton(false);
    ke7.drawButton(false);
    ke8.drawButton(false);
    ke9.drawButton(false);
    ke0.drawButton(false);
    ke_.drawButton(false);
    ken.drawButton(false);

    tft.fillRect(75, 95, 170, 50, CYAN);
    //tft.setCursor(75, 95);
}
#endif

void loop(){

  bool down = Touch_getXY();
  ke1.press(down && ke1.contains(pixel_x, pixel_y));
  ke2.press(down && ke2.contains(pixel_x, pixel_y));
  ke3.press(down && ke3.contains(pixel_x, pixel_y));
  ke4.press(down && ke4.contains(pixel_x, pixel_y));
  ke5.press(down && ke5.contains(pixel_x, pixel_y));
  ke6.press(down && ke6.contains(pixel_x, pixel_y));
  ke7.press(down && ke7.contains(pixel_x, pixel_y));
  ke8.press(down && ke8.contains(pixel_x, pixel_y));
  ke9.press(down && ke9.contains(pixel_x, pixel_y));
  ke0.press(down && ke0.contains(pixel_x, pixel_y));
  ke_.press(down && ke_.contains(pixel_x, pixel_y));
  ken.press(down && ke_.contains(pixel_x, pixel_y));
  
  if (ke1.justReleased())
        ke1.drawButton();
  if (ke2.justReleased())
        ke2.drawButton();
  if (ke3.justReleased())
        ke3.drawButton();
  if (ke4.justReleased())
        ke4.drawButton();
  if (ke5.justReleased())
        ke5.drawButton();
  if (ke6.justReleased())
        ke6.drawButton();
  if (ke7.justReleased())
        ke7.drawButton();
  if (ke8.justReleased())
        ke8.drawButton();
  if (ke9.justReleased())
        ke9.drawButton();
  if (ke0.justReleased())
        ke0.drawButton();
  if (ke_.justReleased())
        ke_.drawButton();
  if (ken.justReleased())
        ken.drawButton();


  if (ke1.justPressed()) {
        ke1.drawButton(true);
        setcurs(dig);
        tft.setTextColor(RED);
        tft.print("*");
        Serial.print("1");
        dig += 1;
    }
    if (ke2.justPressed()) {
        ke2.drawButton(true);
        setcurs(dig);
        tft.setTextColor(RED);
        tft.print("*");
        Serial.print("2");
        dig += 1;
    }
  
}
