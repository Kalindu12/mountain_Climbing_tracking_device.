#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{

    mySerial.begin(9600); // Initialize the software serial communication with the GSM module
    Serial.begin(9600);   // Initialize the serial communication with the Arduino IDE serial monitor

    delay(100); // Delay for 100ms
}

void loop()
{

    if (Serial.available() > 0) // Check if there is data available in the serial monitor

        switch (Serial.read()) // Read the input character from the serial monitor
        {

        case 's':          // If the input character is 's'
            SendMessage(); // Call the SendMessage function
            break;

        case 'r': // If the input character is 'r'

            RecieveMessage(); // Call the RecieveMessage function
            break;
        }

    if (mySerial.available() > 0) // Check if there is data available in the software serial buffer

        Serial.write(mySerial.read()); // Read the data from the software serial buffer and send it to the serial monitor
}

void SendMessage()
{

    mySerial.println("AT+CMGF=1"); // Set the GSM module to text mode

    delay(1000); // Delay for 1 second

    // Set the recipient's mobile number
    mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number

    delay(1000); // Delay for 1 second

    mySerial.println("I am SMS from GSM Module"); // Set the message to be sent

    delay(100); // Delay for 100ms

    mySerial.println((char)26); // Send the ASCII code of CTRL+Z to indicate the end of the message

    delay(1000); // Delay for 1 second
}

void RecieveMessage()
{

    mySerial.println("AT+CNMI=2,2,0,0,0"); // Set the GSM module to receive live SMS

    delay(1000); // Delay for 1 second
}
