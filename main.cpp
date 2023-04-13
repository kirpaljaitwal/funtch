// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wx.h>
#include <wx/socket.h>




class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    wxTextCtrl *fn_ipText;
    wxSocketClient *socket;




    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void fnSetMenuBar();
    void fnSetStatusBar();
    void fnSetIpTextEntry();
    void fnSetSocket();
    void fnSocketConnect(wxCommandEvent& event);
    void check_ipv4_format(char *address);


    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Hello=wxID_HIGHEST, BTN_ID_CONNECT
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(BTN_ID_CONNECT, MyFrame::fnSocketConnect)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}


void MyFrame::fnSetMenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::fnSetStatusBar()
{
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::fnSetIpTextEntry()
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);


    wxBoxSizer *vsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hsizer = new wxBoxSizer(wxHORIZONTAL);

    fn_ipText = new wxTextCtrl(panel,wxID_ANY,"192.168.0.1",wxDefaultPosition,wxSize(300,-1),0,wxDefaultValidator,"iptext");
    wxButton *button = new wxButton(panel, BTN_ID_CONNECT, wxT("Connect"),wxPoint(20, 20));

    hsizer->Add(fn_ipText);
    hsizer->Add(button);
    vsizer->Add(hsizer);

    panel->SetSizer(vsizer);
}


void MyFrame::check_ipv4_format(char *address)
{

}


void MyFrame::fnSocketConnect(wxCommandEvent& event)
{
    wxIPV4address addr;
    if(! fn_ipText->GetLineLength(0)){
        wxLogMessage("Enter Device IP Adress.\r\n");
    }

    //check_ipv4_format();

    addr.Hostname(fn_ipText->GetValue());
    addr.Service(8888);
    socket->Connect(addr, true);

    if(! socket->IsConnected()){
        wxLogMessage("Unable to connect the IP.\r\n%s",fn_ipText->GetValue());
    }
    else{
        wxLogMessage("Connected to the IP.\r\n%s",fn_ipText->GetValue());
    }

}


void MyFrame::fnSetSocket()
{
    socket = new wxSocketClient(wxSOCKET_NONE);
}


MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "funtch 1.0")
{
    fnSetMenuBar();
    fnSetStatusBar();
    fnSetIpTextEntry();
    fnSetSocket();


}

