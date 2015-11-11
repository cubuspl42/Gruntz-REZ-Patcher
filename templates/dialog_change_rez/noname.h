///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H2__
#define __NONAME_H2__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/gauge.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ChangeREZDialogTemplate
///////////////////////////////////////////////////////////////////////////////
class ChangeREZDialogTemplate : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel7;
		wxStaticText* label_description;
		wxTextCtrl* textctrl_path;
		wxButton* button_browse;
		wxGauge* m_gauge1;
		wxCheckBox* checkbox_optional;
		wxStaticText* label_progress;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

		// Virtual event handlers, overide them in your derived class
		virtual void PressedBrowse( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void PressedOK( wxCommandEvent& event ) { event.Skip(); }


	public:

		ChangeREZDialogTemplate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Change output REZ ..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 445,180 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ChangeREZDialogTemplate();

};

#endif //__NONAME_H__
