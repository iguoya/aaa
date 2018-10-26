#ifndef CONTENT_H
#define CONTENT_H
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <vector>
#include <string>
#include "Config.h"
#include <cmath>

using std::string;
using std::wstring;
using std::vector;
class Content {
public:
	Content(string file);
	wstring utf8_to_utf16(const string& str);
	
	string content;
	vector<wstring> split(wstring content, class Config cfg);
};
#endif
