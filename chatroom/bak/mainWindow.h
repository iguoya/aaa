#ifndef CR_MAINWINDOW_H
#define CR_MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/button.h>
class MainWindow : public Gtk::Window
{
 public:
    MainWindow();
    ~MainWindow();
    protected:

    void on_send();
    void on_close();
    void on_view_history();
    void on_sendfile();
    
    Gtk::TextView tv_show, tv_input;
    Gtk::Button btn_sendfile, btn_sendmsg, btn_close, btn_view_history;
    Gtk::ScrolledWindow scrwd_show;
    Gtk::Entry ey_input;
    //    Gtk::Frame fm_show, fm_input;
    Gtk::ButtonBox b_box;
    // Gtk::Separator sep1;
    Gtk::Box VBox;
    
};
#endif
