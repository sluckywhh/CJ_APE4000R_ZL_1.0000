/****************************************************************************
文件名           ：ManageBusinessFunc.h
功能             ：awe4000r管理业务功能流程函数。（税控设备信息读写）
起始日期         ：
作者             ： 
****************************************************************************/

#ifndef MANAGE_BUSINESS_FUNC_H
#define MANAGE_BUSINESS_FUNC_H

#include "YWXMLGY.h"
#include "BusinessBase.h"
#include "DataClassDesign.h"

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
#include "CNetPara.h"
#endif

class CManageBusinessFunc
{
public:
	CManageBusinessFunc();
	~CManageBusinessFunc();

public:

	/*!
	@brief 获取税控设备编号		
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetSksbbh(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr);

	/*!
	@brief 获取税控设备信息		
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetTaxpayerInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &dataUserInfo, string &strCurTime, string &strErr);
	
	/*!
	@brief 获取报税盘信息		
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetBSPInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &dataUserInfo, string &strErr);

	/*!
	@brief 获取监控数据		
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetJKSJ(CYWXML_GY &ywxml_gy, CDataInvKind &dataInvKind, string &strErr);

	/*!
	@brief 获取税率信息		
	@param[in] pTax 税率类数组
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetTaxRateInfo(CYWXML_GY &ywxml_gy, CDataTax *pDataTax, UINT8 &taxNum, string &strErr);

	/*!
	@brief 金税盘口令变更
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 SKPKLBG(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr);

	/*!
	@brief 更新离线信息		
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 LXXXUpdatePro(CYWXML_GY &ywxml_gy, string &strErr);

	/*!
	@brief 变更证书口令
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 BGZSKLProc(CYWXML_GY &ywxml_gy, string yzskl, string xzskl, string &strErr);

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
	/*!
	@brief 网络参数维护
	@param[in] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 NetParaManage(CYWXML_GY &ywxml_gy, CDataNetPara *pDataNetPara, string &strErr);
#endif

	/*!
	@brief 获取离线相关数据
	@param[in] 
	@param[out] fpzs   未上传的发票张数
	@param[out] fpsj   未上传发票时间（第一张未上传发票的开票日期YYYYMMDDHHMMSS）
	@param[out] fpljje 未上传发票累计金额（保留两位小数）
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 GetOffLineInvInfo(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr);

	/*!
	@brief 更新未上传发票信息
	@param[in] 
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 UpdateUploadInvInfo(CYWXML_GY &ywxml_gy);

	/*!
	@brief 安全通道连接测试
	@param[in] 
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr);


	/*!
	@brief 设备清库
	@param[in] 
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 ClearMidDepot(string &strErr);

	/*!
	@brief 修改金税盘时钟
	@param[in] 修改时间“20150909122023”
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	INT32 UpdateClockProc(CYWXML_GY &ywxml_gy, string strTime, string &strErr);


};


#endif


