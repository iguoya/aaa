//#include <wx/wxprec.h>

//#ifndef WX_PRECOMP
#include <wx/wx.h>
//#endif
#include <wx/socket.h>

#include "Login.h"
#include <iostream>

IMPLEMENT_APP(Login)

bool Login::OnInit()
{
    MainFrame *frame = new MainFrame;
                                    
    frame->Show(true);
    SetTopWindow(frame);
    return true;
    
}

MainFrame::MainFrame()
                     :wxFrame(NULL, wxID_ANY, _T("登录窗口"),wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE)
{

    wxPanel *p = new wxPanel(this, wxID_ANY);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);


    wxGridSizer *gridsizer = new wxGridSizer(2, 5, 5);

    //用户名 密码框
    gridsizer->Add(new wxStaticText(p, wxID_ANY, _T("用户名：")),
                   wxSizerFlags().Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));

    m_username = new wxTextCtrl(p, wxID_ANY, _T(""), wxDefaultPosition, wxSize(140, wxDefaultCoord));
    
    gridsizer->Add(m_username, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL));

    
    gridsizer->Add(new wxStaticText(p, wxID_ANY, _T("密码：")),
                   wxSizerFlags().Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
    m_password = new wxTextCtrl(p, wxID_ANY, _T(""), wxDefaultPosition, wxSize(140, wxDefaultCoord), wxTE_PASSWORD);
    
    gridsizer->Add(m_password, wxSizerFlags().Align( wxALIGN_CENTER_VERTICAL));                   

    topsizer->Add(gridsizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));

    //登录按钮

    wxBoxSizer *button_box = new wxBoxSizer(wxHORIZONTAL);

    //    btn_connect = new wxButton(p, ID_CONNECT, _T("连接"));
    //    button_box->Add(btn_connect, wxSizerFlags().Border(wxALL, 17));


    btn_login = new wxButton(p, ID_LOGIN, _T("登录"));
    
    button_box->Add(btn_login, wxSizerFlags().Border(wxALL, 17));

    
    btn_quit = new wxButton(p, ID_QUIT, _T("退出"));
    button_box->Add(btn_quit, wxSizerFlags().Border(wxALL, 17));

    topsizer->Add(button_box, wxSizerFlags().Center());
    
  
    p->SetSizer(topsizer);


}


void MainFrame::OnLogin(wxCommandEvent& WXUNUSED(event)) {
    //    std::cout<<wxStrlen(m_username->GetValue())<<std::endl;
    /*
    wxMessageBox(wxString::Format(_T("username: %s\n")
                                  _T("password: %s\n"),
                                  m_username->GetValue(),
                                  +m_password->GetValue()
                                  ),
                 _T("test:"), wxOK, this);
    */


    if((m_username->GetValue() == _T(""))
       || m_password->GetValue() == _T("")) {
        wxMessageBox(_T("用户名或密码不能为空"));
        return;
    }
    
    wxIPV4address addr;
    addr.Hostname(_T("localhost"));
    addr.Service(5000);

    m_sock = new wxSocketClient();
    
    
      m_sock->SetEventHandler(*this, ID_SOCKET);

    m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                      wxSOCKET_INPUT_FLAG |
                      wxSOCKET_LOST_FLAG);
    
    m_sock->Notify(true);

    m_sock->Connect(addr, false);
    if(m_sock->IsConnected())
        wxMessageBox(_("succeeded"));
    else
        wxMessageBox(_("failed"));
}
/*
void MainFrame::OnLogin(wxSocketEvent& event) {

}
*/

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}
void MainFrame::OnSocketEvent(wxSocketEvent& event) {

    wxSocketBase* sock = event.GetSocket();
    //        char buf[1000];
    char msg[100];
    memset(msg, 0, sizeof(msg));
    wxString send_info;
    wxString get_info;
    switch(event.GetSocketEvent()) {
    case wxSOCKET_CONNECTION:

        send_info = _T("login%#%")+m_username->GetValue()
            +_T("$;$")+m_password->GetValue();
        strcpy(msg, send_info.mb_str());
        sock->Write(msg, sizeof(msg));
        break;
    case wxSOCKET_INPUT:
        //       wxMessageBox(_T("get message"));
        sock->Read(msg, sizeof(msg));
        get_info = wxString::FromAscii(msg);
        // wxMessageBox(get_info);
        break;
    case wxSOCKET_LOST:
        sock->Destroy();
            break;
    }

}

