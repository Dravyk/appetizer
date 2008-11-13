// -*- C++ -*- generated by wxGlade 0.6.3

#include "AboutDialogBase.h"

// begin wxGlade: ::extracode

// end wxGlade



AboutDialogBase::AboutDialogBase(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    // begin wxGlade: AboutDialogBase::AboutDialogBase
    notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    notebook_pane_2 = new wxPanel(notebook, wxID_ANY);
    notebook_1_pane_1 = new wxPanel(notebook, wxID_ANY);
    iconBitmap = new wxStaticBitmap(notebook_1_pane_1, wxID_ANY, wxNullBitmap);
    versionLabel = new wxTextCtrl(notebook_1_pane_1, wxID_ANY, wxT("NAME VERSION"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
    copyrightLabel = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("Copyright (C) 2008"));
    webLabel = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("*Web:"));
    linkLabel = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("http://appetizer.sourceforge.net"));
    contactLabel = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("*Contact:"));
    contactLabel2 = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("nothing@nothing.com"));
    creditLabel = new wxStaticText(notebook_1_pane_1, wxID_ANY, wxT("Credits:"));
    creditTextBox = new wxTextCtrl(notebook_1_pane_1, wxID_ANY, wxT("Translators: Simeon, Pieter Kerstens, Michal Trzebiatowski\n\nThis software uses a number of open source libraries including:\n\n- Simpleini by Brodie Thiesfield\n- TinyXml by Yves Berquin\n- The Boost C++ Libraries\n- wxWidgets by their respective authors\n\nDialog boxes are built using wxGlade by Alberto Griggio."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_LINEWRAP|wxTE_WORDWRAP);
    licenseTextBox = new wxTextCtrl(notebook_pane_2, wxID_ANY, wxT("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. \n\nYou should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_LINEWRAP|wxTE_WORDWRAP);
    okButton = new wxButton(this, ID_ABOUT_DLG_BUTTON_OK, wxT("OK"));

    set_properties();
    do_layout();
    // end wxGlade
}


void AboutDialogBase::set_properties()
{
    // begin wxGlade: AboutDialogBase::set_properties
    SetTitle(wxT("dialog_1"));
    SetSize(wxSize(334, 440));
    versionLabel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DHILIGHT));
    // end wxGlade
}


void AboutDialogBase::do_layout()
{
    // begin wxGlade: AboutDialogBase::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* headerGridSizer = new wxFlexGridSizer(1, 2, 0, 0);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(2, 2, 6, 6);
    headerGridSizer->Add(iconBitmap, 0, 0, 0);
    sizer_6->Add(versionLabel, 0, wxBOTTOM|wxEXPAND, 6);
    sizer_6->Add(copyrightLabel, 0, wxBOTTOM, 10);
    grid_sizer_2->Add(webLabel, 0, 0, 0);
    grid_sizer_2->Add(linkLabel, 0, wxBOTTOM, 4);
    grid_sizer_2->Add(contactLabel, 0, 0, 0);
    grid_sizer_2->Add(contactLabel2, 0, 0, 0);
    sizer_6->Add(grid_sizer_2, 1, wxBOTTOM|wxEXPAND, 6);
    headerGridSizer->Add(sizer_6, 1, wxLEFT|wxEXPAND, 8);
    headerGridSizer->AddGrowableCol(1);
    grid_sizer_1->Add(headerGridSizer, 1, wxBOTTOM|wxEXPAND, 6);
    sizer_4->Add(creditLabel, 0, wxBOTTOM, 6);
    sizer_4->Add(creditTextBox, 1, wxEXPAND, 0);
    grid_sizer_1->Add(sizer_4, 1, wxEXPAND, 0);
    grid_sizer_1->AddGrowableRow(1);
    grid_sizer_1->AddGrowableCol(0);
    sizer_3->Add(grid_sizer_1, 1, wxALL|wxEXPAND, 8);
    notebook_1_pane_1->SetSizer(sizer_3);
    sizer_5->Add(licenseTextBox, 1, wxALL|wxEXPAND, 6);
    notebook_pane_2->SetSizer(sizer_5);
    notebook->AddPage(notebook_1_pane_1, wxT("About"));
    notebook->AddPage(notebook_pane_2, wxT("License"));
    sizer_1->Add(notebook, 1, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 4);
    sizer_2->Add(okButton, 0, wxALIGN_BOTTOM, 0);
    sizer_1->Add(sizer_2, 0, wxALL|wxALIGN_RIGHT, 10);
    SetSizer(sizer_1);
    Layout();
    // end wxGlade
}

