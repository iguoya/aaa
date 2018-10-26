#include "tools.h"

FT_GlyphSlot GetCharBitMap(int iCharSize, unsigned int uiCharCode) {
	FT_Library ftLibrary;
	FT_Error ftError = FT_Init_FreeType(&ftLibrary);
	FT_Face ftFace;
	FT_New_Face(ftLibrary, "msyhbd.ttc", 0, &ftFace);
	if(ftError == FT_Err_Unknown_File_Format) {
		printf("Error! Could not support this format\n");
		exit(-1);
	} else if(ftError) {
		printf("Error , Could not open font file\n");
		exit(-1);
	}
	FT_Set_Pixel_Sizes(ftFace, iCharSize, 0);
	FT_UInt uiGlyphIndex = FT_Get_Char_Index(ftFace, uiCharCode);
	FT_Load_Glyph(ftFace, uiGlyphIndex, FT_LOAD_DEFAULT);
	FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_MONO);
	return ftFace->glyph;
}
Buf_info divide_buf( std::wstring content) {
	FT_GlyphSlot slot;
	int char_size = 64;
	int col_size = floor(1280/char_size);
	int line_size = floor((810*4-720)/char_size);
	Buf_info bufs;
	int index = 0;
	int screen_size = 1280*4*810*4;
	int i = 0;
	for(int i = 0; i < 2; ++i) {
		bufs.buf[i] = new char[screen_size];
		memset(bufs.buf[index], 0, screen_size);
	}
	while(true) {
		int line = 0;
		int col_num = 0;
		//	bufs.buf[index] = new char[720*1280*3*4];
		//memset(bufs.buf[index], 0, 720*1280*3*4);
		while(line < line_size) {
			if(i >= content.size()) {
//				bufs.buf[buf_index] = buf;p
				bufs.size = index + 1;
			//	return bufs;
			}
			if(content[i] == 10) {
				++line;
				col_num = 0;
			} else {
				if(col_num == col_size-1) {
					++line;
					col_num = 0;
				}
				slot = GetCharBitMap(char_size,content[i]);
				int *p;
				for (int iRow = 0; iRow < slot->bitmap.rows; iRow++) {
					for (int iCol = 0; iCol < slot->bitmap.width; iCol++) {
						int pos = 1280*(iRow+line*char_size)+iCol+col_num*char_size;
						if ((slot->bitmap.buffer[iRow * slot->bitmap.pitch + iCol / 8]
							 & (0xC0 >> (iCol % 8))) == 0) {
							//p = (int *)frameBuffer;
							//*(p+pos) = 0x00000000;
//								*(frameBuffer+pos) = 0x00000000;
						} else {
							p = (int *)bufs.buf[index];
							*(p+pos) = 0x33333333;
						}
					}
				}
				++col_num;
			}
			++i;
		}
		++index;
		if(index == 2) {
//			memcpy(bufs.buf[0]-2520*1280*4, bufs.buf[1], 720*1280*4);
			bufs.size = 2;
			printf("%s", (char *)bufs.buf[0]);
			return bufs;
		}
		//	bufs.size = buf_index;
//		return bufs;
	}
}
std::wstring utf8_to_utf16(const std::string& utf8)
{
	std::vector<unsigned long> unicode;
	size_t i = 0;
	while (i < utf8.size())
	{
		unsigned long uni;
		size_t todo;
		bool error = false;
		unsigned char ch = utf8[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			throw std::logic_error("not a UTF-8 string");
		}
		else if (ch <= 0xDF)
		{
			uni = ch&0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch&0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch&0x07;
			todo = 3;
		}
		else
		{
			throw std::logic_error("not a UTF-8 string");
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == utf8.size())
				throw std::logic_error("not a UTF-8 string");
			unsigned char ch = utf8[i++];
			if (ch < 0x80 || ch > 0xBF)
				throw std::logic_error("not a UTF-8 string");
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
			throw std::logic_error("not a UTF-8 string");
		if (uni > 0x10FFFF)
			throw std::logic_error("not a UTF-8 string");
		unicode.push_back(uni);
	}
	std::wstring utf16
		;
	for (size_t i = 0; i < unicode.size(); ++i)
	{
		unsigned long uni = unicode[i];
		if (uni <= 0xFFFF)
		{
			utf16 += (wchar_t)uni;
		}
		else
		{
			uni -= 0x10000;
			utf16 += (wchar_t)((uni >> 10) + 0xD800);
			utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
		}
	}
	return utf16;
}
void printFixedInfo (struct fb_fix_screeninfo fix_screen_info)
{
	printf ("Fixed screen info:\n"
			"\tid: %s\n"
			"\tsmem_start: 0x%lx\n"
			"\tsmem_len: %d\n"
			"\ttype: %d\n"
			"\ttype_aux: %d\n"
			"\tvisual: %d\n"
			"\txpanstep: %d\n"
			"\typanstep: %d\n"
			"\tywrapstep: %d\n"
			"\tline_length: %d\n"
			"\tmmio_start: 0x%lx\n"
			"\tmmio_len: %d\n"
			"\taccel: %d\n"
			"\n",
			fix_screen_info.id, fix_screen_info.smem_start, fix_screen_info.smem_len, fix_screen_info.type,
			fix_screen_info.type_aux, fix_screen_info.visual, fix_screen_info.xpanstep, fix_screen_info.ypanstep,
			fix_screen_info.ywrapstep, fix_screen_info.line_length, fix_screen_info.mmio_start,
			fix_screen_info.mmio_len, fix_screen_info.accel);
}

//打印fb驱动中var结构信息，注：fb驱动加载后，var结构可根据实际需要被重置
void printVariableInfo (struct fb_var_screeninfo var_screen_info)
{
	printf ("Variable screen info:\n"
			"\txres: %d\n"
			"\tyres: %d\n"
			"\txres_virtual: %d\n"
			"\tyres_virtual: %d\n"
			"\tyoffset: %d\n"
			"\txoffset: %d\n"
			"\tbits_per_pixel: %d\n"
			"\tgrayscale: %d\n"
			"\tred: offset: %2d, length: %2d, msb_right: %2d\n"
			"\tgreen: offset: %2d, length: %2d, msb_right: %2d\n"
			"\tblue: offset: %2d, length: %2d, msb_right: %2d\n"
			"\ttransp: offset: %2d, length: %2d, msb_right: %2d\n"
			"\tnonstd: %d\n"
			"\tactivate: %d\n"
			"\theight: %d\n"
			"\twidth: %d\n"
			"\taccel_flags: 0x%x\n"
			"\tpixclock: %d\n"
			"\tleft_margin: %d\n"
			"\tright_margin: %d\n"
			"\tupper_margin: %d\n"
			"\tlower_margin: %d\n"
			"\thsync_len: %d\n"
			"\tvsync_len: %d\n"
			"\tsync: %d\n"
			"\tvmode: %d\n"
			"\n",
			var_screen_info.xres, var_screen_info.yres, var_screen_info.xres_virtual, var_screen_info.yres_virtual,
			var_screen_info.xoffset, var_screen_info.yoffset, var_screen_info.bits_per_pixel,
			var_screen_info.grayscale, var_screen_info.red.offset, var_screen_info.red.length,
			var_screen_info.red.msb_right, var_screen_info.green.offset, var_screen_info.green.length,
			var_screen_info.green.msb_right, var_screen_info.blue.offset, var_screen_info.blue.length,
			var_screen_info.blue.msb_right, var_screen_info.transp.offset, var_screen_info.transp.length,
			var_screen_info.transp.msb_right, var_screen_info.nonstd, var_screen_info.activate,
			var_screen_info.height, var_screen_info.width, var_screen_info.accel_flags, var_screen_info.pixclock,
			var_screen_info.left_margin, var_screen_info.right_margin, var_screen_info.upper_margin,
			var_screen_info.lower_margin, var_screen_info.hsync_len, var_screen_info.vsync_len,
			var_screen_info.sync, var_screen_info.vmode);
}
