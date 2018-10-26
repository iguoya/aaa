#define BOOST_TEST_MODULE config
#include <boost/test/included/unit_test.hpp>
#include "Config.cpp"
#include "Content.cpp"
#include "Render.cpp"
#include <locale>
using std::locale;

BOOST_AUTO_TEST_SUITE(config)

BOOST_AUTO_TEST_CASE(config) 
{
	Config cfg;
	std::cout<<cfg.file_name<<std::endl;
	std::cout<<cfg.frame_width<<std::endl;
	std::cout<<cfg.frame_height<<std::endl;
	std::cout<<cfg.font_size<<std::endl;
	std::cout<<cfg.font_path<<std::endl;
}

BOOST_AUTO_TEST_CASE(content) 
{

	std::string file("test.txt");
	Content *t = new Content(file);
//	std::cout<<t->content<<std::endl;
//	BOOST_CHECK(ts.compare(ws) == 0);
//	BOOST_REQUIRE_EQUAL(ts, t->content);

}
BOOST_AUTO_TEST_CASE(freetype)
{
	std::cout<<"ddd";
	Render* obj = new Render("/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc", 64);
	obj->render_word(L'a');
	obj->render_word(L'l');
	obj->render_word(L'中');
	obj->render_word(L'国');
	obj->render_word(L'一');
	obj->render_word(L'卜');
	obj->render_word(L'？');
	obj->render_word(L'。');

}

BOOST_AUTO_TEST_SUITE_END()
