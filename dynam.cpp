#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#define NUMPIXELS 100

using namespace std;

int pos = 50;
int radius = 50;

int main(int argc, char *argv[]){
    vector < int > left_color(3), right_color(3);
    if (argc == 1){
        left_color = {253, 133, 16};
        right_color = {253, 233, 16};
    }
    if (argc == 7){
        for (int i = 1; i <= 3; i++){
            stringstream convert(argv[i]);
            convert >> left_color[i - 1];
        }
        for (int i = 4; i <= 6; i++){
            stringstream convert(argv[i]);
            convert >> right_color[i - 4];
        }
    }
    else{
        return 0;
    }

    vector < int > diffs(3), char_diffs(3);
    for (int i = 0; i < 3; i++){
        diffs[i] = abs(right_color[i] - left_color[i]) / radius;
        char_diffs[i] = (right_color[i] < left_color[i]) ? 1 : -1;
    }

    ofstream file("diodes_colors.txt");
  	
    for (int i = 0; i < NUMPIXELS; i++){
        if (abs(pos - i) <= radius){
            for (int j = 0; j < 3; j++)
                file << right_color[j] + abs(pos - i) * char_diffs[j] * diffs[j] << " ";
            file << endl;
        }
    }

    file.close();
}
