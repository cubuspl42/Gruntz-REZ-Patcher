/*
 * MainFrame.h
 *
 *  Created on: 06-11-2012
 *      Author: tomek
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <vector>
#include <wx/fileconf.h>

#include "templates/frame_main/noname.h"
#include "templates/dialog_change_rez/noname.h"
#include "templates/dialog_patching/noname.h"

//TODO: CPatch powinien przechowywac liczbê plików w patchu
//TODO: CPatch powinien ³adowac z pliku ZIP jakis specjalny plik, np. 'patch.txt' i z niego zczytywac metryczkê o autorze itd.
class CPatch {
public:
	//CPatch(): m_strPath(""), m_bIsOk(true) {m_constructor_debug();}
	CPatch(wxString str, bool bUsed = false);
	//CPatch();
	//CPatch(wxString str, bool b): m_strPath(str), m_bIsOk(b) {m_constructor_debug();}
private:
	void m_constructor_debug();

public:
	~CPatch();

	inline wxString GetPath() const {
		return m_strPath;
	}
	inline wxString GetName() const {
		if(m_bIsOk)
			return m_strName;
		return "";
	}
	inline wxString GetAuthor() const {
		if(m_bIsOk)
			return m_strAuthor;
		return "";
	}
	inline unsigned int GetFilesCount() const {
		return m_nFiles;
	}
	inline wxString GetDataStamp() const {
		if(m_bIsOk)
			return wxString::Format("%u", GetFilesCount());
		return "-";
	}
	inline bool IsOk() const {
		return m_bIsOk;
	}
	inline bool IsUsed() const {
		return m_bIsUsed;
	}

	inline void SetUsed(bool used) {
		m_bIsUsed = used;
	}

	void Refresh();

private:
	wxString m_strPath;
	wxString m_strAuthor;
	wxString m_strName; //patch name
	unsigned int m_nFiles; //ilosc plików w patchu
	bool m_bIsOk;
	bool m_bIsUsed; //czy jest u¿yty jako patch w liscie PATCHES
};


class MainFrame: public MainFrameTemplate
{
public:
	std::vector<CPatch*> vPatches;
	//std::vector<unsigned int> vApplyPatches;
private:
	wxString m_strREZPath;

public:
	MainFrame();
	~MainFrame();

	inline wxString GetREZPath() const {
		return m_strREZPath;
	}
	inline void SetREZPath(wxString str) {
		label_output_rez->SetLabel(str);
		m_strREZPath = str;
	}

	virtual void PressedPoolApply( wxCommandEvent& event );
	virtual void PressedPoolTakeOff( wxCommandEvent& event );
	virtual void PressedPoolDelete( wxCommandEvent& event );
	virtual void PressedPoolNewPatch( wxCommandEvent& event );
	virtual void PressedPatchMoveUp( wxCommandEvent& event );
	virtual void PressedPatchMoveDown( wxCommandEvent& event );
	virtual void PressedPatchRemove( wxCommandEvent& event );
	virtual void PressedPatch( wxCommandEvent& event );
	virtual void PressedUnpatch( wxCommandEvent& event );
	virtual void PressedMenuClose( wxCommandEvent& event )			{ Close(); }
	virtual void PressedMenuShowPreview( wxCommandEvent& event )	{ event.Skip(); }
	virtual void PressedMenuChangeOutputREZ( wxCommandEvent& event );
	virtual void PressedMenuChangeBackupREZ( wxCommandEvent& event );
	virtual void PressedMenuAbout( wxCommandEvent& event );
	virtual void PressedMenuRefresh( wxCommandEvent& event );
	virtual void PressedMenuRefresh() { wxCommandEvent ev; PressedMenuRefresh(ev); }

	void DroppedFilesPool(wxDropFilesEvent& event);
	void DroppedFilesPatches(wxDropFilesEvent& event);

private:
	void RefreshLists(); //czysci obie listy POOL i PATCHES i ³aduje je od nowa na podstawie danych z vPatches

	CPatch* AddPatch(wxString str) {
		for(std::vector<CPatch*>::iterator it = vPatches.begin(); it != vPatches.end(); it++)
			if((*it)->GetPath() == str)
				return (*it);

		CPatch* pPatch = new CPatch(str);
		vPatches.push_back(pPatch);
		return pPatch;
	}
};

class ChangeREZDialog: public ChangeREZDialogTemplate
{
public:
	ChangeREZDialog(wxWindow* parent);
	~ChangeREZDialog();

	inline void ModeOutput() {
		label_description->SetLabel("Choose the output location for the REZ file.");
		checkbox_optional->SetLabel("If present, back it up and use when patching.");
		checkbox_optional->SetValue(false);
		SetTitle("Choose the output REZ file");
		m_mode = DMODE_OUTPUT;
	}

	inline void ModeBackup() {
		label_description->SetLabel("Choose the original and unmodified REZ file to back it up.");
		checkbox_optional->SetLabel("Set this REZ file as an output REZ.");
		checkbox_optional->SetValue(true);
		SetTitle("Choose the original REZ file");
		m_mode = DMODE_BACKUP;
	}

private:
	MainFrame* GetCastedParent() const;

	virtual void PressedBrowse( wxCommandEvent& event );
	virtual void PressedCancel( wxCommandEvent& event );
	virtual void PressedOK( wxCommandEvent& event );

	enum DMODE {
		DMODE_NONE = 0,
		DMODE_OUTPUT,
		DMODE_BACKUP
	};

	DMODE m_mode;
};

class PatchingDialog: public PatchingDialogTemplate
{
private:
	std::vector<CPatch*> vPatches;
	void Log(wxString);
	void Finalize();

public:
	PatchingDialog(wxWindow* parent, const wxSize& size  = wxSize(664, 312));
	~PatchingDialog();

	inline void AddPatch(CPatch* pPatch) {
		vPatches.push_back(pPatch);
	}

	void Run();
};

//=========================================================================================================

class AboutDialog : public wxDialog
{
private:
	virtual void OnPressedOK( wxCommandEvent& event ) { event.Skip(); }

public:
	AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 570,339 ), long style = wxDEFAULT_DIALOG_STYLE );
	~AboutDialog();

};


#endif /* MAINFRAME_H_ */
