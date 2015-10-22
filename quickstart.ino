/*
 * Mike's quickstart  sketch - a complete template to get the LittleBits Arduino working in seconds
 * There's a SANDBOX section below to play with the data 
 * so that you don't have to worry about setting up inputs & outputs. 
 * 
 * by Mike Vladimer 
 * at Orange Silicon Valley http://www.orangesv.com/
 * October 2015
 * 
 * I welcome feedback via twitter: @mikevladimer
 */

// DECLARATIONS
// Tie input variables to pins
const int top_input_pin = 0;
const int middle_input_pin = A0;
const int bottom_input_pin = A1;

// Tie output variables to pins
const int top_output_pin = 1;
const int middle_output_pin = 5;
const int bottom_output_pin  = 9;

// Declare variables to hold data
int top_button = LOW;
int middle_button = LOW;
int bottom_dimmer = 0;
int top_output_value = LOW;
int middle_output_value = LOW;
int bottom_output_value = 0;


// SETUP. Put your setup code here to run once.
void setup() {

  // Configure input and output pins  
  pinMode(top_input_pin, INPUT);
  pinMode(bottom_input_pin, INPUT);
  pinMode(middle_input_pin, INPUT);

  pinMode(top_output_pin, OUTPUT);
  pinMode(middle_output_pin, OUTPUT);
  pinMode(bottom_output_pin, OUTPUT);

  // Set up the serial monitor to see the values in the Arduino in real time. 
  // Note that the serial monitor works with the computer not the d1/tx output pin. 
  // To see the serial monitor feedback, click the spyglass icon in the top right corner of the Arduino IDE.
  Serial.begin(9600);
} // close SETUP


// LOOP. Put your main code here to run repeatedly
void loop() {
  
  // read the state from the input devices. Note when we're using analog read vs. digital read 
  top_button = digitalRead(top_input_pin);          // top input, d0 is digital only (buttons, switches, triggers, etc.) 
  middle_button = digitalRead(middle_input_pin);    // middle input, a0 can be digital (buttons, etc.) or analog (dimmers, sensors, etc.)
  bottom_dimmer =  analogRead(bottom_input_pin);    // bottom input, a1 can be digital (buttons, etc.) or analog (dimmers, sensors, etc.)

  // Print the input values to the serial monitor to see values in real time. Great for debugging! 
  Serial.print( "INPUTS: Top = " + String(top_button) + "  " );
  Serial.print( "Middle = " + String(middle_button) + "  " );
  Serial.print( "Bottom = " + String(bottom_dimmer) + "    " );  

  // Scale the ANALOG INPUTS from Arduino values to LittleBits values
  // Although LittleBits and Arduino both operate on 0 to 5 volts, 
  // Arduino INPUT values go from 0 to 1023 whereas LittleBits values go from 0 to 99
  // This code fixes that problem so that your logic (below) uses LittleBits values going from 0 to 99
  // Here we use the map() function to scale the output to the input https://www.arduino.cc/en/Tutorial/AnalogInOutSerial 
  bottom_dimmer = map(bottom_dimmer,  0, 1023, 0, 99); 


  // ** THE SANDBOX IS HERE! THIS IS THE BEST SECTION OF CODE TO PLAY WITH **
  // Logic. Manipulate the data and have fun!
  // Tip:   The Top and Middle values are digital (1 or 0) whereas Bottom values are analog (0 to 99)
  //        so use digital (AND, OR, NOT...) or analog (+, -, *, ...) logic accordingly. 
  // Functions are listed here: https://www.arduino.cc/en/Reference/HomePage 
  top_output_value = top_button;                  // pass through the top button's digital input 
  middle_output_value = !(middle_button);           // Example of playing with digital data: the output is the NOT of the input
  bottom_output_value = bottom_dimmer;            // pass throught the bottom dimmer's analog input
  // THE SANDBOX ENDS HERE


  // Scale the ANALOG OUTPUTS from LittleBits values to Arduino values
  // Although LittleBits and Arduino both operate on 0 to 5 volts, 
  // Arduino OUTPUT values go from 0 to 255 whereas LittleBits values go from 0 to 99.
  // Previously we scaled from Arduino inputs to LittleBits. 
  // Now we're scaling the outputs -- note that Arduino's input and output scales are different.
  bottom_output_value = map(bottom_output_value,  0, 99, 0, 255);       
    
  // Get output values out to the pins. Note when we're using analog write vs. digital write 
  // Any of the outputs could be digital or analog -- be deliberate about using digitalWrite vs. analogWrite!
  digitalWrite(top_output_pin, top_output_value);           
  digitalWrite(middle_output_pin, middle_output_value);           
  analogWrite(bottom_output_pin, bottom_output_value);      
  
  // Print the output values to the serial monitor to see values in real time. Great for debugging! 
  Serial.print( "OUTPUTS: Top = " + String(top_output_value) + "  " );
  Serial.print( "Middle = " + String(middle_output_value) + "  " );
  Serial.println( "Bottom  = " + String(bottom_output_value) + "  " );  
 
} // end LOOP

