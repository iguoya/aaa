#include "tools.h"
#include <termio.h>
struct fb_var_screeninfo var_screen_info;
struct fb_fix_screeninfo fix_screen_info;

struct screen_info {
	int time;
	int offset;
	int direct;
	int prvious_direct;
	int num;
};

static struct screen_info s_info;

int scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	in = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}

void *show_screen(void *info) {
	const char *dev = "/dev/fb0";
	char *frameBuffer = 0;
	int frameBuffer_id = open(dev, O_RDWR);

	ioctl(frameBuffer_id, FBIOGET_FSCREENINFO, &fix_screen_info);
	ioctl(frameBuffer_id, FBIOGET_VSCREENINFO, &var_screen_info);
	int screen_size = fix_screen_info.smem_len;
//	int screen_size = 1280*720*4*3;
	frameBuffer = (char *)mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, frameBuffer_id, 0);
	if(frameBuffer == MAP_FAILED) {
		perror("Error:Failed to map device to memory");
		exit(1);
	}
	std::ifstream t("same.txt");
	std::stringstream buffer;
	buffer<<t.rdbuf();
	std::string t_str = buffer.str();
	std::wstring content = utf8_to_utf16(t_str);
//	printFixedInfo(fix_screen_info);
//	printVariableInfo(var_screen_info);
	Buf_info bufs = divide_buf(content);
	
	int index = 0;
	memcpy(frameBuffer, bufs.buf[0], screen_size);
	int i = 0;
	int screen_num = bufs.size;
	
	while(true) {
		//10000:1 normal
		s_info.offset += s_info.direct;
		var_screen_info.yoffset =  s_info.offset % 2520;
		cout<<"time:"<<s_info.time<<endl;
		cout<<"direct:"<<s_info.direct<<endl;
		cout<<"offset:"<<s_info.offset<<endl;
		if(screen_num <= 1) {
			//simple screen
			if(var_screen_info.yoffset < 0 ||
			   var_screen_info.yoffset > 2520) {
//				s_info.offset = 0;
				s_info.direct = 0;
//				var_screen_info.yoffset = 0;
			}
		} else {
			if(s_info.direct == 1) {
				if(var_screen_info.yoffset % 2520 == 0) {
					if(s_info.num < screen_num) {
						++s_info.num;
					} else {
						s_info.num = 1;
					}
//					s_info.offset = 0;
//					ioctl(frameBuffer_id, FBIOPUT_VSCREENINFO, &var_screen_info);
//					ioctl(frameBuffer_id, FBIOPAN_DISPLAY, &var_screen_info);
					memcpy(frameBuffer, bufs.buf[s_info.num-1], screen_size);
				}
			} else {
				if(var_screen_info.yoffset <= 0) {
					if(s_info.num > 1) {
						--s_info.num;
					} else {
						s_info.num = 1;
					}
					//	s_info.offset = 0;
//					ioctl(frameBuffer_id, FBIOPUT_VSCREENINFO, &var_screen_info);
//					ioctl(frameBuffer_id, FBIOPAN_DISPLAY, &var_screen_info);
					memcpy(frameBuffer, bufs.buf[s_info.num-1], screen_size);
				}
			}
		}
		ioctl(frameBuffer_id, FBIOPUT_VSCREENINFO, &var_screen_info);
		ioctl(frameBuffer_id, FBIOPAN_DISPLAY, &var_screen_info);
		usleep(s_info.time);
	}
}

int main() {
	pthread_t pid;
	int res;
	s_info.num = 1;
	s_info.time = 10000;
	s_info.offset = 0;
	s_info.prvious_direct = 1;
	res = pthread_create(&pid, NULL, show_screen, NULL);
	while(true) {
		int signal = scanKeyboard();
//		cout<<"you input "<<signal<<endl;
		switch(signal) {
		case 115://s slow
			s_info.time *= 1.2;
			break;
		case 102:// f fast
			s_info.time *= 0.8;
			break; 
		case 110://n  next 
			s_info.offset +=720;
			if(s_info.offset >= 2520)
				s_info.direct = 0;
				s_info.offset = 2520;
			break;
		case 112://p privious
			s_info.offset -=720;
			if(s_info.offset < 0) {
				s_info.direct = 0;
				s_info.offset = 0;
			}
			break;
		case 117://u up
			s_info.direct = -1;
			break;
		case 100://d down
			s_info.direct = 1;
			break;
		case 32: //blankspace
			if(s_info.direct != 0) {
				s_info.prvious_direct = s_info.direct;
				s_info.direct = 0;
			} else {
				s_info.direct = s_info.prvious_direct;
			}
			break;
		}
	}
	pthread_join(pid, NULL);
	return 0;
}
