#ifndef CR_LOGIN_H
#define CR_LOGIN_H

#include <gtkmm.h>
//#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>


#include "mainWindow.h"

#include <gtkmm/window.h>

class Login : public Gtk::Window
{
 public:
    Login();
    virtual ~Login();
      bool get_login_succeed() { return login_succeed;}
 private:
    bool login_succeed;
 protected:
    void on_login();
    void on_quit();
  
    void set_login_succeed(bool flag) {login_succeed = flag;}
    
    Gtk::Label lb_account, lb_password;

    Gtk::Entry ey_account, ey_password;

    Gtk::Separator sep1, sep2;

    Gtk::Box box_top,box_upper,box_lower, box_1, box_2;

     //     Gtk::Frame m_frame;

    Gtk::Button btn_login, btn_quit;
    
};

#endif
