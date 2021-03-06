/*! \file   PrintDriver.h
   \brief   打印驱动
   \author  Yin Chuntian
 */
#ifndef PRINT_DRIVER_H
#define PRINT_DRIVER_H

#include "comdatatype.h"
#include "VersionConfig.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define PRINTER_INTERRUPT 		0
#define SIDA_PRINTER			1


/*!
@brief	    打开打印机设备文件
@details	初始化内容包括:清除打印缓冲区、恢复默认值、选择字符集1、删除用户定义字符
@others		命令(HEX)：1B  40  
*/
void OpenPrinterDEV();



#if (POS_TYPE == POS_APE4000RG)

/*!
@brief		为与非4000RG的打印机程序匹配而加,无实际意义
*/
void PrinterIni(UINT8 bidirectionalPrint);


/*!
@brief		该命令初始化打印机,4000RG款机所用映美打印机的独有初始化函数
@details	初始化内容包括:清除打印缓冲和行编辑缓存、恢复缺省值、设置字符汉字打印方式、删除自定义字符
@param[in]  bidirectionalPrint 打印参数  
@others		命令(HEX)：1B  40 (ESC @)
*/
void YMPrinterIni(void);

/*!
@brief		进入汉字打印命令
@details	打印机接收到以上命令后，将从5×7点阵ASCII字符打印状态转换到16×16点阵的汉字打印状态。汉字代码是2

字节对应一个汉字的标准机内码
@others		命令(HEX)：1C  26

@brief		选择中文方式下的打印模式
@details	n的bit2(0倍宽无效,1倍宽有效),bit3(0倍高无效,1倍高有效),bit7(0下划线无效,1下划线有效)
@others		命令(HEX)：1C  21 n
*/
void SetChineseMode(void);


/*!
@brief		退出汉字打印命令
@details	打印机接收以上命令后，将从汉字打印状态切换到5×7或7×7点阵ASCII字符打印状态。可实现16×16点阵汉

字与5×7点阵ASCII字符同行混合打印 
@details	n的bit0(字模选择0:5×7,1:7×7),bit5(0倍宽无效,1倍宽有效),bit4(0倍高无效,1倍高有效),bit7(0下划线

无效,1下划线有效)
@others		命令(HEX)：1B  21 n
*/
void SetAsciiMode(void);


/*!
@brief		打印并走纸
@details	打印并走纸n/144英寸，如缓冲区无内容可打，则直接走纸
@param[in]	N 走纸的步数,一步为1/144英寸,0.176mm
@others		命令(HEX)：1B  4A  n
*/
void ForwardNPoint(UINT16 N);


/*!
@brief		打印并进纸n字符行
@details	打印行缓冲器里的数据并向前走纸n字符行, n=0~255, 这个命令不包含回车换行，也不影响后面的换行命令。 
@param[in]	N 行数
@others		命令(HEX)：1B  64  n 
*/
void ForwardNLine(UINT8 N);

/*!
@brief		执行汉字倍宽打印,选择中文方式下的打印模式
@details	打印机在接收到此命令后，打印的汉字将在横向放大一倍，纵向不改变。当遇到FS DC4、CR、LF等命令或自动

换行之后，则退出汉字倍宽打印。即每个倍宽方式的执行最多保持一行 
@details	n的bit2(0倍宽无效,1倍宽有效),bit3(0倍高无效,1倍高有效),bit7(0下划线无效,1下划线有效)
@others		命令(HEX)：1C  21 n
*/
void SetDoubleChineseMode(void);


/*!
@brief		取消汉字倍宽打印,选择中文方式下的打印模式
@details	取消汉字倍宽打印方式。恢复标准汉字打印，可实现不同宽度的汉字同行混合打印
@details	n的bit2(0倍宽无效,1倍宽有效),bit3(0倍高无效,1倍高有效),bit7(0下划线无效,1下划线有效)
@others		命令(HEX)：1C  21 n
*/
void CancelDoubleChineseMode(void);


/*!
@brief       设定字符行距为 n/144 英寸
@details     设置行间距为 n/144英寸, n的值是0-255之间, 默认值：n=24
@details     走纸与设置行间距的单位都是1/144 英寸,打印机的点距是2/144 英寸,因此9针打印机一行字符的高度至少是

16/144 英寸
@details     为不引起重行,n值应大于16
@param[in]   N  行间距步数
@others      命令(HEX)：1B  33  n 
*/
void SetLineSpace(UINT8 N);


/*!
@brief      打印并回车,注意该命令不实现换行命令
@details    打印存放在行编辑缓存中的一行数据，打印头自动退回左边备位
@others     命令(HEX)：0D
*/
void CarriageReturn(void);


/*!
@brief      打印并换行
@details	打印存放在行编辑缓存中的一行数据，并按当前设定的行距向前走纸一行。如果行编辑缓存空，则只按
@details	当前设定的行距向前走纸一行
@others		命令(HEX)：0A  
*/
void LineFormard(void);


/*!
@brief     执行黑标检测 
@details   执行黑标检测，检到黑标立即停止走纸并在串口返回值AAH，如检不到黑标则走完页长长度停止走纸并
@details   在串口返回值55H 
@others    命令(HEX)：1D 0C
*/
void SeekForntBorderBlackMark(void);


/*!
@brief    执行黑标检测 
@details   执行黑标检测，检到黑标立即停止走纸并在串口返回值AAH，如检不到黑标则走完页长长度停止走纸并
@details   在串口返回值55H 
@others   命令(HEX)：1D 0C  
*/
void SeekBackBorderBlackMark(void);


/*!
@brief      设置水平制表值
@details    输入水平造表位置,n1 n2等等，所有这些都应在该型号打印机机头的行宽之内，例如：n1=3,则执行水平造表时，

从第三个字符处开始打印。字符
@details    NUL加在最后，表示该命令的结束。所有输入的水平造表设置,都可以用该命令以ESC D NUL格式清除
@others     命令(HEX)：1B  44  n1 n2 n3 … 00
*/
void SetHT(void);

/*!
@brief      水平制表
@details    打印位置进行到下一水平制表位置, 如果没有设置水平造表值或者当前打印位置等于或超过最后一个水平造表值，

HT命令将不执行
@others     命令(HEX)：09 
*/
void ExecuteHT(void);


/*!
@brief    汉字打印一行字符
@details  打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平造表值或者当前打印位置等于或超过最后

一个水平造表值，HT命令将不执行 
*/
void PrintChineseLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief       倍宽打印一行字符
@details     打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		     造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]   LineBuff 打印的内容   BuffLen 打印内容的长度  
*/
void PrintDoubleChineseLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief      Ascii打印一行字符
@details    打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		    造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]  LineBuff 打印的内容   BuffLen 打印内容的长度 
*/
void PrintAsciiLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief       报表打印一行字符
@details     打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		     造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]   LineBuff 打印的内容   BuffLen 打印内容的长度 
*/
void PrintReportLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief  打印分行符  
*/
void PrintSeparateLine(void);

#if SIDA_PRINTER == 1

/*!
@brief       打印并反向走纸 
@details     打印出打印缓冲区的内容并反向走纸n*1/144英寸，n=0~48
@param[in]   N走纸行的点数 
@others      命令(HEX)：1B  4B  n
*/
void BackwardNPoint(UINT16 N);

/*!
@brief     设置字符右间距 
@details   以半点为设定单位（1/144英寸），设置字符右边间距为n个半点距,n=0~32,默认值n=0 
@param[in] N 字间距的点数
@others    命令(HEX)：1B  20  n
*/
void SetWordSpace(UINT8 N);

/*!
@brief      设置双向打印参数
@details    参数将永久保存在Flash 芯片，直到下次修改
@param[in]  N 双向打印参数  
@others     命令(HEX)：1B 10 03 00 07 N CHK 
*/
void SetBidirectionalPara(UINT8 N);

/*!
@brief      双向打印(BID)参数测试
@details    把从0 到9的各种BID 值的打印效果打印到样张，带‘*’号为当前的选择值
@others     命令(HEX)：1B 10 02 00 07 00 34
*/
void BidirectionalParaTest(void);

/*!
@brief     查询基本状态 
@return    返回基本状态,该命令在串口有效，打印机收到该指令后将当前打印机纸的状况以一个字节的形式传给上位机。该字

节的
@return    含义如下：当打印机无纸时，该字节bit2=1;有纸时，bit2=0;
@return    在黑标有效时，该字节bit7=1 表示当前处于黑标位置，bit7=0 则表示当前不是处于黑标位置；若黑标无
@return    效则该位无定义
@others    命令(HEX)：1B  76
*/
UINT8 GetPrinterStatus(void);

/*!
@brief      查询缓冲区使用行数
@return     返回缓冲区中尚未打印的行数
@others     命令(HEX)：1B  21
@others     映美打印机无此命令,其缓冲区采用先进先出的内存管理策略,因此该函数一直返回0
*/
UINT8 GetUsedLines(void);

/*!
@brief     查询缓冲区使用字节数
@return    查询缓冲区使用行数
@others    命令(HEX)：1B  24
*/
UINT16 GetUsedBytes(void);

void Code128Return(int n, int cmd);
void CodeTwo(int n, int cmd1, int cmd2);

/*!
@brief    打印二维条码
*/
int PrintBiznfo(unsigned char *input1,int VerticalNum,int HorizontalNum, int leftMargin);

int PrintBiznfo2(unsigned char *input1,unsigned char *input2,int VerticalNum,int HorizontalNum,int index);
#endif


#else		//POS_TYPE == POS_APE4000RG

/*!
@brief		向打印机发送初始化命令
@details	初始化内容包括:清除打印缓冲区、恢复默认值、选择字符集1、删除用户定义字符
@param[in]  bidirectionalPrint 打印参数  
@others		命令(HEX)：1B  40 
*/
void PrinterIni(UINT8 bidirectionalPrint);

/*!
@brief		进入汉字打印命令
@details	打印机接收到以上命令后，将从5×7点阵ASCII字符打印状态转换到16×16点阵的汉字打印状态。汉字代码是2字节对应一个汉字的标准机内码
@others		命令(HEX)：1C  26 
*/
void SetChineseMode(void);


/*!
@brief		退出汉字打印命令
@details	打印机接收以上命令后，将从汉字打印状态切换到5×7点阵ASCII字符打印状态。可实现16×16点阵汉字与5×7点阵ASCII字符同行混合打印 
@others		命令(HEX)：1C  2E 
*/
void SetAsciiMode(void);


/*!
@brief		执行n点行走纸
@details	打印机接收到以上命令后，向前走n点行，n的值在1-255范围内。这个命令不包含回车换行，也不影响后面的换行命令。
@param[in]	N 走纸的点数
@others		命令(HEX)：1B  4A  n
*/
void ForwardNPoint(UINT16 N);


/*!
@brief     空走N行
@param[in] N 行数 
*/
void ForwardNLine(UINT8 N);

/*!
@brief    执行汉字倍宽打印
@details  打印机在接收到此命令后，打印的汉字将在横向放大一倍，纵向不改变。当遇到FS DC4、CR、LF等命令或自动换行之后，则退出汉字倍宽打印。即每个倍宽方式的执行最多保持一行 
@others   命令(HEX)：1C  0E 
*/
void SetDoubleChineseMode(void);


/*!
@brief    取消汉字倍宽打印
@details  取消由FS SO命令执行的汉字倍宽打印方式。恢复标准汉字打印，可实现不同宽度的汉字同行混合打印
@oters    命令(HEX)：1C  0E 
*/
void CancelDoubleChineseMode(void);


/*!
@brief       设置 n点行间距
@details     为后面的换行命令设置n点行间距，n的值是0-255之间，在使用ESC K命令打印点阵图形时，通常设置n=0。文本打印时通常设置n=3
@param[in]   N  行间距点数
@others      命令(HEX)：1B  31  n 
*/
void SetLineSpace(UINT8 N);


/*!
@brief      回车
@details    当发送一个CR命令到打印机时，在缓冲区中的所有字符或汉字都将被打印出来，而且纸向前走一行 
@others     命令(HEX)：0D
*/
void CarriageReturn(void);


/*!
@brief     换行
@details   打印机向前走一个字符行
@others    命令(HEX)：0A  
*/
void LineFormard(void);


/*!
@brief     检测黑标前沿
@details   打打印机收到此命令后，向前走纸，直到检测到黑标的前沿时停止走纸 
@others    命令(HEX)：16
*/
void SeekForntBorderBlackMark(void);


/*!
@brief    检测黑标后沿
@details  打印机收到此命令后，向前走纸，直到检测到黑标的后沿时停止走纸。即检测到黑标前沿时并不停止走纸
@others   命令(HEX)：17  
*/
void SeekBackBorderBlackMark(void);


/*!
@brief      设置水平造表值
@details    输入水平造表位置,n1 n2等等，所有这些都应在该型号打印机机头的行宽之内，例如：n1=3,则执行水平造表时，从第三个字符处开始打印。字符
		    NUL加在最后，表示该命令的结束。所有输入的水平造表设置,都可以用该命令以ESC D NUL格式清除
@others     命令(HEX)：1B  44  n1 n2 n3 … 00
*/
void SetHT(void);

/*!
@brief      执行水平造表
@details    打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@others     命令(HEX)：09 
*/
void ExecuteHT(void);


/*!
@brief    汉字打印一行字符
@details  打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行 
*/
void PrintChineseLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief       倍宽打印一行字符
@details     打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		     造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]   LineBuff 打印的内容   BuffLen 打印内容的长度  
*/
void PrintDoubleChineseLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief      Ascii打印一行字符
@details    打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		    造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]  LineBuff 打印的内容   BuffLen 打印内容的长度 
*/
void PrintAsciiLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief       报表打印一行字符
@details     打印位置进行到由ESC D命令设置的下一水平造表位置。如果没有设置水平
		     造表值或者当前打印位置等于或超过最后一个水平造表值，HT命令将不执行
@param[in]   LineBuff 打印的内容   BuffLen 打印内容的长度 
*/
void PrintReportLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief  打印分行符  
*/
void PrintSeparateLine(void);

#if SIDA_PRINTER == 1

/*!
@brief       执行n点行走纸
@details     打印机接收到以上命令后，向前走n点行，n的值在1-255范围内。这个命令不包含回车换行，也不影响后面的换行命令
@param[in]   N走纸行的点数 
@others      命令(HEX)：1B  49  n
*/
void BackwardNPoint(UINT16 N);

/*!
@brief     设置 n点字间距
@details   为后面的换行命令设置n点行间距，n的值是0-255之间，在使用ESC K命令打印点阵图形时，通常设置n=0。文本打印时通常设置n=3
@param[in] N 字间距的点数
@others    命令(HEX)：1B  32  n
*/
void SetWordSpace(UINT8 N);

/*!
@brief      设置双向打印参数
@details    为后面的换行命令设置n点行间距，n的值是0-255之间，在使用ESC K命令 打印点阵图形时，通常设置n=0。文本打印时通常设置n=3
@param[in]  N 双向打印参数  
@others     命令(HEX)：1B  33  n
*/
void SetBidirectionalPara(UINT8 N);

/*!
@brief     查询基本状态 
@return    返回基本状态
@others    命令(HEX)：1B  23
*/
UINT8 GetPrinterStatus(void);

/*!
@brief      查询缓冲区使用行数
@return     查询缓冲区使用行数
@others     命令(HEX)：1B  21
*/
UINT8 GetUsedLines(void);


/*!
@brief     查询缓冲区使用字节数
@return    查询缓冲区使用行数
@others    命令(HEX)：1B  24
*/
UINT16 GetUsedBytes(void);

void Code128Return(int n, int cmd);
void CodeTwo(int n, int cmd1, int cmd2);

/*!
@brief    打印二维条码
*/
int PrintBiznfo(unsigned char *input1,int VerticalNum,int HorizontalNum, int leftMargin);

int PrintBiznfo2(unsigned char *input1,unsigned char *input2,int VerticalNum,int HorizontalNum,int index);

#endif


#endif		//POS_TYPE == POS_APE4000RG



#ifdef __cplusplus
}
#endif

#endif
