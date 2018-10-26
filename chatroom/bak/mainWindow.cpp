#include "mainWindow.h"
#include <iostream>
#include <string>
using std::string;
MainWindow::MainWindow()
    : VBox(Gtk::ORIENTATION_),
       btn_sendfile("发送文件"),
      btn_sendmsg("发送"),
      btn_view_history("历史记录"),
      btn_close("关闭窗口")
{
    set_title("聊天窗口");
    set_border_width(20);
    set_default_size(600, 600);
    
    add(VBox);
    //信息记录框
    VBox.pack_start(scrwd_show);
    scrwd_show.add(tv_show);
    tv_show.set_editable(false);
    //    scrwd_show.set_border_window_sizeGtk::TEXT_WINDOW_()
    scrwd_show.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    //输入框
    VBox.pack_start(ey_input, Gtk::PACK_SHRINK,10);
    

    //添加各种按钮
    VBox.pack_start(b_box, Gtk::PACK_SHRINK);

    b_box.pack_start(btn_sendfile, Gtk::PACK_SHRINK);
	    b_box.pack_start(btn_view_history, Gtk::PACK_SHRINK);
    b_box.pack_start(btn_sendmsg, Gtk::PACK_SHRINK);
    b_box.pack_start(btn_close, Gtk::PACK_SHRINK);

    //事件
    btn_sendmsg.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_send));
    btn_close.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_close)); 
    btn_sendfile.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_sendfile));
        btn_view_history.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_view_history));
    show_all_children();
}

void MainWindow::on_send() {
    string buf = ey_input.get_text();
    std::cout<<buf<<std::endl;
}

void MainWindow::on_close() {
    destroy_();
}

void MainWindow::on_view_history() {
    std::cout<<"history"<<std::endl;
}

void MainWindow::on_sendfile() {
    std::cout<<"sendfile"<<std::endl;
}

MainWindow::~MainWindow() {
}

