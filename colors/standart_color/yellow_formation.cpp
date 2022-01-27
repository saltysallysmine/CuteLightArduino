#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define NUMPIXELS 100

using namespace std;

int pos = 50;
int radius = 50;

int main(){
    vector < int > finish_color = {253, 133, 16};
    vector < int > start_color = {253, 233, 16};

    vector < int > diffs(3);
    for (int i = 0; i < 3; i++)
        diffs[i] = abs(start_color[i] - finish_color[i]) / radius;
    vector < int > char_diffs(3);
    for (int i = 0; i < 3; i++)
        char_diffs[i] = (start_color[i] < finish_color[i]) ? 1 : -1;


    ofstream file("diodes_colors.txt");
  	
    for (int i = 0; i < NUMPIXELS; i++){
        if (abs(pos - i) <= radius){
            for (int j = 0; j < 3; j++)
                file << start_color[j] + abs(pos - i) * char_diffs[j] * diffs[j] << " ";
                file << endl;
        }
    }

    file.close();
}
