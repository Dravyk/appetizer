// -*- C++ -*- generated by wxGlade 0.6.3 on Sun Oct 19 22:20:23 2008

#include "ShortcutEditorFrameBase.h"

// begin wxGlade: ::extracode
// end wxGlade



ShortcutEditorFrameBase::ShortcutEditorFrameBase(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: ShortcutEditorFrameBase::ShortcutEditorFrameBase
    nameLabel = new wxStaticText(this, wxID_ANY, wxT("Name:"));
    nameTextBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    locationLabel = new wxStaticText(this, wxID_ANY, wxT("Location:"));
    locationTextBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    locationButton = new wxButton(this, wxID_ANY, wxT("..."));
    saveButton = new wxButton(this, wxID_ANY, wxT("Save"));
    cancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"));

    set_properties();
    do_layout();
    // end wxGlade
}


void ShortcutEditorFrameBase::set_properties()
{
    // begin wxGlade: ShortcutEditorFrameBase::set_properties
    SetTitle(wxT("Edit shortcut"));
    SetSize(wxSize(338, 156));
    locationButton->SetMinSize(wxSize(30, -1));
    // end wxGlade
}


void ShortcutEditorFrameBase::do_layout()
{
    // begin wxGlade: ShortcutEditorFrameBase::do_layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* saveCancelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* inputSizers = new wxFlexGridSizer(4, 2, 10, 8);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    inputSizers->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL, 0);
    inputSizers->Add(nameTextBox, 0, wxEXPAND, 0);
    inputSizers->Add(locationLabel, 0, wxALIGN_CENTER_VERTICAL, 0);
    sizer_4->Add(locationTextBox, 1, wxRIGHT|wxEXPAND, 8);
    sizer_4->Add(locationButton, 0, 0, 0);
    inputSizers->Add(sizer_4, 1, wxEXPAND, 0);
    inputSizers->AddGrowableCol(1);
    mainSizer->Add(inputSizers, 0, wxALL|wxEXPAND, 10);
    saveCancelSizer->Add(saveButton, 0, wxRIGHT|wxALIGN_BOTTOM, 8);
    saveCancelSizer->Add(cancelButton, 0, wxALIGN_BOTTOM, 0);
    mainSizer->Add(saveCancelSizer, 1, wxRIGHT|wxBOTTOM|wxALIGN_RIGHT, 10);
    SetSizer(mainSizer);
    Layout();
    // end wxGlade
}

