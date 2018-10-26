#include "login.h"
#include <iostream>
#include <string>
using std::string;

Login::Login()
    : btn_login("登陆"),
      btn_quit("退出"),
      lb_account("帐号:"),
      lb_password("密码:"),
      box_top(Gtk::ORIENTATION_VERTICAL),
      box_upper(Gtk::ORIENTATION_VERTICAL),
      box_lower(Gtk::ORIENTATION_HORIZONTAL)
{
    
     set_title("用户登陆");
    set_border_width(20);
    set_size_request(300, 400);
    add(box_top);

    //添加 帐号 密码 输入框
    box_1.pack_start(lb_account,Gtk::PACK_SHRINK, 15);

    box_1.pack_start(ey_account, Gtk::PACK_SHRINK, 15);
    
    ey_password.set_visibility(false);
    box_2.pack_start(lb_password, Gtk::PACK_SHRINK, 15); 
box_2.pack_start(ey_password,  Gtk::PACK_SHRINK, 15);
 box_upper.pack_start(box_1);
     
    box_upper.pack_start(sep1, Gtk::PACK_SHRINK, 10);
 box_upper.pack_start(box_2);
      box_upper.pack_start(sep2, Gtk::PACK_SHRINK, 50);
    
      box_top.add(box_upper);
      //添加登陆 退出按钮
      
    box_top.add(box_lower);

    box_lower.pack_start(btn_login, Gtk::PACK_SHRINK, 50);
    box_lower.pack_start(btn_quit, Gtk::PACK_SHRINK);

    //绑定事件
    btn_login.signal_clicked().connect(sigc::mem_fun(*this, &Login::on_login));
    btn_quit.signal_clicked().connect(sigc::mem_fun(*this, &Login::on_quit));	

    set_login_succeed(false);
    show_all_children();
    
}

void Login::on_login() {
    std::cout<<"login"<<std::endl;
    std::string user = ey_account.get_text();
    std::string pwd = ey_password.get_text();
    std::cout<<"user:"<<user<<", password:"<<pwd<<std::endl;
    set_login_succeed(true);
    destroy_();
    //  hide();
}
void Login::on_quit() {
    hide();
}
Login::~Login() {
}
