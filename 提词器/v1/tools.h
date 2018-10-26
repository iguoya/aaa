#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <linux/fb.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

typedef struct Buf_info {
	char *buf[100];
	int size;
} Buf_info;

using namespace std;

void printFixedInfo(struct fb_fix_screeninfo);
void printVariableInfo(struct fb_var_screeninfo);
std::wstring utf8_to_utf16(const std::string &);
Buf_info divide_buf(std::wstring);
//int drawScreen(int *, wstring, int);
FT_GlyphSlot GetCharBitMap(int, unsigned int );

#endif
