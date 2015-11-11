/*
 * CREZ.cpp
 *
 *  Created on: 19-02-2012
 *      Author: tomek
 */

/*
 * header (127 bytes)
 * unsigned char sHeader[127] =
 * {13, 10, 82, 101, 122, 77, 103, 114, 32, 86, 101, 114,
	115, 105, 111, 110, 32, 49, 32, 67, 111, 112, 121, 114,
	105, 103, 104, 116, 32, 40, 67, 41, 32, 49, 57, 57, 53,
	32, 77, 79, 78, 79, 76, 73, 84, 72, 32, 73, 78, 67, 46,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 13, 10, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 13, 10, 26};
 * */

#include <wx/filename.h> 	//wy³uskanie nazw folderów, rozszerzeñ itd.
#include <wx/app.h>			//metoda Yield() aplikacji ¿eby zaktualizowac Gauge

#include "CREZ.h"

using namespace std;

#define _4BYTES2INT(bf,si) ((int)bf[si]+(int)bf[si+1]*256+(int)bf[si+2]*256*256+(int)bf[si+3]*256*256*256)

CREZFile::CREZFile(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _ext, wxString _name)
{
	//file offset, file length, file date/time, extension, name
	nOffset = _offset;
	nLength = _length;
	nDateTime = _datetime;
	pData = NULL;
	strExtension = _ext;
	strName = _name;

	m_bIsPatch = false;
}

CREZFile::CREZFile(wxString _name, wxString _ext, unsigned char* data, unsigned int nSize)
{
	//_name - this is FULL name with the extension

	nOffset = 0;
	nLength = nSize;
	nDateTime = 0;
	pData = data;
	strExtension = _ext;
	strName = _name;

	m_bIsPatch = true;
}

CREZDir::CREZDir(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _name)
{
	nOffset = _offset;
	nLength = _length;
	nDateTime = _datetime;
	strName = _name;
}

CREZDir::CREZDir(wxString _name)
{
	nOffset = 0;
	nLength = 0;
	nDateTime = 0;
	strName = _name;
}

CREZDir::~CREZDir()
{
	for(int i=0; i<vFiles.size(); i++)
		delete vFiles[i];
	for(int i=0; i<vDirectories.size(); i++)
		delete vDirectories[i];
}

/* bool AddFile(...) returns pointer of a file object if successfull
 * uint 	nFileOffset
 * uint 	nFileLength
 * uint 	nDateTime
 * string	strFileExt
 * string	strFileName */
CREZFile* CREZDir::AddFile(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _ext, wxString _name)
{
	//sprawdzic czy nie istnieje plik z taka nazwa
	for(int i=0; i<vFiles.size(); i++)
		if(vFiles[i]->GetName() == _name && vFiles[i]->GetExtension()==_ext)
		{
			//printf("Trying to add file to CREZDir instance. It already has a file with the same name: %s*%s\n\n", vFiles[i]->GetName().c_str(), vFiles[i]->GetExtension().c_str());
			return NULL;
		}

	CREZFile* pFile = new CREZFile(_offset, _length, _datetime, _ext, _name);
	vFiles.push_back(pFile);
	return pFile;
}

CREZFile* CREZDir::AddFile(wxString strName, wxString strExt, unsigned char* data, unsigned int nSize) {
	//sprawdzic czy nie istnieje plik z taka nazwa
	for(int i=0; i<vFiles.size(); i++)
		if(vFiles[i]->GetName() == strName && vFiles[i]->GetExtension()==strExt)
		{
			return NULL;
		}

	CREZFile* pFile = new CREZFile(strName, strExt, data, nSize);
	vFiles.push_back(pFile);
	return pFile;
}

/* bool AddDir(...) returns pointer of a directory object if successfull
 * uint 	nDirOffset
 * uint 	nDirLength
 * uint 	nDateTime
 * string	strDirName */
CREZDir* CREZDir::AddDir(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _name)
{
	//sprawdzic czy nie istnieje plik z taka nazwa
	for(vector<CREZDir*>::iterator it = vDirectories.begin(); it != vDirectories.end(); it++)
		if((*it)->GetName() == _name)
		{
			//printf("Trying to add directory to CREZDir instance. It already has a directory with the same name: %s\n\n", (*it)->GetName().c_str());
			return NULL;
		}

	CREZDir* pDir = new CREZDir(_offset, _length, _datetime, _name);
	vDirectories.push_back(pDir);
	return pDir;
}

CREZDir* CREZDir::AddDir(wxString _name)
{
	return AddDir(0, 0, 0, _name);
}

//==============================================================================
/*
void CREZ::LoadDirectory_ListFolder(string strDir, string strFolderName, CREZDir* pParentDir)
{
	//np. strFolderName = "My Rez"
	//np. albo ci¹g pusty "" gdy mamy do czynienia z Root Folder

	//np. strDir = "D:\\Gruntz\\"
	//pDir - folder, który teraz analizujemy

	//najpierw przeszukujemy foldery w tym folderze
	vector<string> vFolders;
	string strFullFolder = strDir;
	if(strFolderName != "")
		strFullFolder += (strFolderName + '\\');
	strFullFolder += "*";
	//np. strFullFolder = "D:\\Gruntz\\My Rez\\*"
	char* szItFolderName = GETHGE->Resource_EnumFolders(strFullFolder.c_str());
	while(szItFolderName != 0)
	{
		vFolders.push_back(szItFolderName);
		szItFolderName = GETHGE->Resource_EnumFolders(0);
	}

	for(vector<string>::iterator it = vFolders.begin(); it != vFolders.end(); it++)
	{
		string strTempDir = (strDir + strFolderName + '\\');
		CREZDir* pNewDir = pParentDir->AddDir(0, 0, 0, (*it));
		LoadDirectory_ListFolder(strTempDir, (*it), pNewDir);
	}

	//==================================================
	//Teraz zajmujemy siê plikami w danym folderze
	char* szItFileName = GETHGE->Resource_EnumFiles(strFullFolder.c_str());

	while(szItFileName != 0)
	{

		//* W tym miejsu mamy blok, któremu podlega ka¿dy plik
		//* Przyk³ad:
		//*         strDir = "D:\\Gruntz\\GRUNTZ REZ\\GRUNTZ\\ANIZ\\";
		//*         szFileName = "MYANIM.ANI";



		//najpierw znalezienie rozszerzenia pliku ( je¿eli jest ), a potem pozosta³ej jego czêsci
		//np. strExt = "txt";
		//np. strNoExt = "readme";
		string strFileName = szItFileName;
		string strExt;
		string strNoExt;
		int n = (strFileName.size() - 1);
		while(n >= 0 && strFileName[n] != '.')
		{
			strExt = strFileName[n] + strExt;
			n--;
		}

		if(n < 0) //plik nie ma rozszerzenia
		{
			strNoExt = strExt;
			strExt = "";
		} else
		{
			n--;
			while(n >= 0)
			{
				strNoExt = strFileName[n] + strNoExt;
				n--;
			}
		}

		//skopiowanie zawartosci pliku do pamiêci
		unsigned int nFileSize;
		unsigned char* pData = NULL;

		string strFullFile = strFullFolder.substr(0, strFullFolder.size()-1);
		strFullFile += strFileName;
		ifstream File(strFullFile.c_str(), ifstream::in|ifstream::binary);
		File.seekg (0, ios::end);
		nFileSize = File.tellg();
		if(bDataLoaded)
		{
			File.seekg (0, ios::beg);
			pData = new unsigned char[nFileSize];
			File.read((char*)pData, nFileSize);
		}
		File.close();

		CREZFile* pNewFile = pParentDir->AddFile(0, nFileSize, 0, strExt, strNoExt);
		pNewFile->SetData(pData);

		szItFileName = GETHGE->Resource_EnumFiles(0);
	}
}


bool CREZ::LoadDirectory(string strDir, bool bLoadData)
{
	string strFullFolder = strDir + "*";
	if(GETHGE->Resource_EnumFolders(strFullFolder.c_str()) == 0 &&
			GETHGE->Resource_EnumFiles(strFullFolder.c_str()) == 0)
	{
		printf("Either a specified directory is empty, or it doesn't exist:\n  %s\n\n", strDir.c_str());
		return false;
	}

	//Free the memory if the REZ file is already loaded up
	Free();

	bDataLoaded = bLoadData;

	pRootDirectory = new CREZDir(0, 0, 0, "ROOT");
	LoadDirectory_ListFolder(strDir, "", pRootDirectory);
	nNodesCount = pRootDirectory->GetNodesCount();

	return true;
}
*/
void CREZBase::SaveREZ_WriteDirectory(CREZDir* pDir, wxFile* pFile)
{
	//najpierw np. PLIKI
	//zapisujemy je w REZie po czym spisujemy ich offset
	for(int i = 0; i < pDir->GetFilesCount(); i++)
	{
		CREZFile* pItFile = pDir->GetFile(i);
		if(pItFile->IsPatch())
		{
			pItFile->SetOffset(pFile->Tell());
			pFile->Write(pItFile->GetData(), pItFile->GetLength());
		}
		else
		{
			//je¿eli danych nie ma w pamiêci, odczytuje z BACKUP.REZ
			m_File.Seek(pItFile->GetOffset());
			unsigned char* buffer = new unsigned char[pItFile->GetLength()];
			m_File.Read(buffer, pItFile->GetLength());

			pItFile->SetOffset(pFile->Tell());
			pFile->Write(buffer, pItFile->GetLength());
			delete[] buffer;
		}

		m_nNodesRead++;
	}

	ProgressUpdate();

	//teraz zapisujemy FOLDERY
	for(int i = 0; i < pDir->GetDirectoriesCount(); i++)
	{
		CREZDir* pItDir = pDir->GetDirectory(i);
		SaveREZ_WriteDirectory(pItDir, pFile);
		m_nNodesRead++;
	}

	ProgressUpdate();

	//============================================
	//teraz czêsæ w³asciwa - index wszystkich elementów
	unsigned int nOffsetMark = pFile->Tell();
	pDir->SetOffset(nOffsetMark);

	//najpierw indeks plików
	for(int i = 0; i < pDir->GetFilesCount(); i++)
	{
		CREZFile* pItFile = pDir->GetFile(i);

	    //if (type == 0){
        //
	    //    uint32 {4}   - File Offset
	    //    uint32 {4}   - File Length
	    //    uint32 {4}   - Date/Time
	    //    uint32 {4}   - File ID? (je¿eli nazwa pliku to liczba, FileID to bêdzie ta liczba ( bez zer na pocz¹tku ). W przeciwnym razie 10000000, 10000001 itd., alfabetycznie, ale ju¿ bez tych plików z liczb¹ zamiast nazwy)
	    //    char {4}     - Type/Extension (reversed) (np. mamy PID: "DIP*" gdzie * to NULL)
	    //    uint32 {4}   - null
	    //    char {X}     - filename (terminated by 2 nulls)
	    //    }

		unsigned int nBuffer = 0;
		pFile->Write((&nBuffer), 4);

		nBuffer = pItFile->GetOffset();
		pFile->Write((&nBuffer), 4);

		nBuffer = pItFile->GetLength();
		pFile->Write((&nBuffer), 4);

		nBuffer = pItFile->GetDateTime();
		pFile->Write((&nBuffer), 4);

		nBuffer = 1145661766; // napis "FiID" - File ID
		pFile->Write((&nBuffer), 4);

		//Rozszerzenie:
		unsigned char ExtData[4] = {0, 0, 0, 0};
		wxString strExt = pItFile->GetExtension();
		for(int i = 0; i < 4; i++)
		{
			if(i >= strExt.size())
				break;
			ExtData[i] = strExt[strExt.size()-1-i];
		}

		if(pItFile->GetExtension().length() > 4)
		{
			REZErr s;
			s.strFile = pItFile->GetFullName();
			Log(RER_LONG_EXT, &s);
		}
		pFile->Write(ExtData, 4);

		nBuffer = 0;
		pFile->Write((&nBuffer), 4);

		wxString strFileName = pItFile->GetName();
		pFile->Write(strFileName.c_str(), strFileName.size());
		pFile->Write((&nBuffer), 2); //dwa nulle na koñcu
	}


	//... i foldery
	for(int i = 0; i < pDir->GetDirectoriesCount(); i++)
	{
		CREZDir* pItDir = pDir->GetDirectory(i);

		//uint32 {4}   - Type (0=file, 1=directory)
		//if (type == 1){
        //
	    //uint32 {4}   - Directory Offset
	    //uint32 {4}   - Directory Length
	    //uint32 {4}   - Date/Time
	    //char {X}     - filename (terminated by 1 null)
	    //}

		unsigned int nBuffer = 1;
		pFile->Write((&nBuffer), 4);

		nBuffer = pItDir->GetOffset();
		pFile->Write((&nBuffer), 4);

		nBuffer = pItDir->GetLength();
		pFile->Write((&nBuffer), 4);

		nBuffer = pItDir->GetDateTime();
		pFile->Write((&nBuffer), 4);

		wxString strDirName = pItDir->GetName();
		pFile->Write(strDirName.c_str(), strDirName.size());

		nBuffer = 0;
		pFile->Write((&nBuffer), 1);//jeden null na koñcu
	}

	unsigned int nLength = (pFile->Tell() - nOffsetMark);
	pDir->SetLength(nLength);
}
/*
bool CREZ::SaveREZ(string strDestination)
{
	if(!IsLoaded())
	{
		printf("Trying to save REZ file. There's no data structure loaded up in the memory!\n\n");
		return false;
	}

	if(!bDataLoaded)
	{
		printf("Error! Trying to save REZ file that is in view-only mode! No actual data is loaded.\n\n");
		return false;
	}

	ofstream File(strDestination.c_str(), ofstream::out|ofstream::binary|ofstream::trunc);
	if(!File.good())
	{
		printf("Error when trying to open REZ file for writing:\n  %s\n\n", strDestination.c_str());
		File.close();
		return false;
	}


	//char {127}   - Description/Header
	//uint32 {4}(b127)   - Version (1)
	//uint32 {4}(b131)   - dirOffset
	//uint32 {4}(b135)   - dirSize
	//uint32 {4}(b139)   - Unknown (1C FD 12 00(hex) - 1244444(dec))
	//uint32 {4}(b143)   - Offset to Last Dir (?? What last dir??)
	//uint32 {4}(b147)   - Unknown (GRUNTZ - 3E 3B 91 36/915487550; CLAW - 51 68 CA 33/868902993)
	//uint32 {4}   - null
	//uint32 {4}(b155)   - Unknown (GR-15 00 00 00/21; CL-13 00 00 00/19)
	//uint32 {4}(b159)   - Unknown (GR-19 00 00 00/25; CL-18 00 00 00/24)
	//uint32 {4}   - null
	//uint32 {4}(b167)   - Unknown (01 20 00 00/8193)
	//byte {13}    - null


	unsigned char sHeader[127] = {
	13, 10, 82, 101, 122, 77, 103, 114, 32, 86, 101, 114, 115, 105, 111, 110,
	32, 49, 32, 67, 111, 112, 121, 114, 105, 103, 104, 116, 32, 40, 67, 41,
	32, 49, 57, 57, 53, 32, 77, 79, 78, 79, 76, 73, 84, 72, 32, 73,
	78, 67, 46, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 13, 10,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 13, 10, 26 };
	File.write((char*)sHeader, 127);

	unsigned int nBuffer = 1; //wersja
	File.write((char*)(&nBuffer), 4);

	nBuffer = 4294967295; //FF FF FF FF, trzeba czyms zape³niæ dirOffset i dirSize, ¿eby póŸniej do niego wróciæ
	File.write((char*)(&nBuffer), 4);
	File.write((char*)(&nBuffer), 4);

	nBuffer = 1244444;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 4294967295; //Last Dir. Jest to w ogóle potrzebne? FF FF FF FF
	File.write((char*)(&nBuffer), 4);

	nBuffer = 915487550;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 0;
	File.write((char*)(&nBuffer), 4);

	//uint32 {4}(b155)   - Unknown (GR-15 00 00 00/21; CL-13 00 00 00/19)
	//uint32 {4}(b159)   - Unknown (GR-19 00 00 00/25; CL-18 00 00 00/24)
	//uint32 {4}   - null
	//uint32 {4}(b167)   - Unknown (01 20 00 00/8193)
	//byte {13}    - null

	nBuffer = 21;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 25;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 0;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 8193;
	File.write((char*)(&nBuffer), 4);

	nBuffer = 0;
	for(int i=1; i<=3; i++)
		File.write((char*)(&nBuffer), 4);
	File.write((char*)(&nBuffer), 1);

	//=====================================================
	//TERAZ DANE!

	ProgressPrintHeader();
	SaveREZ_WriteDirectory(pRootDirectory, &File);
	ProgressClear();
	printf("\n\n");
	//=====================================================
	//Wracamy i spisujemy pierwszy folder

	File.seekp(131);

	nBuffer = pRootDirectory->GetOffset();
	File.write((char*)(&nBuffer), 4);

	nBuffer = pRootDirectory->GetLength();
	File.write((char*)(&nBuffer), 4);

	File.close();
	return true;
}

bool CREZ::LoadREZ(string strSource, bool bLoadData)
{
	ifstream File(strSource.c_str(), ifstream::in|ifstream::binary);
	if(!File.good())
	{
		printf("Error when trying to read REZ file:\n  %s\n\n", strSource.c_str());
		File.close();
		return false;
	}

	Free();
	bDataLoaded = bLoadData;

	unsigned int nOffset, nLength;
	unsigned char buffer[8];
	File.seekg(131);
	File.read((char*)buffer, 8);
	nOffset = _4BYTES2INT(buffer, 0);
	nLength = _4BYTES2INT(buffer, 4);

	pRootDirectory = new CREZDir(nOffset, nLength, 0, "ROOT");
	LoadREZ_LoadDirectory(pRootDirectory, &File);

	nNodesCount = pRootDirectory->GetNodesCount();

	File.close();
	return true;
}*/

void CREZBase::LoadREZ_LoadDirectory(CREZDir* pDir)
{
	unsigned int nOffset = pDir->GetOffset();
	unsigned int nLength = pDir->GetLength();
	m_File.Seek(nOffset);

	unsigned char buffer[64];

	while(m_File.Tell() < nOffset + nLength)
	{
		m_File.Read(buffer, 4);
		unsigned int nType = _4BYTES2INT(buffer, 0);

	    /*if (type == 0){

	        uint32 {4}   - File Offset
	        uint32 {4}   - File Length
	        uint32 {4}   - Date/Time
	        uint32 {4}   - File ID? (je¿eli nazwa pliku to liczba, FileID to bêdzie ta liczba ( bez zer na pocz¹tku ). W przeciwnym razie 10000000, 10000001 itd., alfabetycznie, ale ju¿ bez tych plików z liczb¹ zamiast nazwy)
	        char {4}     - Type/Extension (reversed) (np. mamy PID: "DIP*" gdzie * to NULL)
	        uint32 {4}   - null
	        char {X}     - filename (terminated by 2 nulls)
	        }*/

		if(nType == 0)
		{
			//FILE
			m_File.Read(buffer, 24); //6 fields
			unsigned int nFileOffset = 		_4BYTES2INT(buffer, 0);
			unsigned int nFileLength = 		_4BYTES2INT(buffer, 4);
			unsigned int nFileDateTime = 	_4BYTES2INT(buffer, 8);
			unsigned int nFileID = 			_4BYTES2INT(buffer, 12);
			wxString strExt;
			for(int i=19; i>15; i--) //the extension is in bytes 16, 17, 18, 19
				if(buffer[i] != 0)
					strExt += buffer[i];

			//filename with 2 nulls
			wxString strFileName;
			unsigned char cA = 255;
			unsigned char cB = 255;
			for(;;)
			{
				if(cA == 0 && cB == 0)
					break;

				cA = cB;
				m_File.Read((&cB), 1);
				if(cB != 0)
					strFileName += cB;
			}

			//CREZFile::CREZFile(unsigned int _offset, unsigned int _length, unsigned int _datetime, string _ext, string _name)
			CREZFile* pRFile = pDir->AddFile(nFileOffset, nFileLength, nFileDateTime, strExt, strFileName);
		} else if(nType == 1)
		{
			//DIR

			/*
			uint32 {4}   - Type (0=file, 1=directory)
			if (type == 1){

		    uint32 {4}   - Directory Offset
		    uint32 {4}   - Directory Length
		    uint32 {4}   - Date/Time
		    char {X}     - filename (terminated by 1 null)
		    }
			 */

			m_File.Read(buffer, 12);
			unsigned int nDirOffset = _4BYTES2INT(buffer, 0);
			unsigned int nDirLength = _4BYTES2INT(buffer, 4);
			unsigned int nDirDateTime = _4BYTES2INT(buffer, 8);

			//dir name with 1 null at the end
			wxString strDirName;
			for(;;)
			{
				unsigned char c;
				m_File.Read((&c), 1);

				if(c == 0)
					break;

				strDirName += c;
			}

			pDir->AddDir(nDirOffset, nDirLength, nDirDateTime, strDirName);
		} else
		{
			REZErr s;
			s.nID = nType;
			s.nOffset = (m_File.Tell()-4);
			Log(RER_DEC_WRONG_ID, &s);
			m_File.Seek(nOffset + nLength);
			//throw(wxString::Format("Wrong element ID (expected 0 or 1).\nValue read: %d   Offset: %d\n\n", nType, (m_File.Tell()-4)));
		}
	}

	//recursively call this method for all of the children directories
	for(int i=0; i < pDir->GetDirectoriesCount(); i++)
		LoadREZ_LoadDirectory(pDir->GetDirectory(i));
}

/*bool CREZ::SaveDirectory(std::string strDest)
{
	if(!IsLoaded())
	{
		printf("Trying to save the directory file. There's no data structure loaded up in the memory!\n\n");
		return false;
	}

	if(!bDataLoaded)
	{
		printf("Trying to save directory. The REZ file is not loaded in memory - it's in view-only mode.\n\n");
		return false;
	}

	if(CreateFolder(strDest) != CF_ERR_GOOD)
		return false;

	ProgressPrintHeader();
	SaveDirectory_ListFolder(pRootDirectory, strDest);
	ProgressClear();
	printf("\n\n");

	return true;
}

void CREZ::SaveDirectory_ListFolder(CREZDir* pDir, string strDest)
{
	//let's spit out the files in the directory
	for(int i=0; i<pDir->GetFilesCount(); i++)
	{
		CREZFile* pRFile = pDir->GetFile(i);
		string strFullPath = (strDest + pRFile->GetFullName());
		ofstream File(strFullPath.c_str(), ofstream::out|ofstream::binary);
		if(File.good())
			File.write((char*)(pRFile->GetData()), pRFile->GetLength());
		else
			printf("Problems when writing file: %d %d %d\n  %s\n\n", File.bad(), File.eof(), File.fail(), strFullPath.c_str());
		File.close();

		nNodesRead++;
	}

	ProgressUpdate();

	//now the directories
	//create new directory and go with magic of recursion
	for(int i=0; i<pDir->GetDirectoriesCount(); i++)
	{
		CREZDir* pRDir = pDir->GetDirectory(i);
		string strFullPath = (strDest + pRDir->GetName() + '\\');
		if(CreateFolder(strFullPath) != CF_ERR_GOOD)
		{
			printf("Failed at creating a directory: \n  %s\n\n",  strFullPath.c_str());
			break;
		}
		SaveDirectory_ListFolder(pRDir, strFullPath);

		nNodesRead++;
	}

	ProgressUpdate();
}*/

/*pRootDirectory
unsigned int m_nNodesCount;
unsigned int m_nNodesRead;
wxGauge* m_pGauge;
wxFile* m_pFile; //source file (BACKUP.REZ)*/

CREZBase::CREZBase(wxString strFile): pRootDirectory(NULL), m_nNodesRead(0)
{
	//TODO: zrobic implementacje konstruktora dla pustego REZ'a
	//(czyli tworzenie nowego REZa od pocz¹tku z plikami z patchy tylko)

	m_File.Open(strFile);
	if(!m_File.IsOpened() || !m_File.Access(strFile, wxFile::read))
		return;

	try
	{
		unsigned int nOffset, nLength;
		unsigned char buffer[8];
		m_File.Seek(131);
		m_File.Read(buffer, 8);
		nOffset = _4BYTES2INT(buffer, 0);
		nLength = _4BYTES2INT(buffer, 4);

		pRootDirectory = new CREZDir(nOffset, nLength, 0, "ROOT");
		LoadREZ_LoadDirectory(pRootDirectory);
	}
	catch(wxString& str)
	{
		if(pRootDirectory != NULL)
			delete pRootDirectory;
		wxMessageBox(wxString("Unrecoverable error when reading file: ")+strFile+wxString("\nError: ")+str);
	}
	catch(...)
	{
		wxMessageBox(wxString("Unrecoverable error when reading file: ")+strFile);
	}
}

void CREZBase::UpdateFile(wxString strPath, unsigned char* data, unsigned int nSize)
{
	wxFileName oFileName(strPath);
	wxArrayString aDirs = oFileName.GetDirs();

	CREZDir* pDir = pRootDirectory;

	for(int i=0; i<aDirs.size(); i++)
	{
		wxString strDir = aDirs[i];
		bool bFound = false;

		for(int k=0; k<pDir->GetDirectoriesCount(); k++)
			if(pDir->GetDirectory(k)->GetName() == strDir)
			{
				bFound = true;
				pDir = pDir->GetDirectory(k);
				break;
			}

		if(!bFound)
			pDir = pDir->AddDir(strDir);
	}

	wxString strExt = oFileName.GetExt();

	for(int i=0; i<pDir->GetFilesCount(); i++)
	{
		CREZFile* pFile = pDir->GetFile(i);
		if(pFile->GetName() == oFileName.GetName() &&
				pFile->GetExtension() == strExt)
		{
			pDir->DeleteFile(i);
			break;
		}
	}

	pDir->AddFile(oFileName.GetName(), strExt, data, nSize);
}

void CREZBase::UpdateDir(wxString strPath)
{
	wxFileName oFileName(strPath);
	wxArrayString aDirs = oFileName.GetDirs();

	CREZDir* pDir = pRootDirectory;

	for(int i=0; i<aDirs.size(); i++)
	{
		wxString strDir = aDirs[i];
		bool bFound = false;

		for(int k=0; k<pDir->GetDirectoriesCount(); k++)
			if(pDir->GetDirectory(k)->GetName() == strDir)
			{
				bFound = true;
				pDir = pDir->GetDirectory(k);
				break;
			}

		if(!bFound)
		{
			pDir = pDir->AddDir(strDir);
		}
	}
}

bool CREZBase::Save(wxString strOutput)
{
	if(!IsLoaded())
	{
		return false;
	}

	wxFile fileOutput;
	fileOutput.Create(strOutput, true);

	if(!fileOutput.IsOpened() || !m_File.Access(strOutput, wxFile::write))
	{
		//printf("Error when trying to open REZ file for writing:\n  %s\n\n", strDestination.c_str());
		return false;
	}

	ProgressInitialize();

	//nigdy nie zaszkodzi
	m_nNodesRead = 0;

	//char {127}   - Description/Header
	//uint32 {4}(b127)   - Version (1)
	//uint32 {4}(b131)   - dirOffset
	//uint32 {4}(b135)   - dirSize
	//uint32 {4}(b139)   - Unknown (1C FD 12 00(hex) - 1244444(dec))
	//uint32 {4}(b143)   - Offset to Last Dir (?? What last dir??)
	//uint32 {4}(b147)   - Unknown (GRUNTZ - 3E 3B 91 36/915487550; CLAW - 51 68 CA 33/868902993)
	//uint32 {4}   - null
	//uint32 {4}(b155)   - Unknown (GR-15 00 00 00/21; CL-13 00 00 00/19)
	//uint32 {4}(b159)   - Unknown (GR-19 00 00 00/25; CL-18 00 00 00/24)
	//uint32 {4}   - null
	//uint32 {4}(b167)   - Unknown (01 20 00 00/8193)
	//byte {13}    - null


	unsigned char sHeader[127] = {
	13, 10, 82, 101, 122, 77, 103, 114, 32, 86, 101, 114, 115, 105, 111, 110,
	32, 49, 32, 67, 111, 112, 121, 114, 105, 103, 104, 116, 32, 40, 67, 41,
	32, 49, 57, 57, 53, 32, 77, 79, 78, 79, 76, 73, 84, 72, 32, 73,
	78, 67, 46, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 13, 10,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 13, 10, 26 };
	fileOutput.Write(sHeader, 127);

	unsigned int nBuffer = 1; //wersja
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 0xFFFFFFFF; //FF FF FF FF, trzeba czyms zape³niæ dirOffset i dirSize, ¿eby póŸniej do niego wróciæ
	fileOutput.Write((&nBuffer), 4);
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 1244444;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 0xFFFFFFFF; //Last Dir. Jest to w ogóle potrzebne? FF FF FF FF
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 915487550;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 0;
	fileOutput.Write((&nBuffer), 4);

	//uint32 {4}(b155)   - Unknown (GR-15 00 00 00/21; CL-13 00 00 00/19)
	//uint32 {4}(b159)   - Unknown (GR-19 00 00 00/25; CL-18 00 00 00/24)
	//uint32 {4}   - null
	//uint32 {4}(b167)   - Unknown (01 20 00 00/8193)
	//byte {13}    - null

	nBuffer = 21;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 25;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 0;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 8193;
	fileOutput.Write((&nBuffer), 4);

	nBuffer = 0;
	for(int i=1; i<=3; i++)
		fileOutput.Write((&nBuffer), 4);
	fileOutput.Write((&nBuffer), 1);

	//=====================================================
	//TERAZ DANE!

	SaveREZ_WriteDirectory(pRootDirectory, &fileOutput);

	//=====================================================
	//Wracamy i spisujemy pierwszy folder

	fileOutput.Seek(131);

	nBuffer = pRootDirectory->GetOffset();
	fileOutput.Write((&nBuffer), 4);

	nBuffer = pRootDirectory->GetLength();
	fileOutput.Write((&nBuffer), 4);

	return true;
}
