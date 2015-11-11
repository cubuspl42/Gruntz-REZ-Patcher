///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

PatchingDialogTemplate::PatchingDialogTemplate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Progress") ), wxVERTICAL );

	label_progress = new wxStaticText( this, wxID_ANY, wxT("Reading backup REZ file ..."), wxDefaultPosition, wxDefaultSize, 0 );
	label_progress->Wrap( -1 );
	sbSizer4->Add( label_progress, 0, wxALL, 5 );

	gauge_total = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	gauge_total->SetValue( 0 );
	sbSizer4->Add( gauge_total, 0, wxALL|wxEXPAND, 5 );

	text_log = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
	sbSizer4->Add( text_log, 1, wxALL|wxEXPAND, 5 );

	button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( button_ok, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( sbSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PatchingDialogTemplate::OnDialogClose ) );
}

PatchingDialogTemplate::~PatchingDialogTemplate()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( PatchingDialogTemplate::OnDialogClose ) );
}
