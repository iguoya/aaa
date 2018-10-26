#include "Render.h"

Render::Render(const char* font_lib, int font_size) {
	if(FT_Init_FreeType(&library))
		throw std::runtime_error("FT Init failed");
	if(FT_New_Face(library, font_lib, 0, &face))
		throw std::runtime_error("FT_New_Face Failed");
	FT_Set_Pixel_Sizes(face, font_size, 0);
	this->font_size = font_size;
}
word_bitmap Render::render_word(unsigned int char_code) {
	vector<unsigned int> word_map;
	FT_UInt glyph_index = FT_Get_Char_Index(face, char_code);
	FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	FT_GlyphSlot slot = face->glyph;
	FT_Bitmap & bitmap = slot->bitmap;
	int base_y, base_x;
	int front_color = 0x00000000;
	int back_color = 0xffffffff;
	int border_color = 0x88888888;
	base_y = font_size-8-slot->bitmap_top;
	base_x = slot->bitmap_left;
	for(int y = 0; y < font_size; ++y) {
		for(int x = 0; x < font_size; ++x) {
			if((y >= base_y)
			   && (y < base_y + bitmap.rows)
			   && (x >= base_x)
			   && (x < base_x + bitmap.width)
				) {
				if(slot->bitmap.buffer[(y-base_y)*bitmap.width+x-base_x]) {
						word_map.push_back(front_color);
				} else {
						word_map.push_back(back_color);
				}
			} else {
				word_map.push_back(border_color);
			}
		}
	}
	return word_map;
/*
  std::cout<<"top:"<<slot->bitmap_top
  <<", left:"<<slot->bitmap_left
  <<",rows:"<<slot->bitmap.rows
  <<", asd:"<<asd<<std::endl;
  for(int i = 0; i < slot->bitmap.rows; ++i) {
  for(int j = 0; j < slot->bitmap.width; ++j) {
  if(slot->bitmap.buffer[i*bitmap.width+j])
  std::cout<<"*";
  else
  std::cout<<" ";
  }
  std::cout<<"\t"<<"line:"<<i<<std::endl;
  std::cout<<std::endl;
  }
  td::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
**/
}
vector<word_bitmap> Render::render_frame(std::wstring content) {
	int i = 0;
	word_bitmap word;
	vector<word_bitmap> frame_content;
	while(i < content.size()) {
		word = render_word(content[i]);
		frame_content.push_back(word);
	}
	return frame_content;
}
Render::~Render() {
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}
