/*! \file    MediumDeclareMenu.cpp
   \brief    介质抄报菜单
   \author   zcy
   \version  1.0
   \date     2015-05-06
 */

#ifndef MED_DECL_MENU_H
#define MED_DECL_MENU_H

#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"
#include "CMainFrame.h"


/**
 *@class CMedDeclMenu 
 *@brief 税控主界面
 */
class CMedDeclMenu : public CMultiBtnCommonWin
{
public:
	CMedDeclMenu();
		/*!
	@brief 创建窗体	
	@param iX 左上角横坐标
	@param iY 左上角纵坐标
	@param iW 宽度
	@param iH 高度
	@return 1 ：成功；其它：失败
	*/
	int Create(int iX,int iY,int iW,int iH);
		/*!
	@brief 处理事件	
	@param[in] iEvent 事件编号
	@param[in] pEventData 事件内容
	@param[in] iDataLen 事件内容长度
	@return   1  已处理； 0 无法处理
	*/
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	
private:
	/*!
	@brief 征期抄税
	*/
	//void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief 介质报税
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	/*!
	@brief 清零解锁
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);



};


#endif
