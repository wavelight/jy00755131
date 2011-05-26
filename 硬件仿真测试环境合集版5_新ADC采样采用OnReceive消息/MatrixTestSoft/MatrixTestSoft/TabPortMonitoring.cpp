// PortMonitoring.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabPortMonitoring.h"


// CPortMonitoring 对话框

IMPLEMENT_DYNAMIC(CTabPortMonitoring, CDialog)

CTabPortMonitoring::CTabPortMonitoring(CWnd* pParent /*=NULL*/)
	: CDialog(CTabPortMonitoring::IDD, pParent)
	, m_csRcvPort1(_T(""))
	, m_csSendPort1(_T(""))
	, m_csRcvPort2(_T(""))
	, m_csSendPort2(_T(""))
	, m_csIPRec(_T(""))
	, m_csIPSend(_T(""))
	, m_iSaveSize(1024)
	, m_bPortDistribution(FALSE)
//	, m_bStart(FALSE)
{

}

CTabPortMonitoring::~CTabPortMonitoring()
{
}

void CTabPortMonitoring::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PORTMONITORING, m_cTabCtrlItems);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPctrlRec);
	DDX_Control(pDX, IDC_IPADDRESS2, m_IPctrlSend);
	DDX_Text(pDX, IDC_EDIT_AIMRCVPORT1, m_csRcvPort1);
	DDX_Text(pDX, IDC_EDIT_AIMSENDPORT1, m_csSendPort1);
	DDX_Text(pDX, IDC_EDIT_AIMRCVPORT2, m_csRcvPort2);
	DDX_Text(pDX, IDC_EDIT_AIMSENDPORT2, m_csSendPort2);
	DDX_Text(pDX, IDC_EDIT_SAVESIZE, m_iSaveSize);
	DDX_Check(pDX, IDC_CHECK_PORTDISTRIBUTION, m_bPortDistribution);
}


BEGIN_MESSAGE_MAP(CTabPortMonitoring, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PORTMONITORING, &CTabPortMonitoring::OnTcnSelchangeTabPortmonitoring)
	ON_BN_CLICKED(IDC_BUTTON_PORTMONITORING_OPEN, &CTabPortMonitoring::OnBnClickedButtonPortmonitoringOpen)
	ON_BN_CLICKED(IDC_BUTTON_PORTMONITORING_CLOSE, &CTabPortMonitoring::OnBnClickedButtonPortmonitoringClose)
	ON_BN_CLICKED(IDC_BUTTON_STARTSAVE, &CTabPortMonitoring::OnBnClickedButtonStartsave)
	ON_BN_CLICKED(IDC_BUTTON_STOPSAVE, &CTabPortMonitoring::OnBnClickedButtonStopsave)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILEPATH, &CTabPortMonitoring::OnBnClickedButtonSavefilepath)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CTabPortMonitoring::OnBnClickedButtonReset)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// 初始化选项卡控件

void CTabPortMonitoring::InitTabControlItems(void)
{
	m_oPortMonitorRec.Create(IDD_DIALOG_PORTMONITORING_REC, GetDlgItem(IDC_TAB_PORTMONITORING));
	m_oPortMonitorSend.Create(IDD_DIALOG_PORTMONITORING_SEND,GetDlgItem(IDC_TAB_PORTMONITORING));
	

	//获得IDC_TABTEST客户区大小
	CRect rs;
	m_cTabCtrlItems.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top+=20; 

	//设置子对话框尺寸并移动到指定位置
	m_oPortMonitorRec.MoveWindow(&rs);
	m_oPortMonitorSend.MoveWindow(&rs);

	m_oPortMonitorRec.ScreenToClient(&rs);
	m_oPortMonitorSend.ScreenToClient(&rs);

	//分别设置隐藏和显示
	m_oPortMonitorRec.ShowWindow(TRUE);
	m_oPortMonitorSend.ShowWindow(FALSE);
	
	//设置默认的选项卡
	m_cTabCtrlItems.SetCurSel(0); 
	CString str;

	str=_T("接收帧");
	m_cTabCtrlItems.InsertItem(0,str);  //添加参数一选项卡
	str=_T("发送帧");
	m_cTabCtrlItems.InsertItem(1,str);  //添加参数二选项卡
}

void CTabPortMonitoring::OnTcnSelchangeTabPortmonitoring(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int CurSel = m_cTabCtrlItems.GetCurSel();
	switch(CurSel)
	{
	case 0:
		m_oPortMonitorRec.ShowWindow(TRUE); 
		m_oPortMonitorSend.ShowWindow(FALSE);
		Invalidate(TRUE);
		break;
	case 1:
		m_oPortMonitorRec.ShowWindow(FALSE);
		m_oPortMonitorSend.ShowWindow(TRUE);
		Invalidate(TRUE);
		break;
	default:
		;
	}    
	*pResult = 0;
}

void CTabPortMonitoring::OnBnClickedButtonPortmonitoringOpen()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
//	m_bStart = TRUE;
	CString str;
	int itemp;
	int flag = 0;
	UpdateData(TRUE);
	m_IPctrlRec.GetWindowText(m_csIPRec);
	m_IPctrlSend.GetWindowText(m_csIPSend);
	GetDlgItem(IDC_EDIT_AIMRCVPORT1)->GetWindowText(str);			// 0x8202
	sscanf_s(str,"%x", &itemp);
	m_hSocketRec.m_iRecPort = itemp;
	GetDlgItem(IDC_EDIT_AIMSENDPORT1)->GetWindowText(str);			// 0x9002
	sscanf_s(str,"%x", &itemp);
	m_hSocketRec.m_iSendPort = itemp;
	m_hSocketRec.m_csIP = m_csIPRec;
// 	m_oThreadRec.ResumeThread();
// 	m_oThreadRec.OnOpen();
	m_hSocketRec.Close();
	flag =  m_hSocketRec.Create(m_hSocketRec.m_iRecPort,SOCK_DGRAM);
	m_hSocketRec.SetSockOpt(NULL,&m_hSocketRec,65536,SOL_SOCKET);


	GetDlgItem(IDC_EDIT_AIMRCVPORT2)->GetWindowText(str);			// 0x9001
	sscanf_s(str,"%x", &itemp);
	m_hSocketSend.m_iRecPort = itemp;
	GetDlgItem(IDC_EDIT_AIMSENDPORT2)->GetWindowText(str);			// 0x8201
	sscanf_s(str,"%x", &itemp);
	m_hSocketSend.m_iSendPort = itemp;
	m_hSocketSend.m_csIP = m_csIPSend;
// 	m_oThreadSend.ResumeThread();
// 	m_oThreadSend.OnOpen();
	m_hSocketSend.Close();
	flag =  m_hSocketSend.Create(m_hSocketSend.m_iRecPort,SOCK_DGRAM);
	m_hSocketSend.SetSockOpt(NULL,&m_hSocketSend,65536,SOL_SOCKET);

	m_hSocketSend.m_bPortDistribution = m_bPortDistribution;
	m_oSaveFile.m_iSaveSize = m_iSaveSize;
	
	m_IPctrlRec.EnableWindow(FALSE);
	m_IPctrlSend.EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PORTDISTRIBUTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SAVESIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AIMRCVPORT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AIMSENDPORT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AIMRCVPORT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AIMSENDPORT2)->EnableWindow(FALSE);
}

void CTabPortMonitoring::OnBnClickedButtonPortmonitoringClose()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

//	m_bStart = FALSE;
// 	m_oThreadRec.SuspendThread();
// 	m_oThreadRec.OnStop();
// 	m_oThreadSend.SuspendThread();
// 	m_oThreadSend.OnStop();
	m_hSocketRec.Close();
	m_hSocketSend.Close();

	m_IPctrlRec.EnableWindow(TRUE);
	m_IPctrlSend.EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_PORTDISTRIBUTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SAVESIZE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_AIMRCVPORT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_AIMSENDPORT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_AIMRCVPORT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_AIMSENDPORT2)->EnableWindow(TRUE);
}

void CTabPortMonitoring::OnBnClickedButtonStartsave()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_oSaveFile.OnSaveStart();
	
}

void CTabPortMonitoring::OnBnClickedButtonStopsave()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_oSaveFile.OnSaveStop();
}

void CTabPortMonitoring::OnBnClickedButtonSavefilepath()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_oSaveFile.m_hWnd = this->m_hWnd;
	m_oSaveFile.OnSelectSaveFilePath();
}

void CTabPortMonitoring::OnBnClickedButtonReset()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_oSaveFile.OnReset();
//	m_oThreadRec.OnReset();
//	m_oThreadSend.OnReset();
	m_hSocketRec.OnReset();
	m_hSocketSend.OnReset();
	UpdateData(FALSE);
}

// 初始化
void CTabPortMonitoring::OnInit(void)
{
	InitTabControlItems();

	m_oSaveFile.m_pWndTab = this;
	m_oSaveFile.OnInit();

	// 串口调试环境
	m_IPctrlRec.SetAddress(127,0,0,1);
	m_IPctrlSend.SetAddress(127,0,0,1);
	// 并口调试环境
	//  	m_IPctrlRec.SetAddress(192,168,0,12);
	//  	m_IPctrlSend.SetAddress(192,168,0,11);

	m_csRcvPort1.Format("0x%04x", 0x8202);
	m_csSendPort1.Format("0x%04x", 0x9002);
	m_csRcvPort2.Format("0x%04x", 0x9001);
	m_csSendPort2.Format("0x%04x", 0x8201);

	m_bPortDistribution = TRUE;
	UpdateData(FALSE);

	m_hSocketSend.m_pWndTab = this;
	m_hSocketSend.m_pwnd = &(this->m_oPortMonitorRec);
	
	m_hSocketRec.m_pWndTab = this;
	m_hSocketRec.m_pwnd = &(this->m_oPortMonitorSend);

	m_hSocketRec.m_pSaveFile = &m_oSaveFile;
	m_hSocketSend.m_pSaveFile = &m_oSaveFile;

	// ADC数据采集上一帧的数据指针偏移量
	for (int i=0; i<GraphViewNum; i++)
	{
		m_hSocketSend.m_usADCLastDataPoint[i] = 0;
	}

// 	m_oThreadRec.OnInit();
// 	m_oThreadRec.CreateThread();
// 	m_oThreadRec.SuspendThread();
// 
// 	m_oThreadSend.OnInit();
// 	m_oThreadSend.CreateThread();
// 	m_oThreadSend.SuspendThread();
}

void CTabPortMonitoring::OnClose()
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
//	int iResult = 0;
// 	m_oThreadSend.OnClose();
// 	m_oThreadRec.OnClose();
	m_hSocketSend.Close();
	m_hSocketRec.Close();
// 	if (m_bStart == FALSE)
// 	{
// 		return;
// 	}
// 	iResult = ::WaitForSingleObject(m_oThreadSend.m_hThreadSendClose,100);
// 	if (iResult != WAIT_OBJECT_0)
// 	{
// 		AfxMessageBox(_T("发送线程在100ms内未能正常结束！"));
// 	}

// 	iResult = ::WaitForSingleObject(m_oThreadRec.m_hThreadRecClose,100);
// 	if (iResult != WAIT_OBJECT_0)
// 	{
// 		AfxMessageBox(_T("接收线程在100ms内未能正常结束！"));
// 	}
}