///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

ChangeREZDialogTemplate::ChangeREZDialogTemplate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	label_description = new wxStaticText( m_panel7, wxID_ANY, wxT("Choose the original and unmodified REZ file to back it up."), wxDefaultPosition, wxDefaultSize, 0 );
	label_description->Wrap( -1 );
	bSizer10->Add( label_description, 1, wxALL, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	textctrl_path = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( textctrl_path, 1, wxALIGN_CENTER|wxALL, 5 );

	button_browse = new wxButton( m_panel7, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( button_browse, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer10->Add( bSizer8, 1, wxEXPAND, 5 );

	m_gauge1 = new wxGauge( m_panel7, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	m_gauge1->SetValue( 0 );
	bSizer10->Add( m_gauge1, 0, wxALL|wxEXPAND, 5 );

	checkbox_optional = new wxCheckBox( m_panel7, wxID_ANY, wxT("Set this REZ file as an output REZ"), wxDefaultPosition, wxDefaultSize, 0 );
	checkbox_optional->SetValue(true);
	bSizer10->Add( checkbox_optional, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	label_progress = new wxStaticText( m_panel7, wxID_ANY, wxT("No REZ file picked."), wxDefaultPosition, wxDefaultSize, 0 );
	label_progress->Wrap( -1 );
	bSizer9->Add( label_progress, 0, wxALIGN_CENTER|wxALL, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( m_panel7, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( m_panel7, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	bSizer9->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer9, 1, wxEXPAND, 5 );


	m_panel7->SetSizer( bSizer10 );
	m_panel7->Layout();
	bSizer10->Fit( m_panel7 );
	bSizer11->Add( m_panel7, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer11 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	button_browse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedBrowse ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedCancel ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedOK ), NULL, this );
}

ChangeREZDialogTemplate::~ChangeREZDialogTemplate()
{
	// Disconnect Events
	button_browse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedBrowse ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedCancel ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChangeREZDialogTemplate::PressedOK ), NULL, this );

}
