/*! \file    FiscalMainMenu.cpp
   \brief    税控功能主菜单
   \author   zl
   \version  1.0
   \date     2008-01-01
 */


#include "FiscalMainMenu.h"
#include "FiscalFun.h"
#include "CaProgressBar.h"
#include "CaMsgBox.h"
#include "InvVolFunc.h"
#include "GeneralInvInputWin.h"
#include "InvManageMainMenu.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "APIBase.h"
#include "YWXmlBase.h"

CFiscalMenu::CFiscalMenu():CMultiBtnCommonWin(10, 2)
{

}


int CFiscalMenu::Create(int iX,int iY,int iW,int iH)
{
	m_pFrame->RegsiterWin(this,FISCAL_MAIN_MENU);    
    
	CMultiBtnCommonWin::Adjustm_iH(1);
	CMultiBtnCommonWin::Create(iX, iY, iW, iH);
	
	SetTitle(1, "A.初 始 化");
	SetTitle(2, "B.权限更新");
	SetTitle(3, "C.介质抄报");
	SetTitle(4, "D.网络抄报");
	SetTitle(5, "E.金税盘口令");
	SetTitle(6, "F.发票上传");
	SetTitle(7, "G.发票补录");
	SetTitle(8, "H.上传日志");
	SetTitle(9, "I.发票补传");
	SetTitle(0, "J.离线数据");

	return 1;
}

//初始化按钮
void CFiscalMenu::OnButton1(int iEvent, unsigned char * pEventData, int iDataLen)
{
	DBG_PRINT(("进入FiscalMainMenu::OnButton1函数"));

	//linzihao edit
	if (g_globalArg->m_initFlag == 1)
	{
		CaMsgBox::ShowMsg("机器已经初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton1函数"));

		return ;
	}
	
	ChangeWin(INIT_EDIT_WIN);

	DBG_PRINT(("退出FiscalMainMenu::OnButton1函数"));
	
	return;
}

//信息更新
void CFiscalMenu::OnButton2(int iEvent, unsigned char * pEventData, int iDataLen)
{	
	string strErr("");

	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton2函数"));
		
		return ;
	}

	CaProgressBar proBar("权限更新中...");
	proBar.Show();

	INT32 ret = g_pAPIBase->LXXXUpdatePro_API(*g_YwXmlArg, strErr);

	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
	}
	else
	{
		ret =FSC_GetInvKindInfo(strErr);
		if (ret != SUCCESS)
		{
			CaMsgBox::ShowMsg(strErr);
			return;
		}

		CaMsgBox::ShowMsg("权限更新成功");
	}
	DBG_PRINT(("退出FiscalMainMenu::OnButton2函数"));
		return;

}

//介质抄报
void CFiscalMenu::OnButton3(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton3函数"));
		
		return ;
	}
	
	ChangeWin(MEDIUM_DECLARE_MENU);

}

//网络抄报
void CFiscalMenu::OnButton4(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton4函数"));
		
		return ;
	}
	
	ChangeWin(NET_DECLARE_MENU);
	
}

//金税盘口令更改
void CFiscalMenu::OnButton5(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton5函数"));
		
		return ;
	}
	
  ChangeWin(CHANGE_DISK_PSW_WIN);
}

//------------------------------------------------------------------------------------
//发票上传
//------------------------------------------------------------------------------------
void CFiscalMenu::OnButton6(int iEvent, unsigned char * pEventData, int iDataLen)
{
	
	if (g_globalArg->m_initFlag == 0)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		return ;
	}
	
	CaProgressBar proBar("发票上传中...");
	proBar.Show();
	
	string strErr("");
	UINT8 ret=SUCCESS;
	
	ret = INV_InvoiceUpload(strErr);
	if (ret != SUCCESS)
	{
		CaMsgBox::ShowMsg(strErr);
		return ;
	}
	CaMsgBox::ShowMsg( "发票开始上传");
	
	return;	
}

//发票补录
void CFiscalMenu::OnButton7(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton7函数"));
		
		return ;
	}
	
	ChangeWin(FPBL_WIN);
}


//获取出错的发票信息
void CFiscalMenu::OnButton8(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton8函数"));
		
		return ;
	}
	
	ChangeWin(ERR_UP_INV_WIN);
}

//发票补传
void CFiscalMenu::OnButton9(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton9函数"));
		
		return ;
	}

	((CGInvInputWin *)m_pFrame->GetWin(GENERAL_INV_INPUT_WIN))->m_nFlag = 1;

	((CInvManageMenu*)m_pFrame->GetWin(INV_MANAGE_MENU))->m_InvWin_level1 = INV_DETAIL_NO_L1;
	ChangeWin(GENERAL_INV_INPUT_WIN);
}

//离线数据
void CFiscalMenu::OnButton10(int iEvent, unsigned char * pEventData, int iDataLen)
{
	if (g_globalArg->m_initFlag != 1)
	{
		CaMsgBox::ShowMsg("机器未初始化");
		DBG_PRINT(("退出FiscalMainMenu::OnButton5函数"));
		
		return ;
	}

	ChangeWin(HQLXSJ_WIN);
}

int CFiscalMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	if (RETURN_MAIN_MENU == iEvent)
	{
		ChangeWin(SYSTEM_MAIN_MENU);
		return SUCCESS;
	}
	 
	return CMultiBtnCommonWin::ProcEvent(iEvent,pEventData,iDataLen);
}

