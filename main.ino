#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

// CONSTANTS
#define PIN 6

#define TRIG 12 
#define ECHO 13 

#define MAX_DISTANCE 20;
#define NUMPIXELS 50;

const unsigned int delta_distance = 20; // the distance between the detector and the led begining
const unsigned int between_diodes = 2;
const unsigned int radius = 50;
// -------------------------------- //

// SET UP
// -------------------------------- //
// colors
vector < int > left_color(3);
vector < int > right_color(3);
vector < int > diffs(3);
vector < int > char_diffs(3);

void set_colors(){
    left_color = {253, 133, 16};
    right_color = {253, 233, 16}; 

    for (int i = 0; i < 3; i++){
        diffs[i] = abs(right_color[i] - left_color[i]) / radius;
        char_diffs[i] = (right_color[i] < left_color[i]) ? 1 : -1;
    }    
}

// distance detector
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);
// adresssed lent obj
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
    Serial.begin(9600); /* устанавливаем скорость порта */

    pixels.begin();

    set_colors();
}
// -------------------------------- //

// MAIN PART
// -------------------------------- //
double get_distance(){
    return sonar.ping_cm();    
}

int get_diode_number(int distance){
    return distance / between_diodes;
}

void light_the_target_area(int diode_number){
    for (int i = 0; i < NUMPIXELS; i++){
        int new_color = {0, 0, 0};

        if (abs(pos - i) <= radius){
            for (int j = 0; j < 3; j++)
                new_color[i] = right_color[j] + abs(pos - i) * char_diffs[j] * diffs[j];
        }

        pixels.setPixelColor(i, pixels.Color(new_color[0], new_color[1], new_color[2]));
    }
}


void loop(){
    double distance_cm = get_distance();
    int target_diode_number = get_diode_number(distance_cm - delta_distance);
    light_the_target_area(target_diode_number);
}
