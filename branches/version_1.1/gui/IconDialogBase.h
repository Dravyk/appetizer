// -*- C++ -*- generated by wxGlade 0.6.3

#include <wx/wx.h>
#include <wx/image.h>
// begin wxGlade: ::dependencies
// end wxGlade


#ifndef ICONDIALOGBASE_H
#define ICONDIALOGBASE_H


// begin wxGlade: ::extracode
enum {
  ID_GROUPEDIT_DLG_BUTTON_Save,
  ID_GROUPEDIT_DLG_BUTTON_Cancel,
  ID_GROUPEDIT_DLG_BUTTON_SelectFile,
  ID_GROUPEDIT_DLG_BUTTON_SelectFolder,
  ID_GROUPEDIT_DLG_BUTTON_ChangeIcon
};
// end wxGlade


class IconDialogBase: public wxDialog {
public:
    // begin wxGlade: IconDialogBase::ids
    // end wxGlade

    IconDialogBase(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: IconDialogBase::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: IconDialogBase::attributes
    wxStaticText* label_1;
    wxTextCtrl* text_ctrl_1;
    wxStaticText* listViewPlaceHolder;
    wxButton* button_2;
    wxButton* button_3;
    // end wxGlade
}; // wxGlade: end class


#endif // ICONDIALOGBASE_H
