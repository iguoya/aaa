#include "Config.h"

Config::Config() {
	ifstream file("config.txt");
	string line;
	string pattern = ":";
//	pair<string, string> key_value;
	string::size_type pos;
	string key;
	string value;
	while(std::getline(file, line)) {
		if(line.size() > 0) {
			pos = line.find(pattern);
			key = line.substr(0, pos);
			value = line.substr(pos+1, line.size()-pos-1);
			if (key == "file_name") {
				file_name = value;
			} else if(key == "frame_width") {
				frame_width = atoi(value.c_str());
			} else if(key == "frame_height") {
				frame_height = atoi(value.c_str());
			} else if(key == "font_size") {
				font_size =  atoi(value.c_str());
			} else if(key == "font_path") {
				font_path = value;
			}
//			if(key_value.)
//			cfg.insert(key_value);
			//		std::cout<<key_value.first<<std::endl;
			//std::cout<<key_value.second<<std::endl;
		}
	}
	/*
	for(map<string, string>::iterator it = cfg.begin();
		it != cfg.end(); ++it) {
		std::cout<<it->first<<"#"<<it->second<<std::endl;
	}
	*/
//	return cfg;
}
