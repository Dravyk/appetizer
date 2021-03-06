#include "ApplicationTrayIcon.h"
#include "MainFrame.h"
#include "Localization.h"


extern MainFrame* gMainFrame;


BEGIN_EVENT_TABLE(ApplicationTrayIcon, wxTaskBarIcon)
  EVT_MENU(ID_MENU_HideShow, ApplicationTrayIcon::OnMenuHideShow)
  EVT_MENU(ID_MENU_Exit, ApplicationTrayIcon::OnMenuExit)
  EVT_TASKBAR_LEFT_UP(ApplicationTrayIcon::OnLeftUp)
END_EVENT_TABLE()


ApplicationTrayIcon::ApplicationTrayIcon() {}


wxMenu* ApplicationTrayIcon::CreatePopupMenu() {
  wxMenu* menu = new wxMenu();

  menu->Append(ID_MENU_HideShow, gMainFrame->IsVisible() ? LOC(_T("TrayIcon.Hide")) : LOC(_T("TrayIcon.Show")));
  menu->AppendSeparator();  
  menu->Append(ID_MENU_Exit, LOC(_T("Exit")));

  return menu;
}


void ApplicationTrayIcon::OnMenuHideShow(wxCommandEvent& evt) {
  gMainFrame->Show(!gMainFrame->IsVisible());
}


void ApplicationTrayIcon::OnMenuExit(wxCommandEvent& evt) {
  gMainFrame->Close();
}


void ApplicationTrayIcon::OnLeftUp(wxTaskBarIconEvent& evt) {
  if (!gMainFrame->IsVisible()) {
    gMainFrame->Show();
    gMainFrame->Raise();
  } else {
    gMainFrame->Raise();
  }
}