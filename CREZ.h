/*
 * CREZ.h
 *
 *  Created on: 19-02-2012
 *      Author: tomek
 */

#include <vector>

#include <wx/msgdlg.h>	//wxMessageBox(...)
//#include <wx/gauge.h>	//Gauge that represents a progress
#include <wx/file.h>	//m_File

#ifndef CREZ_H_
#define CREZ_H_

typedef unsigned char byte;

class CREZFile {
public:
	//file offset, file length, file date/time, extension, name
	CREZFile(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _ext, wxString _name);
	CREZFile(wxString _name, wxString _ext, unsigned char* data, unsigned int nSize);

	~CREZFile() {
		if(pData != NULL)
		{
			delete[] pData;
		}
	}

	void List(int nTab) {
		for(int i=0; i<nTab; i++)
			printf("  ");
		printf("File: \"%s\" Offset: %d Length: %d\n", GetFullName().c_str(), GetOffset(), GetLength());
	}
	//======================

	inline unsigned int GetOffset() const {
		return nOffset;
	}
	inline unsigned int GetLength() const {
		return nLength;
	}
	inline wxString GetExtension() const {
		return strExtension;
	}
	inline wxString GetName() const {
		return strName;
	}
	inline wxString GetFullName() const {
		wxString strRes = GetName();
		if(GetExtension() != "")
			 strRes += "." + GetExtension();
		return strRes;
	}
	inline unsigned int GetDateTime() const {
		return nDateTime;
	}
	inline unsigned char* GetData() const {
		return pData;
	}

	inline void SetOffset(unsigned int _offset) {
		nOffset = _offset;
	}
	inline void SetLength(unsigned int _length) {
		nLength = _length;
	}
	inline void SetExtension(wxString _ext) {
		strExtension = _ext;
	}
	inline void SetName(wxString _name) {
		strName = _name;
	}
	inline void SetDateTime(unsigned int _datetime) {
		nDateTime = _datetime;
	}
	inline void SetData(unsigned char* _pData) {
		pData = _pData;
	}

	inline bool IsPatch() const {
		return m_bIsPatch;
	}

private:
	unsigned int nOffset; //its offset in REZ file in bytes
	unsigned int nLength; //the length of a file in bytes
	unsigned int nDateTime; //unix stamp
	unsigned char* pData; // the actual data of the file!
	wxString strExtension;
	wxString strName;

	bool m_bIsPatch;
};

class CREZDir {
public:
	//dir offset, dir length, dir date/time, name
	CREZDir(unsigned int _offset, unsigned int _length, unsigned int _datetime, wxString _name);
	CREZDir(wxString _name);
	~CREZDir();

	void List(int nTab) {
		for(int i=0; i<nTab; i++)
			printf("  ");
		printf("Directory: \"%s\" Offset: %d Length: %d\n", GetName().c_str(), GetOffset(), GetLength());
		for(int i=0; i<vFiles.size(); i++)
			vFiles[i]->List(nTab+1);
		for(int i=0; i<vDirectories.size(); i++)
			vDirectories[i]->List(nTab+1);
	}

	unsigned int GetNodesCount() const {
		unsigned int nResult = GetFilesCount();
		nResult += GetDirectoriesCount();
		for(int i=0; i<GetDirectoriesCount(); i++)
			nResult += GetDirectory(i)->GetNodesCount();
		return nResult;
	}

	inline int GetFilesCount() const {
		return vFiles.size();
	}
	inline CREZFile* GetFile(int i) const {
		if(i >= vFiles.size())
			return NULL;
		return vFiles[i];
	}
	inline void DeleteFile(int i) {
		if(i >= vFiles.size())
			return;
		delete vFiles[i];
		vFiles.erase(vFiles.begin()+i);
	}

	inline int GetDirectoriesCount() const {
		return vDirectories.size();
	}
	inline CREZDir* GetDirectory(int i) const {
		if(i >= vDirectories.size())
			return NULL;
		return vDirectories[i];
	}
	inline void DeleteDirectory(int i) {
		if(i >= vDirectories.size())
			return;
		delete vDirectories[i];
		vDirectories.erase(vDirectories.begin()+i);
	}

	/* bool AddFile(...) returns pointer of a file object if successfull
	 * uint 	nFileOffset
	 * uint 	nFileLength
	 * uint 	nDateTime
	 * char*	sFileExt ( reversed! ) ( 4 bytes )
	 * string	strFileName */
	CREZFile* AddFile(unsigned int, unsigned int, unsigned int, wxString, wxString);
	CREZFile* AddFile(wxString, wxString, unsigned char*, unsigned int);

	/* bool AddDir(...) returns pointer of a directory object if successfull
	 * uint 	nDirOffset
	 * uint 	nDirLength
	 * uint 	nDateTime
	 * string	strDirName */
	CREZDir* AddDir(unsigned int, unsigned int, unsigned int, wxString);
	CREZDir* AddDir(wxString);

	inline unsigned int GetOffset() const {
		return nOffset;
	}
	inline unsigned int GetLength() const {
		return nLength;
	}
	inline wxString GetName() const {
		return strName;
	}
	inline unsigned int GetDateTime() const {
		return nDateTime;
	}

	inline void SetOffset(unsigned int _offset) {
		nOffset = _offset;
	}
	inline void SetLength(unsigned int _length) {
		nLength = _length;
	}
	inline void SetName(wxString _name) {
		strName = _name;
	}
	inline void SetDateTime(unsigned int _datetime) {
		nDateTime = _datetime;
	}
private:
	unsigned int nOffset; //its offset in REZ file in bytes
	unsigned int nLength; //the length of a directory in bytes
	unsigned int nDateTime; //unix stamp
	wxString strName;

	std::vector<CREZDir*> vDirectories;
	std::vector<CREZFile*> vFiles;
};

//===================================================================================

class CREZBase {
public:
	CREZBase(wxString);
	virtual ~CREZBase() {
		if(pRootDirectory != NULL)
			delete pRootDirectory;
	}

	void UpdateFile(wxString strPath, unsigned char* data, unsigned int nSize);
	void UpdateDir(wxString strPath);

	bool Save(wxString strOutput);

	CREZDir* pRootDirectory;

	inline bool IsLoaded() const {
		return (pRootDirectory != NULL);
	}

	/*
	bool LoadREZ(std::string, bool bLoadData = true); //³aduje ca³y plik *.REZ do pamiêci. Je¿eli bLoadData, nie ³aduje plików z REZ'a do pamiêci
	bool SaveREZ(std::string); //zapisuje strukturê danych w pamiêci w postaci pliku *.REZ na dysku
	bool LoadDirectory(std::string, bool bLoadData = true); //³aduje do pamiêci ca³¹ scie¿kê z dysku ze wszystkimi folderami ( nawet pustymi ) i plikami
	bool SaveDirectory(std::string); //zapisuje strukturê danych w pamiêci na dysku ( eksport )
*/

protected:
	/*void SaveDirectory_ListFolder(CREZDir* pDir, wxString strDest);
	void LoadDirectory_ListFolder(wxString strDir, wxString strFolderName, CREZDir* pParentDir);*/
	void SaveREZ_WriteDirectory(CREZDir* pDir, wxFile*);
	void LoadREZ_LoadDirectory(CREZDir* pDir);

	// =============== progress bar data ===============

	unsigned int m_nNodesRead;
	wxFile m_File; //source file (BACKUP.REZ)

	virtual void ProgressInitialize(){}	//called in Save(...) method, before
	virtual void ProgressUpdate(){} 	//called from time to time to update the progress bar or whatever

	struct REZErr
	{
		wxString strFile;
		unsigned int nID;
		unsigned int nOffset;
	};

	enum REZ_ERROR {
		RER_NO_ERROR = 0,
		RER_LONG_EXT,		//the extension of the file is longer than 4 characters
		RER_DEC_WRONG_ID,	//
	};

	virtual void Log(REZ_ERROR, REZErr*) {}

};


#endif /* CREZ_H_ */
