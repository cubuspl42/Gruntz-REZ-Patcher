/*
 * main.cpp
 *
 *  Created on: 06-11-2012
 *      Author: tomek
 */

#include <wx/wfstream.h>
#include <wx/msgdlg.h>

#include "main.h"

IMPLEMENT_APP(MyApp)

MyApp::MyApp(): wxApp(),
				frame(NULL),
				m_config("", "", GetExePath() + "grp.ini")
{
	m_config.SetPath("/gui");
}

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	frame = new MainFrame();
	frame->Show();
	frame->SetIcon(wxICON(aaa_tomalla_icon));

	//wxMessageBox(wxString::Format("%d %d %d", sizeof(unsigned int*), sizeof(char*), sizeof(wxApp*)));

	//SKOMENTOWANE
	//Pomysla³em sobie, ¿e ewentualne sprawdzenia bêd¹ mia³y miejsce po wcisniêciu przycisku PATCH,
	//a nie podczas startu programu

	/*wxString strREZPath = frame->GetREZPath();
	if(strREZPath == "")
	{
		 //nie ma ustawionego REZ'a (np. pierwsze uruchomienie programu)
		ChangeREZDialog D(frame);
		D.ModeBackup();
		D.ShowModal();
	} else if(!wxFileExists("BACKUP.REZ"))
	{
		//jest ustawiony output REZ, ale nie ma oryginalnego jako BACKUP - trzeba wybrac na nowo
		int nRes = wxMessageBox("There is no original REZ file backed up! Would you like to pick a new one?", "No backup file", wxYES_NO);
		if(nRes == wxYES)
		{
			ChangeREZDialog D(frame);
			D.ModeBackup();
			D.ShowModal();
		}
	}*/

	return true;
}
