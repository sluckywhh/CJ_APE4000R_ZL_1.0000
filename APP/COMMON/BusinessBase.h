/****************************************************************************
文件名           ：BusinessBase.h
功能             ：awe4000r业务流程抽象类
起始日期         ：
作者             ： 
****************************************************************************/

#ifndef BUSINESS_BASE_H
#define BUSINESS_BASE_H

#include "YWXMLGY.h"
#include "YWXmlBase.h"
#include "VersionConfig.h"
#include "DataClassDesign.h"

//业务流程调用函数接口方式
#ifndef BUSINESS_JSK_MODE
#define BUSINESS_JSK_MODE	1		//转换器方式调用金税盘流程接口
#endif
#ifndef BUSINESS_XML_MODE
#define BUSINESS_XML_MODE	2		//直连方式调用统一xml接口
#endif

#ifndef BUSINESS_TYPE_MODE
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
#endif

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
#include "CNetPara.h"
#include "JSKInfoDef.h"
#else
//2.25.税控设备其他信息查询信息类型定义
#define SKSBQTYXXCX_XXLX_WLCB			0
#define SKSBQTYXXCX_XXLX_QLJS			1
#define SKSBQTYXXCX_XXLX_LXXXSC			2
#define SKSBQTYXXCX_XXLX_WLLQFP			3
#define SKSBQTYXXCX_XXLX_WLLQFPJGQR		4
#define SKSBQTYXXCX_XXLX_FPSCJGHQ		5

//税控盘报税盘组合操作类型定义
#define SKPBSP_CZLX_SJCB		1	//数据抄报
#define SKPBSP_CZLX_QLJS		2	//清零解锁
#define SKPBSP_CZLX_FXGPXX		3	//反写购票信息
#define SKPBSP_CZLX_JZSZ		4	//校准税控设备时钟

#define MAX_ERR_MSG_LEN			200
#endif


//数据抄报介质类型定义
#define SJCB_JZLX_NET			1	//网络
#define SJCB_JZLX_JSP			2	//金税盘
#define SJCB_JZLX_BSP			1	//报税盘


#ifndef JSK_FAILURE
#define JSK_FAILURE		-1
#endif
#ifndef XML_FAILURE
#define XML_FAILURE				-1
#endif


class CBusinessBase;
extern CBusinessBase *g_pBusBase;


class CBusinessBase
{
public:

	/*!
	@brief 锁定互斥体	
	@return  
	*/ 
	void MutexLock(void);

	/*!
	@brief 解锁互斥体	
	*/ 
	void MutexUnlock(void);

	static void InitBusiness();

	INT32 ErrParse(INT32 retCode, string &retMsg);

	//税控设备编号查询
	virtual INT32 SKSBBH_Business(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)=0;

	//报税盘编号查询
//	virtual INT32 BSPBH_Business(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr)=0;

	//税控设备信息查询
	virtual INT32 SKPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strCurTime, string &strErr)=0;

	//税控设备其他信息查询
	virtual INT32 SKSBQTYXXCX_Business(CYWXML_GY &ywxml_gy, UINT8 xxlx, string &sksbxx, string &strErr)=0;

	//报税盘信息查询
	virtual INT32 BSPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strErr)=0;

	//监控数据查询
	virtual INT32 JKSJCX_Business(CYWXML_GY &ywxml_gy, CDataInvKind *pInvKind, string &strErr)=0;

	//授权税率查询
	virtual INT32 SQSLCX_Business(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr)=0;

	//购票信息查询
	virtual INT32 GPXXCX_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr)=0;

	//购票信息写盘
	virtual INT32 GPXXXP_Business(CYWXML_GY &ywxml_gy, string gpxxmw, string &strErr)=0;

	//购票信息写盘解锁
	virtual INT32 GPXXXPJS_Business(CYWXML_GY &ywxml_gy, string wslpjsxx, string &strErr)=0;

	//口令变更
	virtual INT32 KLBG_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)=0;

	//发票开具
	virtual INT32 FPKJ_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, string &strErr)=0;
	
	//发票作废
	virtual INT32 FPZF_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, UINT8 zflx, string &strErr)=0;

	//发票查询
	virtual INT32 FPCX_Business(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr)=0;

	//税控设备报税盘组合操作
	virtual INT32 SKPBSP_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, string qtxx,string &strErr)=0;

	//发票段信息查询(报税盘发票查询)
	virtual INT32 BSPFPCX_Business(CYWXML_GY &ywxml_gy, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr)=0;

	//发票分发
	virtual INT32 BSPFPFF_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)=0;

	//发票收回
	virtual INT32 BSPFPSH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)=0;

	//数据抄报
	virtual INT32 SJCB_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr)=0;

	//监控回传
	virtual INT32 JKHC_Business(CYWXML_GY &ywxml_gy, string strFpjkmw, string &strErr)=0;

	//发票统计信息查询
	virtual INT32 TJXXCX_Business(CYWXML_GY &ywxml_gy, INT32 &monthcount, CDataTjxxhz *pTjxxhz, string &strErr)=0;

	//离线信息写盘
	virtual INT32 LXXXXP_Business(CYWXML_GY &ywxml_gy, string lxxxmw, string &strErr)=0;

	//发票实时上传
	virtual INT32 FPSC_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr)=0;

	//发票更新
	virtual INT32 FPGX_Business(CYWXML_GY &ywxml_gy, string scqrbw, string &strErr)=0;

	//发票读入
	virtual INT32 FPDR_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)=0;

	//分机退回
	virtual INT32 FJTH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)=0;

	//变更证书口令
	virtual INT32 BGZSKL_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)=0;


	//3.1发票上传
	virtual INT32 NETFPSC_Business(CYWXML_GY &ywxml_gy, const string &Fpmx, UINT32 Fpzs, string &Slxlh, string &strErr)=0;

	//3.2发票上传结果获取
	virtual INT32 FPSCJGHQ_Business(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw, string &strErr)=0;

	//3.3网络抄报
	virtual INT32 WLCB_Business(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx, string &strErr)=0;

	//3.4清零解锁
	virtual	INT32 QLJS_Business(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw, string &strErr)=0;

	//3.5清零解锁结果确认
	virtual	INT32 QLJSJGQR_Business(CYWXML_GY &ywxml_gy, string Qtxx, string &strErr)=0;
	
	//3.6离线信息上传
	virtual INT32 NETLXXXSC_Business(CYWXML_GY &ywxml_gy, CDataInvKind *invkind, string strQtxx, string &strLzkzxx, string &strErr)=0;

	//3.7网络领取发票
	virtual INT32 WLLQFP_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)=0;

	//3.8网络领取发票结果确认
	virtual INT32 WLLQFPJGQR_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)=0;

	//发票补录
	virtual INT32 FPBL_Business(CYWXML_GY &ywxml_gy, UINT32 SDate, UINT32 EDate, string &strErr)=0;
	

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
	//网络参数维护 -- 转换器
	virtual INT32 NetPara_Business(CYWXML_GY &ywxml_gy, CDataNetPara *pNetPara, string &strErr)=0;
#endif

	//获取离线相关数据
	virtual INT32 OffInvInfo_Business(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr)=0;


public:
	//更新未上传发票信息
	virtual INT32 UpdateUploadInv(CYWXML_GY &ywxml_gy)=0;

	//安全通道连接测试
	virtual INT32 SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr)=0;
	
	//获取上传错误发票信息 
	virtual INT32 GetErrUpInvInfo(CYWXML_GY &ywxml_gy, CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr)=0;
	
};


#endif


