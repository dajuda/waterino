// Water Pump PIN
int waterPump = 12;

// Buoy PIN
int buoy = 3;

// Buoy Warning PIN
int warningLED = 13;
const long oneHour = 3600000;

void setup() {
    Serial.begin(9600);
    pinMode(waterPump, OUTPUT);
    pinMode(buoy, INPUT);
    pinMode(warningLED, OUTPUT);
}

// Show humidity level
int humidity(){
    int humidityRaw = analogRead(A0); // 1023 to 0 ===> 0 to 100%
    Serial.print("Humidity: ");
    Serial.println(humidityRaw);
    return(map(humidityRaw, 1023, 0, 0, 100));
}

// Verify water level
int waterLevel(){
    int waterLevelRaw = digitalRead(buoy);
    return(waterLevelRaw);
}

// Watering
void watering(){
    while(humidity() < 45){
        Serial.println("humidity under 45%");
        while(!(waterLevel())){
            digitalWrite(waterPump, HIGH);
            Serial.println("Low water in watering");
            blinkLED();
        }
        digitalWrite(waterPump, LOW);
    }
    digitalWrite(waterPump, HIGH);
}

// Blink warning LED
void blinkLED(){
    digitalWrite(warningLED, HIGH);
    delay(200);
    digitalWrite(warningLED, LOW);
    delay(200);
}

void loop(){
    digitalWrite(waterPump, HIGH);
    if(humidity() < 45 && waterLevel()){
        watering();
    }
    while(!(waterLevel())){
        Serial.println("Low water");
        blinkLED();
    }
    delay(12*oneHour);
}
