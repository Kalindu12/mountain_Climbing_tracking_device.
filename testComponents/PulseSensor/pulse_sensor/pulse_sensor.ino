int const PULSE_SENSOR_PIN = 0; //'S' signal pin connected to A0

int Signal = 0;          // store incoming ADC data.value can range from 0 - 1024
int Threshold = 550; // determine which signal to "count as a beat" and which to ingore

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // built-in LED will blink to your heartbeat
    Serial.begin(9600);           // set comm speed for serial plotter window
}
void loop()
{
    Signal = analogRead(PULSE_SENSOR_PIN); // read the sensor value

    Serial.println(Signal) // send the signal value to serial plotter

        if (Signal > Threshold)
    { // if the signal value to serial plotter
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BULTIN, LOW); // else turn off the LED
    }
    delay(10);
}
