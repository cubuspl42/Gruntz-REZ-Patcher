/*
 * main.h
 *
 *  Created on: 07-11-2012
 *      Author: tomek
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif

#include "MainFrame.h"

//#include <wx/zipstrm.h>
//#include <wx/wfstream.h>
//#include <wx/txtstrm.h>
#include <wx/stdpaths.h>

class MyApp : public wxApp
{
public:
	/*inline MainFrame* GetFrame() const {
		return frame;
	}*/

	inline wxFileConfig* Config() {
		return &m_config;
	}

	MyApp();

	wxString GetExePath() const {
		wxString strExePath = wxStandardPaths::Get().GetExecutablePath();
		int i = strExePath.find_last_of("\\");
		return strExePath.substr(0, i+1);
	}

    virtual bool OnInit();

private:
	MainFrame* frame;
	wxFileConfig m_config;
};

#endif /* MAIN_H_ */
