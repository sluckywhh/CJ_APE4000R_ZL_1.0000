#ifndef _PASSWORD_EDIT_WIN_H
#define _PASSWORD_EDIT_WIN_H

#include <string>
#include "CaWindow.h"
#include "CaInput.h"
#include "CaButton.h"
#include "g_def.h"
#include "CMainFrame.h"
using namespace std;

class CPswEditWin : public CaWindow{
public:
	CaInput *m_pInput1;
	CaInput *m_pInput2;
	CaButton *m_pBtn1;
	CaButton *m_pBtn2;
	
	int m_iBtnW;//Button �Ŀ���
	int m_iColW;

public:
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	bool IsCurWin();	
	virtual int ReFresh();
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

	static void S_OnActive(CaWindow *obj);
	void DoActive(); 
	
	CPswEditWin();
	~CPswEditWin();

private:
	static void S_OnInput1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnInput2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

    UINT8 CheckInputValid(string &strErr);
	void ClearPswEditWin();
	void BacktoUpperWin();
	
};


#endif
