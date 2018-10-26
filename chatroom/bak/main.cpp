#include "login.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //    Login lgn;
  //  app->run(lgn);
  //    if(lgn.get_login_succeed()) {
	MainWindow cr;
	app->run(cr);
	//    }
  //Shows the window and returns when it is closed.
 return 0;
}
