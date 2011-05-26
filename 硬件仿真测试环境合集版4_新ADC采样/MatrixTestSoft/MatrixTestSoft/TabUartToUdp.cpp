// TabUartToUdp.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabUartToUdp.h"


// CTabUartToUdp 对话框
HANDLE	hCom;				// 准备打开的串口的句柄
HANDLE	hCommWatchThread;	// 辅助线程的全局函数
UINT CommWatchProc(CTabUartToUdp *pwnd);	// 线程函数

IMPLEMENT_DYNAMIC(CTabUartToUdp, CDialog)

CTabUartToUdp::CTabUartToUdp(CWnd* pParent /*=NULL*/)
	: CDialog(CTabUartToUdp::IDD, pParent)
	, m_usUartBufCount(0)
	, m_uiUartCount(0)
	, m_bUartThreadclose(FALSE)
{

}

CTabUartToUdp::~CTabUartToUdp()
{
}

void CTabUartToUdp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_COM, m_comboSerialPortCom);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_BAUD, m_comboSerialPortBaud);
}


BEGIN_MESSAGE_MAP(CTabUartToUdp, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERIALPORT_OPEN, &CTabUartToUdp::OnBnClickedButtonSerialportOpen)
	ON_BN_CLICKED(IDC_BUTTON_SERIALPORT_CLOSE, &CTabUartToUdp::OnBnClickedButtonSerialportClose)
END_MESSAGE_MAP()

// 初始化设置
void CTabUartToUdp::OnInit(void)
{
	//端口设置
	m_comboSerialPortCom.SetWindowText( _T(COM0) );		// 设置控件初始化显示
	m_comboSerialPortCom.InsertString( 0, _T(COM0) );	// 插入下拉菜单选项
	m_comboSerialPortCom.InsertString( 1, _T(COM1) );
	m_comboSerialPortCom.InsertString( 2, _T(COM2) );
	m_comboSerialPortCom.InsertString( 3, _T(COM3) );
	m_comboSerialPortCom.InsertString( 4, _T(COM4) );
	m_comboSerialPortCom.InsertString( 5, _T(COM5) );
	m_comboSerialPortCom.InsertString( 6, _T(COM6) );
	m_comboSerialPortCom.InsertString( 7, _T(COM7) );
	m_comboSerialPortCom.InsertString( 8, _T(COM8) );
	m_comboSerialPortCom.InsertString( 9, _T(COM16) );

	//波特率设置
	m_comboSerialPortBaud.SetWindowText( _T(BAUD11) );	// 设置控件初始化显示
	m_comboSerialPortBaud.InsertString( 0, _T(BAUD0) );	// 插入下拉菜单选项
	m_comboSerialPortBaud.InsertString( 1, _T(BAUD1) );
	m_comboSerialPortBaud.InsertString( 2, _T(BAUD2) );
	m_comboSerialPortBaud.InsertString( 3, _T(BAUD3) );
	m_comboSerialPortBaud.InsertString( 4, _T(BAUD4) );
	m_comboSerialPortBaud.InsertString( 5, _T(BAUD5) );
	m_comboSerialPortBaud.InsertString( 6, _T(BAUD6) );
	m_comboSerialPortBaud.InsertString( 7, _T(BAUD7) );
	m_comboSerialPortBaud.InsertString( 8, _T(BAUD8) );
	m_comboSerialPortBaud.InsertString( 9, _T(BAUD9) );
	m_comboSerialPortBaud.InsertString( 10, _T(BAUD10) );
	m_comboSerialPortBaud.InsertString( 11, _T(BAUD11) );

	// 串口通讯设置
// 	m_ctrlMSComm1.put_InBufferCount(0);		// 清空接收缓存
// 	m_ctrlMSComm1.put_OutBufferCount(0);	// 清空发送缓存
// 	m_ctrlMSComm1.put_InputMode(1);         // 二进制模式
	CString str;
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->SetWindowText("127.0.0.1");
	str.Format("0x%04x",0x9001);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->SetWindowText(str);	// 0x9001
	str.Format("0x%04x",0x9002);
	GetDlgItem(IDC_EDIT_PORT_REC)->SetWindowText(str);			// 0x9002

	m_usUartBufCount = 0;
	m_uiUartCount = 0;
}

// 得到当前选择的串口号

int CTabUartToUdp::OnGetSerialPortCom(void)
{
	int iCurrentCom = 0;
	CString str;
	m_comboSerialPortCom.GetWindowText(str);	
	if (str == _T(COM0))
	{
		iCurrentCom = 1;
	}
	else if (str == _T(COM1))
	{
		iCurrentCom = 2;
	}
	else if (str == _T(COM2))
	{
		iCurrentCom = 3;
	}
	else if (str == _T(COM3))
	{
		iCurrentCom = 4;
	}
	else if (str == _T(COM4))
	{
		iCurrentCom = 5;
	}
	else if (str == _T(COM5))
	{
		iCurrentCom = 6;
	}
	else if (str == _T(COM6))
	{
		iCurrentCom = 7;
	}
	else if (str == _T(COM7))
	{
		iCurrentCom = 8;
	}
	else if (str == _T(COM8))
	{
		iCurrentCom = 9;
	}
	else if (str == _T(COM16))
	{
		iCurrentCom = 17;
	}
	else
	{
		AfxMessageBox(_T("Input Serial Port Com Nb is Wrong!"));
	}
	return iCurrentCom;
}

// 得到当前选择的波特率
int CTabUartToUdp::OnGetSerialPortBaud(void)
{
	int iCurrentBaud = 0;
	CString str;
	m_comboSerialPortBaud.GetWindowText(str);	
	if (str == _T(BAUD0))
	{
		iCurrentBaud = 300;
	}
	else if (str == _T(BAUD1))
	{
		iCurrentBaud = 600;
	}
	else if (str == _T(BAUD2))
	{
		iCurrentBaud = 1200;
	}
	else if (str == _T(BAUD3))
	{
		iCurrentBaud = 2400;
	}
	else if (str == _T(BAUD4))
	{
		iCurrentBaud = 4800;
	}
	else if (str == _T(BAUD5))
	{
		iCurrentBaud = 9600;
	}
	else if (str == _T(BAUD6))
	{
		iCurrentBaud = 19200;
	}
	else if (str == _T(BAUD7))
	{
		iCurrentBaud = 38400;
	}
	else if (str == _T(BAUD8))
	{
		iCurrentBaud = 43000;
	}
	else if (str == _T(BAUD9))
	{
		iCurrentBaud = 56000;
	}
	else if (str == _T(BAUD10))
	{
		iCurrentBaud = 57600;
	}	
	else if (str == _T(BAUD11))
	{
		iCurrentBaud = 115200;
	}
	else
	{
		AfxMessageBox(_T("Input Serial Port Baud is Wrong!"));
	}

	return iCurrentBaud;
}

// 从UDP发送数据
void CTabUartToUdp::OnSendFromUDP(unsigned char* TXDATA, unsigned int uiCount)
{
	unsigned int uiFrameCount = 0;
	unsigned char ucTxdata[256];
	CString str;
	CString strIP;
	int iSendPort;
	uiFrameCount = uiCount/256;
	if (uiFrameCount == 0)
	{
		return;
	}
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->GetWindowText(str);
	sscanf_s(str,"%x", &iSendPort);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->GetWindowText(str);
	strIP = str;
	for (unsigned int i=0; i<uiFrameCount; i++)
	{
		memcpy(&ucTxdata, &TXDATA[i*256], 256);
		m_socketUartToUdp.SendTo(ucTxdata, 256, iSendPort, strIP);
	}
}
UINT CommWatchProc(CTabUartToUdp *pwnd)
{
	unsigned char lpBuffer[1024];
	unsigned long datacount;	//接收数据的数量

	OVERLAPPED wol;
	wol.Internal=0;
	wol.InternalHigh=0;
	wol.Offset=0;
	wol.OffsetHigh=0;
	wol.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

	while(1)
	{
		if (pwnd->m_bUartThreadclose == TRUE)
		{
			break;
		}
		ReadFile(hCom, lpBuffer, 256, &datacount, &wol);	
		if (datacount!=0)			//收到有效数据
		{							//把接收的数据作为参数传给消息相应函数
			pwnd->OnUartReceiveData(lpBuffer, datacount);
		}
		if (pwnd->m_bUartThreadclose == TRUE)
		{
			break;
		}
		Sleep(5);
	}
	return 1;
}

void CTabUartToUdp::OnBnClickedButtonSerialportOpen()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	// 打开串口
	OnOpenCom();
	m_bUartThreadclose = FALSE;
	DWORD threadID;							// 启动USB口监视线程
	if (NULL != hCommWatchThread)
	{
		CloseHandle(hCommWatchThread);
	}
	hCommWatchThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 0,
		(LPTHREAD_START_ROUTINE)CommWatchProc,this, 0, &threadID);//hDevice  
	if (hCommWatchThread == NULL)
	{
		::AfxMessageBox(_T("创建接收线程失败!"));
	}
	GetDlgItem(IDC_BUTTON_SERIALPORT_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SERIALPORT_CLOSE)->EnableWindow(TRUE);
}

void CTabUartToUdp::OnBnClickedButtonSerialportClose()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	OnCloseCom();
	m_bUartThreadclose = TRUE;
	m_socketUartToUdp.Close();
	ControlEnable();
	AfxMessageBox(_T("Close Serial Port Successful!"));
	GetDlgItem(IDC_BUTTON_SERIALPORT_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SERIALPORT_CLOSE)->EnableWindow(FALSE);
}

// 使能控件
void CTabUartToUdp::ControlEnable(void)
{
	GetDlgItem(IDC_COMBO_SERIALPORT_COM)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SERIALPORT_BAUD)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT_REC)->EnableWindow(TRUE);
}

// 禁用控件
void CTabUartToUdp::ControlDisable(void)
{
	GetDlgItem(IDC_COMBO_SERIALPORT_COM)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SERIALPORT_BAUD)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT_REC)->EnableWindow(FALSE);
}

// 打开串口
void CTabUartToUdp::OnOpenCom(void)
{
	UpdateData(TRUE);
	CString str;
	m_comboSerialPortCom.GetWindowText(str);
	hCom =CreateFile( str, GENERIC_READ | GENERIC_WRITE/*允许读写*/,
		0/*此项必须为0*/,NULL/*no security attrs*/,
		OPEN_EXISTING/*设置产生方式*/,
		0/*使用同步通信*/,
		NULL );

	if(hCom!=INVALID_HANDLE_VALUE)			// 检测打开串口操作是否成功
	{
		AfxMessageBox(_T("Open Serial Port Successful!"));
	}
	else
	{
		AfxMessageBox(_T("Serial Port COM Nb is Invalid!"));
		return;
	}


	SetupComm( hCom, 1024,1024);					// 设置输入、输出缓冲区的大小

	PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR| PURGE_RXCLEAR );	// 清干净输入、输出缓冲区

	LPCOMMTIMEOUTS lpCommTimeouts = new COMMTIMEOUTS;//(LPCOMMTIMEOUTS)malloc(sizeof(LPCOMMTIMEOUTS));
	lpCommTimeouts->ReadIntervalTimeout=MAXDWORD; // 读间隔超时
	lpCommTimeouts->ReadTotalTimeoutMultiplier=0; // 读时间系数
	lpCommTimeouts->ReadTotalTimeoutConstant=0; // 读时间常量 
	lpCommTimeouts->WriteTotalTimeoutMultiplier=50; // 写时间系数
	lpCommTimeouts->WriteTotalTimeoutConstant=2000; // 写时间常量
	//加入读取和写入延时以避免同步通信过程中的线程阻塞情况

	SetCommTimeouts(hCom, lpCommTimeouts);

	DCB	dcb ; // 定义数据控制块结构

	GetCommState(hCom, &dcb ) ; //读串口原来的参数设置

	dcb.BaudRate = OnGetSerialPortBaud(); 
	dcb.ByteSize = 8; 
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT ;
	dcb.fBinary = TRUE ;
	dcb.fParity = FALSE;

	SetCommState(hCom, &dcb ) ; //串口参数配置

	int iRecPort;
	GetDlgItem(IDC_EDIT_PORT_REC)->GetWindowText(str);			// 0x9002
	sscanf_s(str,"%x", &iRecPort);
	// 创建Socket
	m_socketUartToUdp.Create(iRecPort,SOCK_DGRAM);
	m_socketUartToUdp.SetSockOpt(NULL,&m_socketUartToUdp,65536,SOL_SOCKET);
	ControlDisable();

}

// 关闭串口
void CTabUartToUdp::OnCloseCom(void)
{
	if(hCom != NULL)
	{
		CloseHandle(hCom);
	}
}

// 串口接收数据
void CTabUartToUdp::OnUartReceiveData(unsigned char* lpbuffer, unsigned int dwBytes)
{
	if(dwBytes > 0) 
	{
		if (dwBytes >1024)
		{
			AfxMessageBox(_T("Receive data from Uart leaked!"));
			return;
		} 

		for (unsigned int i=0; i<dwBytes; i++)
		{
			switch(m_uiUartCount)
			{
			case 0:
				if (lpbuffer[i] == 0x11)
				{
					m_ucUartBuf[m_usUartBufCount][0] = lpbuffer[i];
					m_uiUartCount++;
					break;
				}
				else
				{
					m_uiUartCount = 0;
					break;
				}

			case 1:
				if (lpbuffer[i] == 0x22)
				{
					m_ucUartBuf[m_usUartBufCount][1] = lpbuffer[i];
					m_uiUartCount++;
					break;
				}
				else
				{
					m_uiUartCount = 0;
					break;
				}
			case 2:
				if (lpbuffer[i] == 0x33)
				{
					m_ucUartBuf[m_usUartBufCount][2] = lpbuffer[i];
					m_uiUartCount++;
					break;
				}
				else
				{
					m_uiUartCount = 0;
					break;
				}
			case 3:
				if (lpbuffer[i] == 0x44)
				{
					m_ucUartBuf[m_usUartBufCount][3] = lpbuffer[i];
					m_uiUartCount++;
					break;
				}
				else
				{
					m_uiUartCount = 0;
					break;
				}
			default:
				m_ucUartBuf[m_usUartBufCount][m_uiUartCount] = lpbuffer[i];
				m_uiUartCount++;
				if (m_uiUartCount == 256)
				{
					m_uiUartCount = 0;
					OnSendFromUDP(m_ucUartBuf[m_usUartBufCount], 256);
					m_usUartBufCount += 1;
					m_usUartBufCount = m_usUartBufCount % 8;
				}
				break;
			}
		}
	}
}

// 关闭
void CTabUartToUdp::OnClose(void)
{
	OnCloseCom();
	m_socketUartToUdp.Close();
	m_bUartThreadclose = TRUE;
}
