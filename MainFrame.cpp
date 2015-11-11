/*
 * MainFrame.cpp
 *
 *  Created on: 06-11-2012
 *      Author: tomek
 */

#include <vector>
using namespace std;

#include <wx/hyperlink.h>	//for About Dialog
#include <wx/mstream.h>		//for CPatch::Refresh - czytanie konfiga do pamiêci i czytanie fo
#include <wx/zipstrm.h>		//for PatchingDialog
#include <wx/datetime.h>	//for PatchingDialog (time in log textctrl)
#include "wx/md5.h"

#include "CREZ.h"
#include "MainFrame.h"
#include "utils.h"
#include "main.h"

#define COL_DEFAULT		(*wxWHITE)
#define COL_ERROR 		wxColor(255, 237, 237)
#define COL_ERROR_USED 	wxColor(219, 219, 255)
#define COL_USED_ERROR	COL_ERROR_USED
#define COL_USED		wxColor(168, 168, 255)

#define DIALOG_ERROR(str) 	{ wxMessageDialog error(this, str, "Error", wxOK|wxICON_ERROR); error.ShowModal(); }

wxString GetTimeStamp() {
	tm s;
	wxDateTime::GetTmNow(&s);
	return wxString::Format("[%02d:%02d:%02d]", s.tm_hour, s.tm_min, s.tm_sec);
}

class wxLogOff
{
public:
	wxLogOff(): m_bOn(false) { On(); }
    ~wxLogOff() { Off(); }

    void On() {
    	if(!m_bOn)
    	{
    		m_bFlagOld = wxLog::EnableLogging(false);
    		m_bOn = true;
    	}
    }

    void Off() {
    	if(m_bOn)
    	{
    		wxLog::EnableLogging(m_bFlagOld);
    		m_bOn = false;
    	}
    }

private:
    bool m_bFlagOld; // the previous value of the wxLog::ms_doLog
    bool m_bOn;
};

//=========================================================================

class CREZ: public CREZBase {
public:
	CREZ(wxString str): CREZBase(str),
		m_pGauge(NULL), m_pLog(NULL)
	{}
	virtual ~CREZ() {}

	inline void SetLog(wxTextCtrl* p) {
		m_pLog = p;
	}
	inline void SetGauge(wxGauge* p) {
		m_pGauge = p;
	}

	inline void List() const {
		//if(IsLoaded())
		//	pRootDirectory->List(0);
	}

protected:
	wxGauge* m_pGauge;
	wxTextCtrl* m_pLog;

	virtual void ProgressInitialize();
	virtual void ProgressUpdate();
	virtual void Log(REZ_ERROR eEr, REZErr* pEr);
};

void CREZ::ProgressInitialize()
{
	if(m_pGauge != NULL)
	{
		m_pGauge->SetValue(0);
		m_pGauge->SetRange(pRootDirectory->GetNodesCount());
	}
}

void CREZ::ProgressUpdate()
{
	if(m_pGauge != NULL)
	{
		m_pGauge->SetValue(m_nNodesRead);
		wxTheApp->Yield();
	}
}

void CREZ::Log(REZ_ERROR eEr, REZErr* pEr)
{
	if(m_pLog != NULL)
	{
		switch(eEr)
		{
		case RER_LONG_EXT:
			m_pLog->AppendText(wxString::Format("%s Warning: the file %s had too long extension. Took last 4 characters only\n", GetTimeStamp().c_str(), pEr->strFile.c_str()));
			break;
		case RER_DEC_WRONG_ID:
			m_pLog->AppendText(wxString::Format("%s Error when decoding REZ file: encountered unknown entry ID (%d@%u)\n", GetTimeStamp().c_str(), pEr->nID, pEr->nOffset));
			break;

		case RER_NO_ERROR:
			break;
		}
	}
}

//=========================================================================
#include "xpm\xpm_about.h"

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style): wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 216, 228, 248 ) );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBitmap* m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, wxBitmap(xpm_about), wxDefaultPosition, wxSize(-1, -1), 0 );
	bSizer12->Add( m_bitmap1, 0, wxALIGN_CENTER|wxALL, 15 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	wxStaticText* m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Gruntz REZ Patcher"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( 22, 74, 90, 92, false, wxT("Trebuchet MS") ) );

	bSizer13->Add( m_staticText7, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* m_staticText71 = new wxStaticText( this, wxID_ANY, wxT("v1.0.0           "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText71->Wrap( -1 );
	m_staticText71->SetFont( wxFont( 12, 74, 93, 90, false, wxT("Trebuchet MS") ) );

	bSizer13->Add( m_staticText71, 0, wxALIGN_RIGHT|wxALL, 5 );

	wxStaticText* m_staticText711 = new wxStaticText( this, wxID_ANY, wxT("The tool for patching the REZ files\nDesigned and tested for Gruntz, but will probably\nwork with Claw and Get Mediaval as well"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText711->Wrap( -1 );
	m_staticText711->SetFont( wxFont( 12, 74, 93, 90, false, wxT("Trebuchet MS") ) );

	bSizer13->Add( m_staticText711, 0, wxALL|wxEXPAND, 5 );


	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer12, 1, wxEXPAND, 5 );

	wxStaticText* m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("by Tomalla"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( 20, 74, 90, 92, false, wxT("Trebuchet MS") ) );

	bSizer16->Add( m_staticText11, 0, wxALL|wxEXPAND, 5 );

	wxHyperlinkCtrl* m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("http://datashenanigans.blogspot.com"), wxT("http://datashenanigans.blogspot.com"), wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_CENTRE|wxHL_DEFAULT_STYLE );
	m_hyperlink1->SetFont( wxFont( 12, 74, 93, 90, false, wxT("Trebuchet MS") ) );

	bSizer16->Add( m_hyperlink1, 0, wxALL|wxEXPAND, 8 );

	wxButton* m_button10 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button10->SetDefault();
	bSizer16->Add( m_button10, 0, wxALIGN_CENTER|wxALL, 15 );


	this->SetSizer( bSizer16 );
	this->Layout();

	this->Centre( wxBOTH );
}

AboutDialog::~AboutDialog() {}

//===================================================================================================
//===================================================================================================
//===================================================================================================

//MainFrameTemplate( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 976,714 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
MainFrame::MainFrame():	MainFrameTemplate(NULL, wxID_ANY, "Gruntz REZ Patcher", wxDefaultPosition, wxSize(CONFIG->Read("width", 976), CONFIG->Read("height", 714)))
{
	//=============== GUI SETTINGS ==============
	CONFIG->SetPath("/gui");
	int nWidth = CONFIG->Read("width", 976);
	int nHeight = CONFIG->Read("height", 714);

	//m_splitter1->SetSashPosition(CONFIG->Read("sash1", nWidth/4));
	//m_splitter2->SetSashPosition(CONFIG->Read("sash2", nWidth/2));
	m_splitter3->SetSashPosition(CONFIG->Read("sash3", nHeight/2));

	//adding columns and drop file feature
	list_pool->InsertColumn(0, "Patch name");
	list_pool->InsertColumn(1, "Author");
	list_pool->InsertColumn(2, "Files");
	list_pool->InsertColumn(3, "Path");
	list_pool->DragAcceptFiles(true);
	list_pool->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(MainFrame::DroppedFilesPool), NULL, this);

	list_patches->InsertColumn(0, "Patch name");
	list_patches->InsertColumn(1, "Author");
	list_patches->InsertColumn(2, "Files");
	list_patches->InsertColumn(3, "Path");
	list_patches->DragAcceptFiles(true);
	list_patches->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(MainFrame::DroppedFilesPatches), NULL, this);

	//*** reading the columns' width ***
	int n=0;
	int key = CONFIG->Read("pool_c0", -1);
	while(key != (-1))
	{
		list_pool->SetColumnWidth(n, key);
		n++;
		key = CONFIG->Read(wxString::Format("pool_c%d", n), -1);
	}

	n=0;
	key = CONFIG->Read("patches_c0", -1);
	while(key != (-1))
	{
		list_patches->SetColumnWidth(n, key);
		n++;
		key = CONFIG->Read(wxString::Format("patches_c%d", n), -1);
	}

	//===================== REZ FILE ================================
	CONFIG->SetPath("/rez");
	SetREZPath(CONFIG->Read("path", ""));

	//======================== READING PATCHES FROM CONFIG ========================

	CONFIG->SetPath("/pool");
	{
		int n=1;
		wxString key = CONFIG->Read("path1", "");
		while(key != "")
		{
			CPatch* pPatch = new CPatch(key);
			vPatches.push_back(pPatch);

			wxListItem Item;
			Item.SetId(n-1);
			Item.SetColumn(0);
			Item.SetText(pPatch->GetPath());
			Item.SetData(pPatch); //adres to struktury CPatch
			list_pool->InsertItem(Item);

			n++;
			key = CONFIG->Read(wxString::Format("path%d", n), "");
		}
	}

	CONFIG->SetPath("/apply");
	{
		int n=1;
		int nPathIndex = CONFIG->Read("patch1", (-1));
		while(nPathIndex != (-1))
		{
			if(nPathIndex > vPatches.size())
			{
				n++;
				nPathIndex = CONFIG->Read(wxString::Format("patch%d", n), (-1));
				continue;
			}

			CPatch* pPatch = vPatches[nPathIndex-1];
			pPatch->SetUsed(true);

			wxListItem Item;
			Item.SetId(n-1);
			Item.SetColumn(0);
			Item.SetText(pPatch->GetPath());
			Item.SetData(pPatch); //adres to struktury CPatch
			list_patches->InsertItem(Item);

			n++;
			nPathIndex = CONFIG->Read(wxString::Format("patch%d", n), (-1));
		}
	}

	RefreshLists(); //setting correct colors and fonts
}

MainFrame::~MainFrame()
{
	//writing the setting to INI file

	//============================== GUI SETTINGS ========================
	CONFIG->SetPath("/gui");
	wxSize clientSize = GetSize();
	CONFIG->Write("width", clientSize.GetWidth());
	CONFIG->Write("height", clientSize.GetHeight());
	//CONFIG->Write("sash1", m_splitter1->GetSashPosition());
	//CONFIG->Write("sash2", m_splitter2->GetSashPosition());
	CONFIG->Write("sash3", m_splitter3->GetSashPosition());

	//zapisujemy kolumny z list POOL i PATCH
	for(int i = 0; i<list_pool->GetColumnCount(); i++)
		CONFIG->Write(wxString::Format("pool_c%d", i), list_pool->GetColumnWidth(i));
	for(int i = 0; i<list_patches->GetColumnCount(); i++)
		CONFIG->Write(wxString::Format("patches_c%d", i), list_patches->GetColumnWidth(i));

	//============================= REZ FILE =============================
	CONFIG->SetPath("/rez");
	CONFIG->Write("path", GetREZPath());

	//======================== PATCHES AND POOL ENTRIES ===============================
	CONFIG->DeleteGroup("/pool");
	CONFIG->DeleteGroup("/apply");

	CONFIG->SetPath("/pool");
	for(int i=0; i<list_pool->GetItemCount(); i++)
	{
		CPatch* pPatch = reinterpret_cast<CPatch*>(list_pool->GetItemData(i));
		CONFIG->Write(wxString::Format("path%d", i+1), pPatch->GetPath());
	}

	CONFIG->SetPath("/apply");
	for(int i=0; i<list_patches->GetItemCount(); i++)
	{
		bool bFound = false;
		long int p = list_patches->GetItemData(i);
		for(int k=0; k<list_pool->GetItemCount(); k++)
			if(list_pool->GetItemData(k) == p)
			{
				CONFIG->Write(wxString::Format("patch%d", i+1), k+1);
				bFound = true;
				break;
			}

		if(!bFound)
		{
			wxMessageDialog error(this, wxString::Format("A pool entry #%d \"%s\" does not have a corresponding patch, aborting.", i, list_patches->GetItemText(i).c_str()), "Error", wxOK|wxICON_ERROR);
			error.ShowModal();
			break;
		}
	}

	//================================================
	//Deleting CPatches from memory

	for(int i=0; i<vPatches.size(); i++)
		delete vPatches[i];
}

void MainFrame::PressedPoolApply( wxCommandEvent& event )
{
	int nIndex = list_pool->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	while(nIndex != (-1))
	{
		unsigned int nData = list_pool->GetItemData(nIndex);
		CPatch* pPatch = reinterpret_cast<CPatch*>(nData);

		//sprawdzic, czy nie jest juz patch w liscie
		bool bCont = false;
		for(int i=0; i<list_patches->GetItemCount(); i++)
			if(list_patches->GetItemData(i) == nData)
			{
				bCont = true;
				break;
			}
		if(bCont)
		{
			nIndex = list_pool->GetNextItem(nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			continue;
		}

		/*if(pPatch->IsOk())
			list_pool->SetItemBackgroundColour(nIndex, COL_USED);
		else
			list_pool->SetItemBackgroundColour(nIndex, COL_ERROR_USED);*/

		wxListItem Item;
		Item.SetId(list_patches->GetItemCount());
		Item.SetColumn(0);
		Item.SetText(pPatch->GetPath());
		Item.SetData(pPatch); //adres to struktury CPatch
		list_patches->InsertItem(Item);

		pPatch->SetUsed(true);

		nIndex = list_pool->GetNextItem(nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	//CPatch* p = (CPatch*)list_pool->GetItemData(n);
	RefreshLists();
	list_pool->SetFocus();
}

void MainFrame::PressedPoolTakeOff( wxCommandEvent& event )
{
	int nIndex = list_pool->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	while(nIndex != (-1))
	{
		unsigned int nData = list_pool->GetItemData(nIndex);
		CPatch* pPatch = reinterpret_cast<CPatch*>(nData);

		for(int i=0; i<list_patches->GetItemCount(); i++)
			if(list_patches->GetItemData(i) == nData)
			{
				list_patches->DeleteItem(i);
				break;
			}

		pPatch->SetUsed(false);

		nIndex = list_pool->GetNextItem(nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}

	RefreshLists();
	list_pool->SetFocus();
}

void MainFrame::PressedPoolDelete( wxCommandEvent& event )
{
	int nIndex = list_pool->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	while(nIndex != (-1))
	{
		unsigned int nData = list_pool->GetItemData(nIndex);
		CPatch* pPatch = reinterpret_cast<CPatch*>(nData);

		for(int i=0; i<list_patches->GetItemCount(); i++)
			if(list_patches->GetItemData(i) == nData)
			{
				list_patches->DeleteItem(i);
				break;
			}

		list_pool->DeleteItem(nIndex);

		//nie ma sobie co zaprz¹tac g³owy usuwaniem wpisu w vPatches - zrobi siê to automatycznie kiedy program bêdzie siê koñczy³
		pPatch->SetUsed(false);

		nIndex = list_pool->GetNextItem(nIndex-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}

	RefreshLists();
	list_pool->SetFocus();
}

void MainFrame::PressedPoolNewPatch( wxCommandEvent& event )
{
	//TODO: Pomys³: w menu dodac dwa przyciski na dodawanie plików GRP, ZIP oraz osobno folderów z danymi
	//		Przycisk New Patch dodawa³by tylko pliki *.GRB i *.ZIP

	wxFileDialog fd(this, "Choose a REZ file", GETAPP->GetExePath(), "", "Default (*.grp, *.zip)|*.grp;*.zip|Gruntz REZ Patcher files (*.grp)|*.grp|ZIP archives (*zip)|*.zip", wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
	if(fd.ShowModal() != wxID_CANCEL)
	{
		wxArrayString a;
		fd.GetFilenames(a);
		for(int i=0; i<a.size(); i++)
		{
			wxFileName fn(a[i]);
			wxString strExt = fn.GetExt().Lower();
			wxString strPath = a[i];
			if(strExt == "zip" || strExt == "grp")
			{
				bool bFound = false;
				for(int k=0; k<list_pool->GetItemCount(); k++)
				{
					CPatch* pPatch = reinterpret_cast<CPatch*>(list_pool->GetItemData(k));
					if(pPatch->GetPath() == strPath) //pozycja na liscie ju¿ jest
					{
						bFound = true;
						break;
					}
				}
				if(bFound)
					continue;

				CPatch* pPatch = AddPatch(a[i]); //if it's already in memory, get it's address

				wxListItem Item;
				Item.SetId(list_pool->GetItemCount());
				Item.SetData(pPatch);
				Item.SetState(wxLIST_STATE_SELECTED);
				list_pool->InsertItem(Item);
			}
		}

		RefreshLists();
		list_pool->SetFocus();
	}
}

void MainFrame::DroppedFilesPool(wxDropFilesEvent& event)
{
	for(int k=0; k<list_pool->GetItemCount(); k++)
		list_pool->SetItemState(k, 0, wxLIST_STATE_SELECTED); //deselect all of the items

	wxString* Files = event.GetFiles();

	for(int i=0; i < event.GetNumberOfFiles(); i++)
	{
		bool bCont = false;
		for(int k=0; k<list_pool->GetItemCount(); k++)
			if(reinterpret_cast<CPatch*>(list_pool->GetItemData(k))->GetPath() == Files[i])
			{
				bCont = true;
				break;
			}
		if(bCont)
			continue;

		if(wxFileExists(Files[i])) //jest to plik
		{
			wxFileName fn(Files[i]);
			if(fn.GetExt().CmpNoCase("zip") != 0
				&& fn.GetExt().CmpNoCase("grp") != 0)
				continue;

			CPatch* pPatch = new CPatch(Files[i]);
			vPatches.push_back(pPatch);

			wxListItem Item;
			Item.SetId(list_pool->GetItemCount());
			Item.SetData(pPatch); //adres to struktury CPatch
			Item.SetState(wxLIST_STATE_SELECTED);
			list_pool->InsertItem(Item);
		} else if(wxDirExists(Files[i])) //jest to dir
		{
			//TODO: mo¿liwosc wrzucenia folderów (PATCH i POOL)
		}
	}

	RefreshLists();
	list_pool->SetFocus();

	/*wxMessageBox(wxString::Format("Number: %d", event.GetNumberOfFiles()));
	for (int i = 0; i < event.GetNumberOfFiles(); i++)
	{
		wxMessageBox(event.GetFiles()[i]);
	}*/
}

void MainFrame::DroppedFilesPatches(wxDropFilesEvent& event)
{
	for(int k=0; k<list_patches->GetItemCount(); k++)
		list_patches->SetItemState(k, 0, wxLIST_STATE_SELECTED); //deselect all of the items

	wxString* Files = event.GetFiles();

	for(int i=0; i < event.GetNumberOfFiles(); i++)
	{
		bool bCont = false;
		for(int k=0; k<list_pool->GetItemCount(); k++)
			if(reinterpret_cast<CPatch*>(list_pool->GetItemData(k))->GetPath() == Files[i])
			{
				bCont = true;
				break;
			}
		if(bCont)
			continue;

		if(wxFileExists(Files[i]))
		{
			wxFileName fn(Files[i]);
			if(fn.GetExt().CmpNoCase("zip") != 0
				&& fn.GetExt().CmpNoCase("grp") != 0)
				continue;

			CPatch* pPatch = new CPatch(Files[i]);
			vPatches.push_back(pPatch);

			wxListItem Item;
			Item.SetId(list_pool->GetItemCount());
			Item.SetData(pPatch); //adres to struktury CPatch
			list_pool->InsertItem(Item);
			Item.SetState(wxLIST_STATE_SELECTED);
			list_patches->InsertItem(Item);

			pPatch->SetUsed(true);
		} else if(wxDirExists(Files[i]))
		{
			//TODO: mo¿liwosc wrzucenia folderów (PATCH i POOL)
		}
	}

	RefreshLists();
	list_patches->SetFocus();
}

void MainFrame::PressedPatchMoveUp( wxCommandEvent& event )
{
	vector<int> vSelection;
	{
		int nIndex = list_patches->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		while(nIndex != (-1))
		{
			vSelection.push_back(nIndex);
			nIndex = list_patches->GetNextItem(nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		}
	}

	//analizujemy od koñca
	for(vector<int>::iterator it = vSelection.begin(); it != vSelection.end(); it++)
	{
		int nIndex = (*it);

		//je¿eli pocz¹tkowy element listy, nic nie robimy
		if(nIndex == 0)
		{
			//wxMessageBox("Pocz¹tkowy element! Jajco");
			continue;
		}

		//je¿eli poprzedni element jest zaznaczony, upychamy elementy na koñcu - nic nie robimy
		bool bCont = false;
		for(int i=0; i<vSelection.size(); i++)
			if(vSelection[i] == nIndex-1)
			{
				//wxMessageBox(wxString::Format("Poprzedni element jest zajêty! Jajco\nAnalizowany element: %d, zajêty element: %d", nIndex, nIndex-1));
				bCont = true;
				continue;
			}
		if(bCont)
			continue;

		//CPatch* pPatch = reinterpret_cast<CPatch*>(list_patches->GetItemData(nIndex));

		//Kopiujemy element z listy ...

		wxListItem Item;
		Item.SetId(nIndex);
		Item.SetMask(wxLIST_MASK_DATA);
		list_patches->GetItem(Item);
		Item.SetState(wxLIST_STATE_SELECTED);

		//... i wklejamy z kolejnym indeksem
		list_patches->DeleteItem(nIndex);
		Item.SetId(nIndex-1);
		list_patches->InsertItem(Item);

		(*it) -= 1;
	}

	RefreshLists();
	list_patches->SetFocus();
}

void MainFrame::PressedPatchMoveDown( wxCommandEvent& event )
{
	vector<int> vSelection;
	{
		int nIndex = list_patches->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		while(nIndex != (-1))
		{
			vSelection.push_back(nIndex);
			nIndex = list_patches->GetNextItem(nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		}
	}

	//analizujemy od koñca
	for(vector<int>::reverse_iterator rit = vSelection.rbegin(); rit != vSelection.rend(); rit++)
	{
		int nIndex = (*rit);

		//je¿eli koñcowy element, nic nie robimy
		if(nIndex == list_patches->GetItemCount()-1)
		{
			//wxMessageBox("Koncowy element! Jajco");
			continue;
		}

		//je¿eli nastêpny element jest zaznaczony, upychamy elementy na koñcu - nic nie robimy
		bool bCont = false;
		for(int i=0; i<vSelection.size(); i++)
			if(vSelection[i] == nIndex+1)
			{
				//wxMessageBox(wxString::Format("Nastêpny element jest zajêty! Jajco\nAnalizowany element: %d, zajêty element: %d", nIndex, nIndex+1));
				bCont = true;
				continue;
			}
		if(bCont)
			continue;

		//CPatch* pPatch = reinterpret_cast<CPatch*>(list_patches->GetItemData(nIndex));

		//Kopiujemy element z listy ...
		wxListItem Item;
		Item.SetId(nIndex);
		Item.SetMask(wxLIST_MASK_DATA);
		list_patches->GetItem(Item);
		Item.SetState(wxLIST_STATE_SELECTED);

		//... i wklejamy z kolejnym indeksem
		list_patches->DeleteItem(nIndex);
		Item.SetId(nIndex+1);
		list_patches->InsertItem(Item);

		(*rit) += 1;
	}

	RefreshLists();
	list_patches->SetFocus();
}

//TODO: CREZ: Wykrywanie konfliktów pomiêdzy zawartosci¹ patchy
void MainFrame::PressedPatchRemove( wxCommandEvent& event )
{
	int nIndex = list_patches->GetNextItem((-1), wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	while(nIndex != (-1))
	{
		int nData = list_patches->GetItemData(nIndex);
		CPatch* pPatch = reinterpret_cast<CPatch*>(nData);

		list_patches->DeleteItem(nIndex);
		pPatch->SetUsed(false);

		nIndex = list_patches->GetNextItem(nIndex-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}

	RefreshLists();
	list_patches->SetFocus();
}

void MainFrame::PressedMenuChangeOutputREZ( wxCommandEvent& event ) {
	ChangeREZDialog D(this);
	D.ModeOutput();
	D.ShowModal();
}

void MainFrame::PressedMenuChangeBackupREZ( wxCommandEvent& event ) {
	ChangeREZDialog D(this);
	D.ModeBackup();
	D.ShowModal();
}

void MainFrame::PressedUnpatch( wxCommandEvent& event )
{
	if(GetREZPath() == "")
	{
		int nRes = wxMessageBox("There is no output REZ file specified! Would you like to choose an output REZ file?", "No output REZ file", wxYES_NO);
		if(nRes != wxYES)
			return;
		ChangeREZDialog D(this);
		D.ModeOutput();
		if(D.ShowModal() != wxOK)
			return;
	}

	if(!wxFileExists("BACKUP.REZ"))
	{
		int nRes = wxMessageBox("There is no backup REZ file stored! Would you like to pick a new one?", "No backup REZ file", wxYES_NO);
		if(nRes != wxYES)
			return;
		ChangeREZDialog D(this);
		D.ModeBackup();
		if(D.ShowModal() != wxOK)
			return;
	}

	wxFile fileOutput;
	fileOutput.Create(GetREZPath(), true);
	wxFile fileBackup;
	fileBackup.Open("BACKUP.REZ");

	const int nBufferSize = 5*1024*512; //2.5MB
	unsigned char* buffer = new unsigned char[nBufferSize];
	while(!fileBackup.Eof())
	{
		unsigned int nRead = fileBackup.Read(buffer, nBufferSize);
		fileOutput.Write(buffer, nRead);
	}
	delete[] buffer;

	wxMessageBox("The original REZ file has just been restored.");
}

void MainFrame::PressedPatch( wxCommandEvent& event )
{
	if(!wxFileExists("BACKUP.REZ"))
	{
		int nRes = wxMessageBox("There is no backup REZ file stored! Would you like to pick a new one?", "No backup REZ file", wxYES_NO);
		if(nRes != wxYES)
			return;
		ChangeREZDialog D(this);
		D.ModeBackup();
		if(D.ShowModal() != wxOK)
			return;
	}

	if(GetREZPath() == "")
	{
		int nRes = wxMessageBox("There is no output REZ file specified! Would you like to choose an output REZ file?", "No output REZ file", wxYES_NO);
		if(nRes != wxYES)
			return;
		ChangeREZDialog D(this);
		D.ModeOutput();
		if(D.ShowModal() != wxOK)
			return;
	}

	PressedMenuRefresh(); //force list refresh

	CONFIG->SetPath("/gui");
	PatchingDialog D(this, wxSize(CONFIG->Read("pwidth", 664), CONFIG->Read("pheight", 312)));

	for(int i=0; i<list_patches->GetItemCount(); i++)
		D.AddPatch(reinterpret_cast<CPatch*>(list_patches->GetItemData(i)));

	wxWindowDisabler* pDisable = new wxWindowDisabler(&D);
	D.Run();
	delete pDisable;

	D.ShowModal();

	/*CREZ Rez("MYREZ1.REZ");
	if(Rez.IsLoaded())
	{
		wxString strNew = "KUUUURWA YAAAAAK!\n ... znaczy ... tak\n\nKurwa nie czepiaj sie mnie, dobra??";
		Rez.UpdateFile("f2\\f1b.txt", (unsigned char*)strNew.c_str(), strNew.Length());
		strNew = "Jakis tam nowy tekst. \n\n£otever";
		Rez.UpdateFile("f5\\nowy.txt", (unsigned char*)strNew.c_str(), strNew.Length());
		Rez.UpdateDir("f85\\f666\\infinity\\");
		Rez.Save("MYREZ2.REZ");
	}*/
}

void MainFrame::PressedMenuAbout( wxCommandEvent& event )
{
	AboutDialog D(this);
	D.ShowModal();
}

void MainFrame::PressedMenuRefresh( wxCommandEvent& event )
{
	for(vector<CPatch*>::iterator it = vPatches.begin(); it != vPatches.end(); it++)
	{
		CPatch* pPatch = (*it);
		pPatch->Refresh();
	}

	RefreshLists();
}

void MainFrame::RefreshLists()
{
	//POOL
	for(int i=0; i<list_pool->GetItemCount(); i++)
	{
		CPatch* pPatch = reinterpret_cast<CPatch*>(list_pool->GetItemData(i));

		//list_pool->InsertColumn(0, "Patch name");
		//list_pool->InsertColumn(1, "Author");
		//list_pool->InsertColumn(2, "Files/Directories");
		//list_pool->InsertColumn(3, "Path");
/*
		//w³asciwe teksty w wierszu
		wxListItem Item;
		Item.SetId(i);
		Item.SetColumn(0);
		Item.SetText(pPatch->GetPath());
		Item.SetData(pPatch); //adres to struktury CPatch
		list_pool->InsertItem(Item);*/

		list_pool->SetItem(i, 0, pPatch->GetName());
		list_pool->SetItem(i, 1, pPatch->GetAuthor());
		list_pool->SetItem(i, 2, pPatch->GetDataStamp());
		list_pool->SetItem(i, 3, pPatch->GetPath());

		//kolor t³a pozycji i czcionka
		if(pPatch->IsOk())
			list_pool->SetItemFont(i, *wxNORMAL_FONT);
		else
			list_pool->SetItemFont(i, *wxITALIC_FONT);

		if(pPatch->IsUsed())
		{
			if(pPatch->IsOk())
				list_pool->SetItemBackgroundColour(i, COL_USED);
			else
				list_pool->SetItemBackgroundColour(i, COL_ERROR_USED);
		} else
		{
			if(pPatch->IsOk())
				list_pool->SetItemBackgroundColour(i, COL_DEFAULT);
			else
				list_pool->SetItemBackgroundColour(i, COL_ERROR);
		}
	}

	//PATCHES
	for(int i=0; i<list_patches->GetItemCount(); i++)
	{
		CPatch* pPatch = reinterpret_cast<CPatch*>(list_patches->GetItemData(i));

		list_patches->SetItem(i, 0, pPatch->GetName());
		list_patches->SetItem(i, 1, pPatch->GetAuthor());
		list_patches->SetItem(i, 2, pPatch->GetDataStamp());
		list_patches->SetItem(i, 3, pPatch->GetPath());

		if(pPatch->IsOk())
		{
			list_patches->SetItemFont(i, *wxNORMAL_FONT);
			list_patches->SetItemBackgroundColour(i, COL_DEFAULT);
		}
		else
		{
			list_patches->SetItemFont(i, *wxITALIC_FONT);
			list_patches->SetItemBackgroundColour(i, COL_ERROR);
		}
	}
}


//====================================================================
//======================== CHANGE REZ DIALOG =========================
//====================================================================

ChangeREZDialog::ChangeREZDialog(wxWindow* parent):
		ChangeREZDialogTemplate(parent)
{
	textctrl_path->SetValue(GetCastedParent()->GetREZPath());
	ModeBackup();
}

ChangeREZDialog::~ChangeREZDialog(){

}

void ChangeREZDialog::PressedCancel( wxCommandEvent& event ) {
	//default event: exit with wxID_CANCEL
	event.Skip();
}

void ChangeREZDialog::PressedBrowse( wxCommandEvent& event )
{
	wxFileDialog* pFileDialog = NULL;
	wxString strDefaultPath = GETAPP->GetExePath();
	if(GetCastedParent()->GetREZPath() != "")
		strDefaultPath = GetCastedParent()->GetREZPath();

	bool bSuccess = false;

	if(m_mode == DMODE_BACKUP)
	{
		pFileDialog = new wxFileDialog(this, "Choose a REZ file", strDefaultPath, "", "REZ files (*.REZ)|*.REZ", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		if(pFileDialog->ShowModal() != wxID_CANCEL)
			bSuccess = true;
	} else if(m_mode == DMODE_OUTPUT)
	{
		pFileDialog = new wxFileDialog(this, "Choose an output REZ file", strDefaultPath, "", "REZ files (*.REZ)|*.REZ", wxFD_SAVE);
		if(pFileDialog->ShowModal() != wxID_CANCEL)
			bSuccess = true;
	} else
		wxMessageBox("Change REZ dialog has no mode set up!");

	if(pFileDialog != NULL && bSuccess)
	{
		textctrl_path->SetValue(pFileDialog->GetPath());
	}

	delete pFileDialog;
}

void ChangeREZDialog::PressedOK( wxCommandEvent& event )
{
	wxString strPath = textctrl_path->GetValue();

	if(m_mode == DMODE_BACKUP)
	{
		if(strPath == "")
		{
			DIALOG_ERROR("No REZ file specified!");
			return;
			//wxMessageDialog error(this, "No REZ file specified!", "Error", wxOK|wxICON_ERROR);
			//error.ShowModal();
		}

		if(!wxFileExists(strPath))
		{
			DIALOG_ERROR("File doesn't exist!");
			return;
		}

		/*wxFileInputStream input_stream(strPath);
		if(!input_stream.IsOk())
		{
			wxMessageDialog error(this, wxString::Format("Cannot open file:\n      %s", strPath.c_str()), "Error", wxOK|wxICON_ERROR);
			error.ShowModal();
			return;
		}*/

		wxFile fileSrc;
		fileSrc.Open(strPath);
		if(!fileSrc.IsOpened())
		{
			DIALOG_ERROR(wxString::Format("Cannot open file:\n      %s", strPath.c_str()));
			return;
		}

		//Everything is perfectly fine up to this moment
		if(checkbox_optional->GetValue())
			GetCastedParent()->SetREZPath(strPath);

		//making a backup copy of a REZ file, used for patching.
		bool bNeedBackup = true;
		wxString strBackupPath = GETAPP->GetExePath() + "BACKUP.REZ";
		//wxString strBackupPath = "D:\\Eclipse C++ Juno\\Workspace\\Gruntz REZ Patcher\\Debug\\BACKUP.REZ";
		//wxString strBackupPath = "D:\\Gruntz\\GRUNTZ. REZ";

		if(wxFileExists(strBackupPath))
		{
			label_progress->SetLabel("Checking the back up copy ...");
			GETAPP->Yield(); //for a label to be displayed correctly
			wxString strHashBackup = wxMD5::GetFileMD5(strBackupPath);
			wxString strHashSrc = wxMD5::GetFileMD5(strPath);

			if(strHashBackup.Cmp(strHashSrc) == 0) //equal strings
				bNeedBackup = false;
		}

		if(bNeedBackup)
		{
			wxFile fileBackup;
			fileBackup.Create("BACKUP.REZ", true);

			label_progress->SetLabel("Making a backup copy ...");
			m_gauge1->SetRange(fileSrc.Length());
			m_gauge1->SetValue(0);

			const int nBufferSize = 5*1024*512; //2.5MB
			unsigned char* buffer = new unsigned char[nBufferSize];
			while(!fileSrc.Eof())
			{
				unsigned int nRead = fileSrc.Read(buffer, nBufferSize);
				fileBackup.Write(buffer, nRead);
				m_gauge1->SetValue(fileSrc.Tell());
				GETAPP->Yield();
			}
			delete[] buffer;
		}
	} else if(m_mode == DMODE_OUTPUT)
	{
		if(strPath == "")
		{
			DIALOG_ERROR("No output REZ file specified!");
			return;
			//wxMessageDialog error(this, "No REZ file specified!", "Error", wxOK|wxICON_ERROR);
			//error.ShowModal();
		}

		//Everything is perfectly fine up to this moment
		if(checkbox_optional->GetValue())
			if(wxFileExists(strPath))
			{
				//set it as a backup copy
				bool bNeedBackup = true;
				wxString strBackupPath = GETAPP->GetExePath() + "BACKUP.REZ";

				label_progress->SetLabel("Checking the back up copy ...");
				GETAPP->Yield(); //for a label to be displayed correctly
				wxString strHashBackup = wxMD5::GetFileMD5(strBackupPath);
				wxString strHashSrc = wxMD5::GetFileMD5(strPath);

				if(strHashBackup.Cmp(strHashSrc) == 0) //equal strings
					bNeedBackup = false;

				if(bNeedBackup)
				{
					wxFile fileBackup;
					fileBackup.Create("BACKUP.REZ", true);
					wxFile fileSrc;
					fileSrc.Open(strPath);

					label_progress->SetLabel("Making a backup copy ...");
					m_gauge1->SetRange(fileSrc.Length());
					m_gauge1->SetValue(0);

					const int nBufferSize = 5*1024*512; //2.5MB
					unsigned char* buffer = new unsigned char[nBufferSize];
					while(!fileSrc.Eof())
					{
						unsigned int nRead = fileSrc.Read(buffer, nBufferSize);
						fileBackup.Write(buffer, nRead);
						m_gauge1->SetValue(fileSrc.Tell());
						GETAPP->Yield();
					}
					delete[] buffer;
				}
			}

		GetCastedParent()->SetREZPath(strPath);
	} else
		wxMessageBox("Change REZ dialog has no mode set up!");

	EndModal(wxID_OK);
}

MainFrame* ChangeREZDialog::GetCastedParent() const
{
	MainFrame* p = dynamic_cast<MainFrame*>(GetParent());
	if(p == NULL)
		wxMessageBox("This dialog has no valid parent window!");
	return p;
}




//=======================================================================================================



void CPatch::m_constructor_debug()
{
	//if(GetPath() == "D:\\Eclipse C++ Juno\\Workspace\\Gruntz REZ Patcher\\Debug\\png\\16\\calendar.png")
	//wxMessageBox(wxString::Format("CONSTRUCTING CPATCH! Address: %x\nText: %s", this, GetPath().c_str()));
}

CPatch::CPatch(wxString str, bool bUsed): m_strPath(str), m_bIsUsed(bUsed), m_nFiles(0)
{
	m_constructor_debug();
	//na razie proste sprawdzenie
	Refresh();
}

// CPatch destructor, 4fun
CPatch::~CPatch()
{
	//if(GetPath() == "D:\\Eclipse C++ Juno\\Workspace\\Gruntz REZ Patcher\\Debug\\png\\16\\calendar.png")
	//wxMessageBox(wxString::Format("DELETING CPATCH! Address: %x\nText: %s", this, GetPath().c_str()));
}

void CPatch::Refresh()
{
	m_nFiles = 0;
	m_strName = m_strAuthor = "";
	m_bIsOk = false;

	//TODO: CPatch::Refresh() obs³uga DIRsów

	if(!wxFileExists(m_strPath))
		return;

	wxFileName fn(m_strPath);
	wxString strExt = fn.GetExt().Lower();
	if(strExt != "grp" && strExt != "zip")
		return;

	//próbuje wczytac ZIP'a
	wxLogOff LogOff;
	wxFileInputStream streamBase(m_strPath);
	if(!streamBase.IsOk())
		return;

	wxZipInputStream streamZip(streamBase);
	vector<wxZipEntry*> vEntries;
	wxZipEntry* zentryPatch = NULL; //plik 'patch.txt' dla formatu GRP

	wxZipEntry* pEntry = streamZip.GetNextEntry();
	while(pEntry != NULL)
	{
		if(pEntry->GetName().Lower() == "patch.txt")
		{
			if(zentryPatch != NULL)
			{
				wxMessageBox("Few occurences of patch.txt file!");
				vEntries.push_back(pEntry);
			} else
				zentryPatch = pEntry;
		}

		vEntries.push_back(pEntry);
		pEntry = streamZip.GetNextEntry();
	}

	if(streamZip.GetLastError() == wxSTREAM_READ_ERROR)
		return;

	LogOff.Off();

	for(int i=0; i<vEntries.size(); i++)
	{
		if(!vEntries[i]->IsDir())
			m_nFiles++;
	}

	if(strExt == "zip")
	{
		m_strName = fn.GetFullName();
	} else if(strExt == "grp")
	{
		//czytamy plik 'patch.txt' w samym archiwum
		if(zentryPatch == NULL) //nie ma pliku patch.txt
			m_strName = fn.GetFullName();
		else
		{
			unsigned int nSize = zentryPatch->GetSize();
			unsigned char* buffer = new unsigned char[nSize];

			streamZip.OpenEntry(*zentryPatch);
			streamZip.Read(buffer, nSize);
			wxMemoryInputStream in(buffer, streamZip.LastRead());
			LogOff.On();
			if(in.IsOk())
			{
				wxFileConfig fc(in);
				fc.SetPath("/patch");
				m_strAuthor = fc.Read("author", "");
				m_strName = fc.Read("name", fn.GetFullName());
			} else
			{
				//z niewiadomych powodów nie mo¿na odczytac konfiga z pamiêci
				m_strName = fn.GetFullName();
			}
			LogOff.Off();

			delete[] buffer;
		}
	}

	if(zentryPatch != NULL) //jest dodatkowy plik, który nie liczy sie w statystykach itd.
		m_nFiles--;

	for(int i=0; i<vEntries.size(); i++)
	{
		delete vEntries[i];
	}

	m_bIsOk = true;
}

//===================================================================================================

//TODO: Je¿eli format GRP, nie zapisywac pliku 'patch.txt' je¿eli jest w nowym REZie!

PatchingDialog::PatchingDialog(wxWindow* parent, const wxSize& size): PatchingDialogTemplate(parent, wxID_ANY, "Patching", wxDefaultPosition, size)
{
	button_ok->Disable();
	SetEscapeId(wxID_CANCEL); //inaczej nie dzia³a krzy¿yk zamykaj¹cy okno dialogowe w prawym górnym rogu
}

PatchingDialog::~PatchingDialog()
{
	wxSize clientSize = GetSize();
	CONFIG->SetPath("/gui");
	CONFIG->Write("pwidth", clientSize.GetWidth());
	CONFIG->Write("pheight", clientSize.GetHeight());
}

void PatchingDialog::Finalize()
{
	gauge_total->SetValue(gauge_total->GetRange());
	button_ok->Enable();
	//ShowModal();
	return;
}

void PatchingDialog::Run()
{
	Show(true);
	wxTheApp->Yield();

	label_progress->SetLabel("Reading backup file ...");
	Log("Reading BACKUP.REZ ...");

	wxTheApp->Yield();

	wxLogOff LogNull;
	CREZ Rez("BACKUP.REZ");
	if(!Rez.IsLoaded())
	{
		label_progress->SetLabel("Failed to load BACKUP.REZ!");
		Log("Failed to load BACKUP.REZ!");
		Finalize();
		return;
	}
	LogNull.Off();

	Rez.SetGauge(gauge_total);
	Rez.SetLog(text_log);

	label_progress->SetLabel("Reading patches ...");

	wxTheApp->Yield();

	for(vector<CPatch*>::iterator it = vPatches.begin(); it != vPatches.end(); it++)
	{
		CPatch* pPatch = (*it);

		if(!wxFileExists(pPatch->GetPath()))
		{
			Log(wxString::Format("Cannot find archive: %s", pPatch->GetPath().c_str()));
			continue;
		}

		Log(wxString::Format("Reading patch: %s", pPatch->GetPath().c_str()));

		LogNull.On(); //wredny b³¹d o braku dostêpu do pliku, bla bla bla
		wxFileInputStream streamBase(pPatch->GetPath());
		if(!streamBase.IsOk())
		{
			Log(wxString::Format("Cannot access archive: %s", pPatch->GetPath().c_str()));
			continue;
		}
		LogNull.Off();

		wxZipInputStream streamZip(streamBase);
		vector<wxZipEntry*> vEntries;

		LogNull.On();
		wxZipEntry* pEntry = streamZip.GetNextEntry();
		while(pEntry != NULL)
		{
			vEntries.push_back(pEntry);
			pEntry = streamZip.GetNextEntry();
		}
		LogNull.Off();

		if(streamZip.GetLastError() == wxSTREAM_READ_ERROR)
		{
			Log(wxString::Format("Cannot read archive: %s", pPatch->GetPath().c_str()));
			continue;
		}

		for(int i=0; i<vEntries.size(); i++)
		{
			if(!vEntries[i]->IsDir() && vEntries[i]->GetName().Lower() != "patch.txt")
			{
				unsigned int nSize = vEntries[i]->GetSize();
				unsigned char* buffer = new unsigned char[nSize];
				streamZip.OpenEntry(*(vEntries[i]));
				if(!streamZip.CanRead())
				{
					Log(wxString::Format("Cannot read entry \"%s\" in archive: %s", vEntries[i]->GetName().c_str(), pPatch->GetPath().c_str()));
					delete[] buffer;
					continue;
				}

				streamZip.Read(buffer, nSize);
				Rez.UpdateFile(vEntries[i]->GetName(), buffer, nSize);
				//buffer pointer is now owned by CREZ and it will be deleted later on automatically
			} else
				Rez.UpdateDir(vEntries[i]->GetName());
		}

		for(int i=0; i<vEntries.size(); i++)
		{
			delete vEntries[i];
		}
	}


	MainFrame* pParent = dynamic_cast<MainFrame*>(GetParent());
	if(pParent != NULL)
	{
		label_progress->SetLabel(wxString::Format("Saving to: %s ...", pParent->GetREZPath().c_str()));
		Log(wxString::Format("Saving to: %s ...", pParent->GetREZPath().c_str()));
		wxTheApp->Yield();
		LogNull.On();
		if(!Rez.Save(pParent->GetREZPath()))
		{
			Log(wxString::Format("Failed to update output REZ file: %s.", pParent->GetREZPath().c_str()));
			label_progress->SetLabel("Failed to update output REZ file.");
			Finalize();
			return;
		}
		LogNull.Off();
	}
	else
		Log("This window has undefined parent!");

	label_progress->SetLabel("Finished.");
	Log("Finished.");

	Finalize();
	return;
}

void PatchingDialog::Log(wxString str) {
	text_log->AppendText(wxString::Format("%s %s\n", GetTimeStamp().c_str(), str.c_str()));
}

//==========================================================================================
