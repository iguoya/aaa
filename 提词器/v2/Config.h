#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>



using std::string;
using std::ifstream;

class Config {
public:
	string file_name;
	int frame_width;
	int frame_height;
	int font_size;
	string font_path;
	Config();
};



#endif
