/*! \file   InvSegMenu.cpp
\brief    awe4000r��Ʊ�������������ܵ����˵�
\author   Yu Yan
\version  1.0
\date     2010-12-26
*/

#include "InvSegMenu.h"
#include "InvManageMainMenu.h"

#include "CaMsgBox.h"
#include "CaProgressBar.h"
#include "CMainFrame.h"
#include "CGlobalArg.h"
#include "InvVolFunc.h" 

CInvSegMenu::CInvSegMenu():CMultiBtnCommonWin(3)
{
}

int CInvSegMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,INV_SEG_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1,"A.��Ʊ�ַ�");  
	SetTitle(2,"B.��Ʊ�˻�");
	SetTitle(3,"C.��Ʊ�ջ�");  

	return 1;
}

void CInvSegMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (0 != g_globalArg->m_corpInfo->m_Kpjhm)
	{
		CaMsgBox::ShowMsg("�����������ַܷ���Ʊ");
		return ;
	}
	((CInvManageMenu*)m_pFrame->GetWin(INV_MANAGE_MENU))->m_InvWin_level1 = INV_DISTRIBUTE_L1;
	ChangeWin(GENERAL_INV_INPUT_WIN);

	return ;
}

void CInvSegMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{
// 	if (0 == g_globalArg->m_corpInfo->m_Kpjhm)
// 	{
//  		CaMsgBox::ShowMsg("�Ƿֻ��������˻ط�Ʊ");
// 		return ;
// 	}
	((CInvManageMenu*)m_pFrame->GetWin(INV_MANAGE_MENU))->m_InvWin_level1 = INV_RETREAT_L1;
	ChangeWin(GENERAL_INV_INPUT_WIN);
	return ;
}
void CInvSegMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	string strErr("");
	UINT8 ret=SUCCESS;

	if (0 != g_globalArg->m_corpInfo->m_Kpjhm)
	{
		CaMsgBox::ShowMsg("�������������ջط�Ʊ");
		return ;
	}

    UINT8 uJZlx=2;//��˰�̽���
	
	ret= INV_MediumType(uJZlx);
    if (ret != SUCCESS)
	{
		return ;
	}

	CaMsgBox::ShowMsg("�뱣������˰���豸ͬʱ���ӿ��");

	CaProgressBar proBar("");
	proBar.SetText("��Ʊ�ջ���...");
    proBar.Show();
	
	ret = INV_HostGetInvVol(uJZlx, strErr);

	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
        CaMsgBox::ShowMsg("��Ʊ�ջسɹ�");
	return ;
}



int CInvSegMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	switch(iEvent) 
	{
	case RETURN_MAIN_MENU:
		ChangeWin(INV_MANAGE_MENU);
		return SUCCESS;
		break;
	default: break;
	}
	
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}


