#ifndef HELLOWORLD_H
#define HELLOWORLD_H

class Login : public wxApp
{
 public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame
{
 public:
    MainFrame();
    void OnQuit(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);
    void OnSocketEvent(wxSocketEvent& event);
 private:
        
    wxTextCtrl *m_password;
    wxTextCtrl *m_username;

    //  wxButton *btn_connect;
    wxButton *btn_login;
    wxButton *btn_quit;

    //    wxString 
    wxSocketClient *m_sock;
    DECLARE_EVENT_TABLE()
};

enum {
    ID_QUIT = 1,
    ID_LOGIN,
    ID_CONNECT,
    ID_SOCKET
};
//DECLARE_APP(Login)
BEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_BUTTON(ID_QUIT, MainFrame::OnQuit)
//EVT_BUTTON(ID_CONNECT, MainFrame::OnLogin)
EVT_BUTTON(ID_LOGIN, MainFrame::OnLogin)

EVT_SOCKET(ID_SOCKET, MainFrame::OnSocketEvent)


END_EVENT_TABLE()

#endif

    
