/*
    Name:       reveil_matin.ino
    Created:	05/12/2019 13:07:16
    Author:     Marycha
*/









// The setup() function runs once each time the micro-controller starts
void setup()
{
    Serial.begin(9600);


}

// Add the main program code into the continuous loop() function
void loop()
{
    Serial.println((millis() / 1000) / 60);
    delay(120000);
    Serial.print("Apres le delais");
}
