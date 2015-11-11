///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H3__
#define __NONAME_H3__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PatchingDialogTemplate
///////////////////////////////////////////////////////////////////////////////
class PatchingDialogTemplate : public wxDialog
{
	private:

	protected:
		wxStaticText* label_progress;
		wxGauge* gauge_total;
		wxTextCtrl* text_log;
		wxButton* button_ok;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDialogClose( wxCloseEvent& event ) { event.Skip(); }


	public:

		PatchingDialogTemplate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Patching"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 664,312 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~PatchingDialogTemplate();

};

#endif //__NONAME_H__
