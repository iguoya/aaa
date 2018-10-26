#ifndef SERVER_H
#define SERVER_H

class Server : public wxApp
{
 public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame
{
 public:
    MainFrame();
              
    wxTextCtrl *m_log;


    void OnServer(wxCommandEvent& event);
 private:
    DECLARE_EVENT_TABLE()
};

enum {
    ID_QUIT = 1,
    ID_LOGIN,
};
//DECLARE_APP(Server)
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_QUIT, MainFrame::OnQuit)
//EVT_SOCKET(ID_SOCKET, MainFrame::OnAbout)
EVT_BUTTON(ID_LOGIN, MainFrame::OnServer)
END_EVENT_TABLE()

#endif

    
