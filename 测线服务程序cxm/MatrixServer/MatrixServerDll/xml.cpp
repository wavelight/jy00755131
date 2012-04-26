#include "stdafx.h"
#include "MatrixServerDll.h"

// 创建仪器通讯信息结构体
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	pCommInfo->m_pLogOutPut = NULL;
	pCommInfo->m_strDllXMLFilePath = "..\\parameter\\MatrixLineApp.XML";
	pCommInfo->m_strLineXMLFilePath = "..\\parameter\\Matrix.XML";
	pCommInfo->m_strOptXMLFilePath = "";
	InitializeCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 初始化ADC参数设置信息
	OnInitXMLADCSetupData(pCommInfo);
	// 重置测线客户端信息
	OnResetLineSetupData(pCommInfo);
	return pCommInfo;
}
// 初始化ADC参数设置信息
void OnInitXMLADCSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Survery
void OnResetSurveryList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSurveryStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Survery
	for (iter = pCommInfo->m_oLineSetupData.m_olsSurveryStruct.begin(); 
		iter != pCommInfo->m_oLineSetupData.m_olsSurveryStruct.end(); iter++)
	{
		if (iter->m_pcReceiverSection != NULL)
		{
			delete[] iter->m_pcReceiverSection;
		}
	}
	pCommInfo->m_oLineSetupData.m_olsSurveryStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Point Code
void OnResetPointCodeList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oPointCodeStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Survery
	for (iter = pCommInfo->m_oLineSetupData.m_olsPointCodeStruct.begin(); 
		iter != pCommInfo->m_oLineSetupData.m_olsPointCodeStruct.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
		}
		if (iter->m_pcSensorType != NULL)
		{
			delete[] iter->m_pcSensorType;
		}
	}
	pCommInfo->m_oLineSetupData.m_olsPointCodeStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Sensor
void OnResetSensorList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSensorStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Survery
	for (iter = pCommInfo->m_oLineSetupData.m_olsSensorStruct.begin(); 
		iter != pCommInfo->m_oLineSetupData.m_olsSensorStruct.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
		}
	}
	pCommInfo->m_oLineSetupData.m_olsSensorStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Marker
void OnResetMarkerList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Marker
	pCommInfo->m_oLineSetupData.m_olsMarkerStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Aux
void OnResetAuxList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oAuxStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Aux
	for (iter = pCommInfo->m_oLineSetupData.m_olsAuxStruct.begin(); 
		iter != pCommInfo->m_oLineSetupData.m_olsAuxStruct.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
		}
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
		}
	}
	pCommInfo->m_oLineSetupData.m_olsAuxStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Detour
void OnResetDetourList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Detour
	pCommInfo->m_oLineSetupData.m_olsDetourStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Mute
void OnResetMuteList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Mute
	pCommInfo->m_oLineSetupData.m_olsMuteStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置BlastMachine
void OnResetBlastMachineList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oBlastMachineStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// BlastMachine
	for (iter = pCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.begin(); 
		iter != pCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
		}
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
		}
	}
	pCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置Absolute
void OnResetAbsoluteList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	map<unsigned int, list<m_oAbsoluteStruct>>::iterator iterMap;
	list<m_oAbsoluteStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Absolute
	for (iterMap = pCommInfo->m_oLineSetupData.m_oAbsoluteStructMap.begin();
		iterMap != pCommInfo->m_oLineSetupData.m_oAbsoluteStructMap.end(); iterMap++)
	{
		for (iter = iterMap->second.begin(); iter != iterMap->second.end(); iter++)
		{
			if (iter->m_pcLabel != NULL)
			{
				delete[] iter->m_pcLabel;
			}
			if (iter->m_pcAbsoluteSpread != NULL)
			{
				delete[] iter->m_pcAbsoluteSpread;
			}
		}
		iterMap->second.clear();
	}
	pCommInfo->m_oLineSetupData.m_oAbsoluteStructMap.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 重置测线客户端信息
void OnResetLineSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// 重置Survery
	OnResetSurveryList(pCommInfo);
	// 重置Point Code
	OnResetPointCodeList(pCommInfo);
	// 重置Sensor
	OnResetSensorList(pCommInfo);
	// 重置Marker
	OnResetMarkerList(pCommInfo);
	// 重置Aux
	OnResetAuxList(pCommInfo);
	// 重置Detour
	OnResetDetourList(pCommInfo);
	// 重置Mute
	OnResetMuteList(pCommInfo);
	// 重置BlastMachine
	OnResetBlastMachineList(pCommInfo);
	// 重置Absolute
	OnResetAbsoluteList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// Generic
	pCommInfo->m_oLineSetupData.m_olsGenericStruct.clear();
	// Look
	pCommInfo->m_oLineSetupData.m_olsLookStruct.clear();
	// Form Line
	pCommInfo->m_oLineSetupData.m_olsFormLineStruct.clear();
	// Instrument Test base
	pCommInfo->m_oLineSetupData.m_olsInstrumentTestBaseStruct.clear();
	// Sensor Test base
	pCommInfo->m_oLineSetupData.m_olsSensorTestBaseStruct.clear();
	// Instrument Limit
	pCommInfo->m_oLineSetupData.m_olsInstrumentTestLimitStruct.clear();
	// Sensor Limit
	pCommInfo->m_oLineSetupData.m_olsSensorTestLimitStruct.clear();
	// Instrument Test
	pCommInfo->m_oLineSetupData.m_olsInstrumentTestStruct.clear();
	// Sensor Test
	pCommInfo->m_oLineSetupData.m_olsSensorTestStruct.clear();
	// Multple Test
	pCommInfo->m_oLineSetupData.m_olsMultpleTestStruct.clear();
	// SeisMonitor
	pCommInfo->m_oLineSetupData.m_olsSeisMonitorStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 打开程序配置文件
BOOL OpenAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo,
	string strXMLFilePath)
{
	if (pCommInfo == NULL)
	{
		return FALSE;
	}
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;
	CString str = _T("");
	strOLEObject = _T("msxml2.domdocument");
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 初始化COM库
	CoInitialize(NULL);
	if (FALSE == pCommInfo->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "CreateDispatch",
			ErrorType, IDS_ERR_XMLINTERFACE);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	str = strXMLFilePath.c_str();
	oVariant = str;
	if (false == IfFileExist(str))
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "",
			ErrorType, IDS_ERR_FILE_NOEXIST);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	if (FALSE == pCommInfo->m_oXMLDOMDocument.load(oVariant))
	{
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	return TRUE;
}
//加载IP地址设置数据
void LoadServerIP(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	CString csSrcIP = _T("");
	CString csDstIP = _T("");
	string strConv = "";
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到IP地址设置区
		strKey = _T("LineServerAppIPSetup");
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// 和现场仪器通讯的本机IP地址
		strKey = _T("IPForInstrument");
		csSrcIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csSrcIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiSrcIP = inet_addr(strConv.c_str());
		// LCI的IP地址
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiAimIP = inet_addr(strConv.c_str());
		// ADC数据返回地址
		strKey = _T("IPForADCData");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiADCDataReturnAddr = inet_addr(strConv.c_str());
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载端口设置数据
void LoadServerPort(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到IP地址设置区
		strKey = _T("LineServerAppPortSetup");
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = _T("PortLCI");
		pCommInfo->m_oXMLPortSetupData.m_usAimPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeartBeat");
		pCommInfo->m_oXMLPortSetupData.m_usHeartBeatReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeadFrame");
		pCommInfo->m_oXMLPortSetupData.m_usHeadFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForIPSet");
		pCommInfo->m_oXMLPortSetupData.m_usIPSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailFrame");
		pCommInfo->m_oXMLPortSetupData.m_usTailFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailTimeFrame");
		pCommInfo->m_oXMLPortSetupData.m_usTailTimeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTimeSet");
		pCommInfo->m_oXMLPortSetupData.m_usTimeDelayReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCSet");
		pCommInfo->m_oXMLPortSetupData.m_usADCSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForErrorCode");
		pCommInfo->m_oXMLPortSetupData.m_usErrorCodeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCData");
		pCommInfo->m_oXMLPortSetupData.m_usADCDataReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载ADC参数设置数据
void LoadServerADCSet(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey = _T("");
	CString strValue = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到ADC参数设置区
		strKey = _T("ADCSetSetup");
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// ADC设置正弦波命令大小
		strKey = _T("SetADCSetSineSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCSetSineSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置正弦波命令
		strKey = _T("SetADCSetSine");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCSetSineSize, strValue);

		// ADC设置停止采样命令大小
		strKey = _T("SetADCStopSampleSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCStopSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置停止采样命令
		strKey = _T("SetADCStopSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCStopSampleSize, strValue);

		// ADC设置打开TB电源低位大小
		strKey = _T("SetADCOpenTBPowerLowSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置打开TB电源低位
		strKey = _T("SetADCOpenTBPowerLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize, strValue);
	
		// ADC设置打开TB电源高位大小
		strKey = _T("SetADCOpenTBPowerHighSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置打开TB电源高位
		strKey = _T("SetADCOpenTBPowerHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize, strValue);
	
		// ADC设置打开TB开关低位大小
		strKey = _T("SetADCOpenSwitchTBLowSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置打开TB开关低位
		strKey = _T("SetADCOpenSwitchTBLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize, strValue);
	
		// ADC设置打开TB开关高位大小
		strKey = _T("SetADCOpenSwitchTBHighSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置打开TB开关高位
		strKey = _T("SetADCOpenSwitchTBHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize, strValue);
	
		// ADC设置读寄存器大小
		strKey = _T("SetADCRegisterReadSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterReadSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置读寄存器
		strKey = _T("SetADCRegisterRead");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterReadSize, strValue);

		// ADC设置写寄存器大小
		strKey = _T("SetADCRegisterWriteSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置写寄存器
		strKey = _T("SetADCRegisterWrite");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize, strValue);

		// ADC设置打开TB开关大小
		strKey = _T("SetADCTBSwitchOpenSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置打开TB开关
		strKey = _T("SetADCTBSwitchOpen");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize, strValue);
		
		// ADC采样设置大小
		strKey = _T("SetADCSampleSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC采样设置
		strKey = _T("SetADCSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCSampleSize, strValue);
		
		// ADC设置连续采样大小
		strKey = _T("SetADCReadContinuousSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCReadContinuousSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC设置连续采样
		strKey = _T("SetADCReadContinuous");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCReadContinuousSize, strValue);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Survery设置数据
void LoadSurvery(m_oSurveryStruct* pSurveryStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "LineName";
		pSurveryStruct->m_uiLine = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ReceiverSection";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSurveryStruct->m_usReceiverSectionSize = (unsigned short)strConv.size();
		pSurveryStruct->m_pcReceiverSection = new char[pSurveryStruct->m_usReceiverSectionSize];
		memcpy(pSurveryStruct->m_pcReceiverSection, strConv.c_str(), pSurveryStruct->m_usReceiverSectionSize);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Survery设置队列数据
void LoadSurveryList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Survery设置区
		strKey = "SurverySetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Survery总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oSurveryStruct oSurveryStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadSurvery(&oSurveryStruct, &oElement);
			// 增加Survery
			pCommInfo->m_oLineSetupData.m_olsSurveryStruct.push_back(oSurveryStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Survery设置数据
void LoadSurverySetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Survery
	OnResetSurveryList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Survery设置队列数据
		LoadSurveryList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Point Code设置数据
void LoadPointCode(m_oPointCodeStruct* pPointCodeStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		pPointCodeStruct->m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pPointCodeStruct->m_usLabelSize = (unsigned short)strConv.size();
		pPointCodeStruct->m_pcLabel = new char[pPointCodeStruct->m_usLabelSize];
		memcpy(pPointCodeStruct->m_pcLabel, strConv.c_str(), pPointCodeStruct->m_usLabelSize);
		strKey = "SensorType";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pPointCodeStruct->m_usSensorTypeSize = (unsigned short)strConv.size();
		pPointCodeStruct->m_pcSensorType = new char[pPointCodeStruct->m_usSensorTypeSize];
		memcpy(pPointCodeStruct->m_pcSensorType, strConv.c_str(), pPointCodeStruct->m_usSensorTypeSize);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Point Code设置队列数据
void LoadPointCodeList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到PointCode设置区
		strKey = "PointCodeSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到PointCode总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oPointCodeStruct oPointCodeStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadPointCode(&oPointCodeStruct, &oElement);
			// 增加PointCode
			pCommInfo->m_oLineSetupData.m_olsPointCodeStruct.push_back(oPointCodeStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Point Code设置数据
void LoadPointCodeSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Point Code
	OnResetPointCodeList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载PointCode设置队列数据
		LoadPointCodeList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Sensor设置数据
void LoadSensor(m_oSensorStruct* pSensorStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		pSensorStruct->m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSensorStruct->m_usLabelSize = (unsigned short)strConv.size();
		pSensorStruct->m_pcLabel = new char[pSensorStruct->m_usLabelSize];
		memcpy(pSensorStruct->m_pcLabel, strConv.c_str(), pSensorStruct->m_usLabelSize);
		strKey = "ContinuityMin";
		pSensorStruct->m_fContinuityMin = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "ContinuityMax";
		pSensorStruct->m_fContinuityMax = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "Tilt";
		pSensorStruct->m_fTilt = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "Noise";
		pSensorStruct->m_fNoise = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "Leakage";
		pSensorStruct->m_fLeakage = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "SEGDCode";
		pSensorStruct->m_uiSEGDCode = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Sensor设置队列数据
void LoadSensorList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Sensor设置区
		strKey = "SensorSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Sensor总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oSensorStruct oSensorStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadSensor(&oSensorStruct, &oElement);
			// 增加Sensor
			pCommInfo->m_oLineSetupData.m_olsSensorStruct.push_back(oSensorStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Sensor设置数据
void LoadSensorSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Sensor
	OnResetSensorList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Sensor设置队列数据
		LoadSensorList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Marker设置数据
void LoadMarker(m_oMarkerStruct* pMarkerStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "BoxType";
		pMarkerStruct->m_uiBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SN";
		pMarkerStruct->m_uiSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "LineName";
		pMarkerStruct->m_uiLineName = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "PointNb";
		pMarkerStruct->m_uiPointNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ChannelNb";
		pMarkerStruct->m_uiChannelNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "MarkerIncr";
		pMarkerStruct->m_uiMarkerIncr = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Reversed";
		pMarkerStruct->m_uiReversed = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Marker设置队列数据
void LoadMarkerList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Marker设置区
		strKey = "MarkerSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Marker总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oMarkerStruct oMarkerStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadMarker(&oMarkerStruct, &oElement);
			// 增加Marker
			pCommInfo->m_oLineSetupData.m_olsMarkerStruct.push_back(oMarkerStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Marker设置数据
void LoadMarkerSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Marker
	OnResetMarkerList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Marker设置队列数据
		LoadMarkerList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Aux设置数据
void LoadAux(m_oAuxStruct* pAuxStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		pAuxStruct->m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pAuxStruct->m_usLabelSize = (unsigned short)strConv.size();
		pAuxStruct->m_pcLabel = new char[pAuxStruct->m_usLabelSize];
		memcpy(pAuxStruct->m_pcLabel, strConv.c_str(), pAuxStruct->m_usLabelSize);
		strKey = "BoxType";
		pAuxStruct->m_uiBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SN";
		pAuxStruct->m_uiSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ChannelNb";
		pAuxStruct->m_uiChannelNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Gain";
		pAuxStruct->m_uiGain = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "DPGNb";
		pAuxStruct->m_uiDpgNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pAuxStruct->m_usCommentsSize = (unsigned short)strConv.size();
		pAuxStruct->m_pcComments = new char[pAuxStruct->m_usCommentsSize];
		memcpy(pAuxStruct->m_pcComments, strConv.c_str(), pAuxStruct->m_usCommentsSize);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Aux设置队列数据
void LoadAuxList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Aux设置区
		strKey = "AuxSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Aux总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oAuxStruct oAuxStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadAux(&oAuxStruct, &oElement);
			// 增加Aux
			pCommInfo->m_oLineSetupData.m_olsAuxStruct.push_back(oAuxStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Aux设置数据
void LoadAuxSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Aux
	OnResetAuxList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Aux设置队列数据
		LoadAuxList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Detour设置数据
void LoadDetour(m_oDetourStruct* pDetourStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "BoxTypeLow";
		pDetourStruct->m_uiLowBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SNLow";
		pDetourStruct->m_uiLowSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ChannelNbLow";
		pDetourStruct->m_uiLowChanNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "BoxTypeHigh";
		pDetourStruct->m_uiHighBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SNHigh";
		pDetourStruct->m_uiHighSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ChannelNbHigh";
		pDetourStruct->m_uiHighChanNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "StopMarking";
		pDetourStruct->m_uiStopMarking = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Detour设置队列数据
void LoadDetourList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Detour设置区
		strKey = "DetourSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Aux总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oDetourStruct oDetourStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadDetour(&oDetourStruct, &oElement);
			// 增加Aux
			pCommInfo->m_oLineSetupData.m_olsDetourStruct.push_back(oDetourStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Detour设置数据
void LoadDetourSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Detour
	OnResetDetourList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Detour设置队列数据
		LoadDetourList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Mute设置数据
void LoadMute(m_oMuteStruct* pMuteStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "LineName";
		pMuteStruct->m_uiLineName = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "PointNb";
		pMuteStruct->m_uiPointNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载Mute设置队列数据
void LoadMuteList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到Mute设置区
		strKey = "MuteSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到Mute总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oMuteStruct oMuteStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadMute(&oMuteStruct, &oElement);
			// 增加Mute
			pCommInfo->m_oLineSetupData.m_olsMuteStruct.push_back(oMuteStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Mute设置数据
void LoadMuteSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Mute
	OnResetMuteList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Mute设置队列数据
		LoadMuteList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载BlastMachine设置数据
void LoadBlastMachine(m_oBlastMachineStruct* pBlastMachineStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		pBlastMachineStruct->m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pBlastMachineStruct->m_usLabelSize = (unsigned short)strConv.size();
		pBlastMachineStruct->m_pcLabel = new char[pBlastMachineStruct->m_usLabelSize];
		memcpy(pBlastMachineStruct->m_pcLabel, strConv.c_str(), pBlastMachineStruct->m_usLabelSize);
		strKey = "BoxType";
		pBlastMachineStruct->m_uiBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SN";
		pBlastMachineStruct->m_uiSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ChannelNb";
		pBlastMachineStruct->m_uiChannelNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Gain";
		pBlastMachineStruct->m_uiGain = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "DPGNb";
		pBlastMachineStruct->m_uiDpgNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pBlastMachineStruct->m_usCommentsSize = (unsigned short)strConv.size();
		pBlastMachineStruct->m_pcComments = new char[pBlastMachineStruct->m_usCommentsSize];
		memcpy(pBlastMachineStruct->m_pcComments, strConv.c_str(), pBlastMachineStruct->m_usCommentsSize);
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//加载BlastMachine设置队列数据
void LoadBlastMachineList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// 找到BlastMachine设置区
		strKey = "BlastMachineSetup";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// 找到入口
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// 得到BlastMachine总数
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// 得到队列
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oBlastMachineStruct oBlastMachineStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadBlastMachine(&oBlastMachineStruct, &oElement);
			// 增加BlastMachine
			pCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.push_back(oBlastMachineStruct);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载BlastMachine设置数据
void LoadBlastMachineSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置BlastMachine
	OnResetBlastMachineList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载BlastMachine设置队列数据
		LoadBlastMachineList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载Absolute设置数据
void LoadAbsolute(m_oAbsoluteStruct* pAbsoluteStruct,CXMLDOMElement* pElement)
{

}
//加载Absolute设置队列数据
void LoadAbsoluteList(m_oInstrumentCommInfoStruct* pCommInfo)
{

}
//加载Absolute设置索引数据
void LoadAbsoluteMap(m_oInstrumentCommInfoStruct* pCommInfo)
{

}
//加载Absolute设置数据
void LoadAbsoluteSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// 重置Absolute
	OnResetAbsoluteList(pCommInfo);
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strLineXMLFilePath))
	{
		//加载Absolute设置队列数据
		LoadAbsoluteList(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载测线客户端程序设置数据
void LoadLineAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	//加载Survery设置数据
	LoadSurverySetupData(pCommInfo);
	//加载Point Code设置数据
	LoadPointCodeSetupData(pCommInfo);
	//加载Sensor设置数据
	LoadSensorSetupData(pCommInfo);
	//加载Marker设置数据
	LoadMarkerSetupData(pCommInfo);
	//加载Aux设置数据
	LoadAuxSetupData(pCommInfo);
	//加载Detour设置数据
	LoadDetourSetupData(pCommInfo);
	//加载Mute设置数据
	LoadMuteSetupData(pCommInfo);
	//加载BlastMachine设置数据
	LoadBlastMachineSetupData(pCommInfo);
	//加载Absolute设置数据
	LoadAbsoluteSetupData(pCommInfo);
}
//加载IP地址设置数据
void LoadServerIPSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		//加载IP地址设置数据
		LoadServerIP(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载端口设置数据
void LoadServerPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		//加载端口设置数据
		LoadServerPort(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载ADC参数设置数据
void LoadServerADCSetSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// 打开程序配置文件
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		//加载ADC参数设置数据
		LoadServerADCSet(pCommInfo);
	}
	// 关闭程序配置文件
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
//加载服务器程序设置数据
void LoadServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	//加载IP地址设置数据
	LoadServerIPSetupData(pCommInfo);
	//加载端口设置数据
	LoadServerPortSetupData(pCommInfo);
	//加载ADC参数设置数据
	LoadServerADCSetSetupData(pCommInfo);
}
// 初始化仪器通讯信息结构体
void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo, 
	m_oLogOutPutStruct* pLogOutPut)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_pLogOutPut = pLogOutPut;
	//加载服务器程序设置数据
	LoadServerAppSetupData(pCommInfo);
	//加载测线客户端程序设置数据
	LoadLineAppSetupData(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 关闭程序配置文件
void CloseAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_oXMLDOMDocument.DetachDispatch();
	// 释放COM库
	CoUninitialize();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 释放ADC参数设置信息结构体缓冲区
void OnFreeXMLADCSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// 释放仪器通讯信息结构体
void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	OnFreeXMLADCSetupData(pCommInfo);
	// 重置测线客户端信息
	OnResetLineSetupData(pCommInfo);
	DeleteCriticalSection(&pCommInfo->m_oSecCommInfo);
	delete pCommInfo;
}

