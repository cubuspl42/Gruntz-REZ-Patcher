///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/splitter.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_CLOSE 1000
#define ID_REFRESH 1001
#define ID_SHOW_PATCH_PREVIEW 1002
#define ID_TEST_MENU_ITEM__SELECT_ALL 1003
#define ID_CHANGE_BACKED_UP_REZ_ 1004
#define ID_CHANGE_OUTPUT_REZ_PATH_ 1005
#define ID_ABOUT 1006

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameTemplate
///////////////////////////////////////////////////////////////////////////////
class MainFrameTemplate : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel5;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel51;
		wxListCtrl* list_pool;
		wxButton* button_pool_apply;
		wxButton* button_pool_takeoff;
		wxButton* button_pool_delete;
		wxButton* button_pool_newpatch;
		wxPanel* m_panel6;
		wxListCtrl* list_patches;
		wxButton* button_patches_moveup;
		wxButton* button_patches_movedown;
		wxButton* button_patches_remove;
		wxButton* button_patch;
		wxButton* button_unpatch;
		wxStaticText* statictext666;
		wxStaticText* label_output_rez;
		wxMenuBar* m_menubar1;
		wxMenu* menu_file;
		wxMenu* menu_options;
		wxMenu* help;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, overide them in your derived class
		virtual void PressedPoolApply( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPoolTakeOff( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPoolDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPoolNewPatch( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPatchMoveUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPatchMoveDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPatchRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedPatch( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedUnpatch( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuShowPreview( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedHiddenMenuSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuChangeBackupREZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuChangeOutputREZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedMenuAbout( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameTemplate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 976,714 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrameTemplate();

		void m_splitter3OnIdle( wxIdleEvent& )
		{
			//m_splitter3->SetSashPosition( 279 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrameTemplate::m_splitter3OnIdle ), NULL, this );
		}

};

#endif //__NONAME_H__
