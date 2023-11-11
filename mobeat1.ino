// Simplified version of the suit with 5 flex sensors and three piezos.
// Each piezo emits sound at a frequency that depends on how the sensors are bent.
//

const int flexPin_1 = A0;			// Pin connected to voltage divider output
const int flexPin_2 = A1;
const int flexPin_3 = A2;
const int flexPin_4 = A3;
const int flexPin_5 = A4;
const int piezo_1 = 6;
const int piezo_2 = 7;
const int piezo_3 = 8;

const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 47000.0;	// resistor used to create a voltage divider
const float flatResistance = 30000.0;	// resistance when flat
const float bendResistance = 70000.0;	// resistance at 90 deg

float Rflex_1 = 0.0;
float Rflex_2 = 0.0;
float Rflex_3 = 0.0;
float Rflex_4 = 0.0;
float Rflex_5 = 0.0;

void setup() {
  Serial.begin(9600);
	pinMode(flexPin_1, INPUT);
  	pinMode(flexPin_2, INPUT);
  	pinMode(flexPin_3, INPUT);
  	pinMode(flexPin_4, INPUT);
  	pinMode(flexPin_5, INPUT);
  	pinMode(piezo_1, OUTPUT);
  	pinMode(piezo_2, OUTPUT);
}

void loop() {
	Rflex_1 = resistenceRead(flexPin_1, "l_elbow");
  	Rflex_2 = resistenceRead(flexPin_2, "l_ribs");
  	Rflex_3 = resistenceRead(flexPin_3, "back");
  	Rflex_4 = resistenceRead(flexPin_4, "r_elbow");
  	Rflex_5 = resistenceRead(flexPin_5, "r_ribs");
  	
  	// plays a tune based on the flex sensor bend degree
  	tone(piezo_1, (Rflex_1+Rflex_2)/500);
  	delay(100);
  	noTone(piezo_1);
  	tone(piezo_2, Rflex_3/250);
  	delay(100);
  	noTone(piezo_2);
  	tone(piezo_3, (Rflex_4+Rflex_5)/500);
  	delay(100);
  	noTone(piezo_3);
  	
}

// calculates the flex sensor resistance
float resistenceRead(int flexPin, char finger[]) {

	int flex_analog = analogRead(flexPin);
	float Voltage_flex = flex_analog * VCC / 1023.0;
	float Res_flex = R_DIV * (VCC / Voltage_flex - 1.0);
	Serial.println("Resistance: " + String(finger) + " " + String(Res_flex) + " ohms");
 
	return Res_flex;
}
