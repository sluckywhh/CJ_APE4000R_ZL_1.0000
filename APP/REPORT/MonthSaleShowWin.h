/*! \file    MonthSaleShowWin.h
   \brief    awe4000r月销售统计显示界面
   \author   Yu Yan
   \version  1.0
   \date     2015-06-15
 */

#ifndef MONTH_SALE_SHOW_WIN_H
#define MONTH_SALE_SHOW_WIN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#endif

#include "IncludeMe.h"
#include "CaWindow.h"
#include "LOGCTRL.h"
#include "pos_debug.h"
#include "g_def.h"
#include "CaLabel.h"
#include "CMainFrame.h"
#include "CaButton.h"

#include "SysMacDef.h"
#include "CGlobalArg.h"
//#include "CTjxxhz.h"
#include "DataClassDesign.h"

/**
 *@class MonthSaleShowWin 
 *@brief 月销售统计显示界面
 */
class CMonthSaleShowWIn : public CaWindow
{
public:
	char title_array[7][OBJ_TITLE_MAX_LEN + 1];	/**< 标签的标题*/

	CaLabel *label[7];							/**< 指向标签的指针 */
	
	CaButton *m_pBtn1, *m_pBtn2;				/**< 指向按钮的指针 */
	        	
	int m_iBtnW;								/**< 两列时，控件的宽度 */  
	int m_iColW;								/**< 两列时，第二列的横坐标 */  

	UINT32 m_pageIndex;							/**< 当前页码*/
	UINT32 m_pageNum;							/**< 总页码数*/
	CDataTjxxhz *m_ptrTjxxhz;						/**< 发票领用信息*/
	UINT32 m_recordIndex;						/**< 记录在表中的序号*/

	UINT32 m_iStartDate;					/**< 查询的起始日期*/
    UINT32 m_iEndDate;					/**< 查询的截止日期*/


private:

	/*!
	@brief 按钮响应的静态函数
	@param[in] obj 控件指针
	@param[in] iEvent 事件编号
	@param[in] pEventData 事件内容
	@param[in] iDataLen 事件内容长度
	*/
	static void S_OnButton1(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);
	
	/*!
	@brief 按钮响应的静态函数
	@param[in] obj 控件指针
	@param[in] iEvent 事件编号
	@param[in] pEventData 事件内容
	@param[in] iDataLen 事件内容长度
	*/
	static void S_OnButton2(CaObject *obj,int iEvent, unsigned char * pEventData, int iDataLen);

public:

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

	/*!
	@brief 刷新窗口显示	
	@return 1: SUCCESS
	*/
	virtual int ReFresh();

	/*!
	@brief 按钮1响应函数	
	@param[in] iEvent 事件编号
	@param[in] pEventData 事件内容
	@param[in] iDataLen 事件内容长度
	*/
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief 按钮2响应函数	
	@param[in] iEvent 事件编号
	@param[in] pEventData 事件内容
	@param[in] iDataLen 事件内容长度
	*/
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief 构造函数	
	*/
	CMonthSaleShowWIn();

	/*!
	@brief 析构函数	
	*/
	virtual ~CMonthSaleShowWIn();
   
	/*!
	@brief 更新显示内容的静态函数	 
	*/
	static void S_OnActive(CaWindow *obj);
    
	/*!
	@brief 更新显示内容的函数	 
	*/
	void DoActive(); 

	
	/*!
	@brief 改变Label所关联的title值	
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ChangeTitle();

	/*!
	@brief 获取月销售统计信息，并修改屏幕显示
	@param[in] pTjxxhz 统计信息查询表的指针
	@param[in] nPageIndex  本次屏幕显示的页码号
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 QueryShow(CDataTjxxhz *pTjxxhz, UINT32 nPageIndex);

		/*!
	@brief 打印月销售统计过程
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 PrnMonthSaleSumProc();

	/*!
	@brief 月销售统计核心过程
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 MonthSaleSumHandle();
  

};

#endif
