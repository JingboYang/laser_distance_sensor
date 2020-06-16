#include <SoftwareSerial.h> // Soft string oral document

SoftwareSerial Serial1(2, 3); // Define the name of the soft serial port Serial1，and pin2 is defined as RX，pin3 is designated as TX /* For Arduino boards with multiple serial ports, such as DUE boards，comment out the above two pieces of code and use Serial 1 serial port directly. */ int dist;// Distance LiDAR detected

int i;

int check;    //Check the stored data
int uart[9];             //Store LiDAR detected data

int strength; //LiDAR signal intensity，which is implausible if the data is under 100
int dist;
float temprature;

const int HEADER = 0x59; // pockets frame header
const int SERIAL_PLOTTER = 1; // Change to 1 to use Arduino IDE's Serial Plotter

void setup()
{
    Serial.begin(115200);  // Set Baud Rate of Connecting Serial Port of Arduino and Computer
    Serial1.begin(115200); //Set Baud Rate of Connecting Serial Port of Arduino and LiDAR
}

void loop()
{

    if (Serial1.available()) //Check SATA have data input or not
    {
        if (Serial1.read() == HEADER) // Decide pockets frame header 0x59
        {
            uart[0] = HEADER;
            if (Serial1.read() == HEADER) //Decide pockets frame header 0x59
            {
                uart[1] = HEADER;
                for (i = 2; i < 9; i++) //Store the data into array
                {
                    uart[i] = Serial1.read();
                }

                check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
                if (uart[8] == (check & 0xff)) //Check the received number following the agreement
                {
                    dist = uart[2] + uart[3] * 256; //calculate the distance
                    strength = uart[4] + uart[5] * 256; //]calculate intensity of the signal
                    temprature = uart[6] + uart[7] *256;//calculate chip temprature                    
                    temprature = temprature / 8 - 256;
                }

                // Print to serial for human reading
                if (SERIAL_PLOTTER == 0){
                  Serial.print('\t');
                  Serial.print("Dist=");
                  Serial.print(dist);//Output LiDAR detected distance
                  Serial.print('\t');
                  Serial.print("Signal Strength=");
                  Serial.print(strength);//Intensity of the output signal
                  Serial.print('\t');
                  Serial.print("Chip Temprature=");
                  Serial.print(temprature);
                  Serial.println();
                }
                // Print to serial for Serial Plotter
                else {
                  Serial.print(dist);//Output LiDAR detected distance
                  Serial.print(' ');
                  Serial.print(strength);//Intensity of the output signal
                  Serial.print(' ');
                  Serial.print(temprature); 
                  Serial.println();
                }
                
            }
        }
    }
}
