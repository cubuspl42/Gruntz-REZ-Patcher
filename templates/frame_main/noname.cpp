///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MainFrameTemplate::MainFrameTemplate( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	m_splitter3 = new wxSplitterWindow( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrameTemplate::m_splitter3OnIdle ), NULL, this );
	m_splitter3->SetMinimumPaneSize( 1 );

	m_panel51 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_panel51, wxID_ANY, wxT("Pool") ), wxVERTICAL );

	list_pool = new wxListCtrl( m_panel51, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_ASCENDING );
	sbSizer11->Add( list_pool, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	button_pool_apply = new wxButton( m_panel51, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( button_pool_apply, 1, wxALL, 5 );

	button_pool_takeoff = new wxButton( m_panel51, wxID_ANY, wxT("Take off"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( button_pool_takeoff, 1, wxALL, 5 );

	button_pool_delete = new wxButton( m_panel51, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( button_pool_delete, 1, wxALL, 5 );

	button_pool_newpatch = new wxButton( m_panel51, wxID_ANY, wxT("New Patch ..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( button_pool_newpatch, 1, wxALL, 5 );


	bSizer7->Add( bSizer3, 1, wxEXPAND, 5 );


	sbSizer11->Add( bSizer7, 0, wxEXPAND, 5 );


	m_panel51->SetSizer( sbSizer11 );
	m_panel51->Layout();
	sbSizer11->Fit( m_panel51 );
	m_panel6 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, wxT("Patches to apply") ), wxVERTICAL );

	list_patches = new wxListCtrl( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizer6->Add( list_patches, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	button_patches_moveup = new wxButton( m_panel6, wxID_ANY, wxT("Move up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( button_patches_moveup, 1, wxALL, 5 );

	button_patches_movedown = new wxButton( m_panel6, wxID_ANY, wxT("Move down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( button_patches_movedown, 1, wxALL, 5 );

	button_patches_remove = new wxButton( m_panel6, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( button_patches_remove, 1, wxALL, 5 );


	sbSizer6->Add( bSizer72, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	button_patch = new wxButton( m_panel6, wxID_ANY, wxT("Patch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( button_patch, 1, wxALL|wxEXPAND, 5 );

	button_unpatch = new wxButton( m_panel6, wxID_ANY, wxT("Unpatch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( button_unpatch, 1, wxALL, 5 );


	sbSizer6->Add( bSizer20, 0, wxEXPAND, 5 );

	statictext666 = new wxStaticText( m_panel6, wxID_ANY, wxT("Current output REZ path:"), wxDefaultPosition, wxDefaultSize, 0 );
	statictext666->Wrap( -1 );
	sbSizer6->Add( statictext666, 0, wxALL, 5 );

	label_output_rez = new wxStaticText( m_panel6, wxID_ANY, wxT("Not set"), wxDefaultPosition, wxDefaultSize, 0 );
	label_output_rez->Wrap( -1 );
	sbSizer6->Add( label_output_rez, 0, wxALL, 5 );


	m_panel6->SetSizer( sbSizer6 );
	m_panel6->Layout();
	sbSizer6->Fit( m_panel6 );
	m_splitter3->SplitHorizontally( m_panel51, m_panel6, 279 );
	bSizer71->Add( m_splitter3, 1, wxEXPAND, 5 );


	m_panel5->SetSizer( bSizer71 );
	m_panel5->Layout();
	bSizer71->Fit( m_panel5 );
	bSizer15->Add( m_panel5, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( bSizer15 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	menu_file = new wxMenu();
	wxMenuItem* menu_file_close;
	menu_file_close = new wxMenuItem( menu_file, ID_CLOSE, wxString( wxT("Close") ) , wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_close );

	m_menubar1->Append( menu_file, wxT("File") );

	menu_options = new wxMenu();
	wxMenuItem* refresh;
	refresh = new wxMenuItem( menu_options, ID_REFRESH, wxString( wxT("Refresh") ) + wxT('\t') + wxT("F5"), wxEmptyString, wxITEM_NORMAL );
	menu_options->Append( refresh );

	//wxMenuItem* menu_showPatchPreview;
	//menu_showPatchPreview = new wxMenuItem( menu_options, ID_SHOW_PATCH_PREVIEW, wxString( wxT("Show patch preview") ) , wxEmptyString, wxITEM_CHECK );
	//menu_options->Append( menu_showPatchPreview );
	//menu_showPatchPreview->Check( true );

	//wxMenuItem* testMenuItemSelectAll;
	//testMenuItemSelectAll = new wxMenuItem( menu_options, ID_TEST_MENU_ITEM__SELECT_ALL, wxString( wxT("Test Menu Item - Select All") ) + wxT('\t') + wxT("Ctrl+A"), wxEmptyString, wxITEM_NORMAL );
	//menu_options->Append( testMenuItemSelectAll );

	menu_options->AppendSeparator();

	wxMenuItem* changeBackedUpRez;
	changeBackedUpRez = new wxMenuItem( menu_options, ID_CHANGE_BACKED_UP_REZ_, wxString( wxT("Change backed up REZ ...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_options->Append( changeBackedUpRez );

	wxMenuItem* changeOutputRezPath;
	changeOutputRezPath = new wxMenuItem( menu_options, ID_CHANGE_OUTPUT_REZ_PATH_, wxString( wxT("Change output REZ path ...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_options->Append( changeOutputRezPath );

	m_menubar1->Append( menu_options, wxT("Options") );

	help = new wxMenu();
	wxMenuItem* about;
	about = new wxMenuItem( help, ID_ABOUT, wxString( wxT("About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	help->Append( about );

	m_menubar1->Append( help, wxT("Help") );

	this->SetMenuBar( m_menubar1 );

	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	button_pool_apply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolApply ), NULL, this );
	button_pool_takeoff->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolTakeOff ), NULL, this );
	button_pool_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolDelete ), NULL, this );
	button_pool_newpatch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolNewPatch ), NULL, this );
	button_patches_moveup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchMoveUp ), NULL, this );
	button_patches_movedown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchMoveDown ), NULL, this );
	button_patches_remove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchRemove ), NULL, this );
	button_patch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatch ), NULL, this );
	button_unpatch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedUnpatch ), NULL, this );
	this->Connect( menu_file_close->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuClose ) );
	this->Connect( refresh->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuRefresh ) );
	//this->Connect( menu_showPatchPreview->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuShowPreview ) );
	//this->Connect( testMenuItemSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedHiddenMenuSelectAll ) );
	this->Connect( changeBackedUpRez->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuChangeBackupREZ ) );
	this->Connect( changeOutputRezPath->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuChangeOutputREZ ) );
	this->Connect( about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuAbout ) );
}

MainFrameTemplate::~MainFrameTemplate()
{
	// Disconnect Events
	button_pool_apply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolApply ), NULL, this );
	button_pool_takeoff->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolTakeOff ), NULL, this );
	button_pool_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolDelete ), NULL, this );
	button_pool_newpatch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPoolNewPatch ), NULL, this );
	button_patches_moveup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchMoveUp ), NULL, this );
	button_patches_movedown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchMoveDown ), NULL, this );
	button_patches_remove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatchRemove ), NULL, this );
	button_patch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedPatch ), NULL, this );
	button_unpatch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameTemplate::PressedUnpatch ), NULL, this );
	this->Disconnect( ID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuClose ) );
	this->Disconnect( ID_REFRESH, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuRefresh ) );
	//this->Disconnect( ID_SHOW_PATCH_PREVIEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuShowPreview ) );
	//this->Disconnect( ID_TEST_MENU_ITEM__SELECT_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedHiddenMenuSelectAll ) );
	this->Disconnect( ID_CHANGE_BACKED_UP_REZ_, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuChangeBackupREZ ) );
	this->Disconnect( ID_CHANGE_OUTPUT_REZ_PATH_, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuChangeOutputREZ ) );
	this->Disconnect( ID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameTemplate::PressedMenuAbout ) );

}
