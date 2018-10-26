#ifndef RENDER_H
#define RENDER_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
typedef vector<unsigned int>  word_bitmap;
class Render {
public:
	FT_Library library;
	FT_Face face;
	int font_size;
	Render(const char *font_lib, int font_size);
	word_bitmap  render_word(unsigned int char_code);
	vector<word_bitmap> render_frame(std::wstring content);
	~Render();
};
#endif
