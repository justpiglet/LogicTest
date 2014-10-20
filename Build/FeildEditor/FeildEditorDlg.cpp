
// FeildEditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FeildEditor.h"
#include "FeildEditorDlg.h"
#include "afxdialogex.h"
#include"cantools/jsoncpp/json/reader.h"
#include "Feild/UserFeildManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeildEditorDlg �Ի���



CFeildEditorDlg::CFeildEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeildEditorDlg::IDD, pParent)
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFeildEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
}

BEGIN_MESSAGE_MAP(CFeildEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFeildEditorDlg::OnBnClickedOk)

	ON_NOTIFY(NM_RCLICK, IDC_LIST_INFO, &CFeildEditorDlg::OnNMRClickListInfo)
	ON_COMMAND(ID_FEILD_INFO_PEEP, &CFeildEditorDlg::OnMenuClickPeepFeildInfo)
	ON_COMMAND(ID_SINGLE_PEEP, &CFeildEditorDlg::OnMenuClickPeepPwd)
	ON_BN_CLICKED(IDC_BUTTON2, &CFeildEditorDlg::OnBnClickedLogoin)
	ON_BN_CLICKED(IDC_BUTTON3, &CFeildEditorDlg::OnBnClickedInsertInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CFeildEditorDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BUTTON1, &CFeildEditorDlg::OnBnClickedCreateUser)
END_MESSAGE_MAP()


// CFeildEditorDlg ��Ϣ�������

BOOL CFeildEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	for (int i(0); i < FeildColumn_Max;++i)
		m_ListInfo.InsertColumn(i, g_FeildName[i], LVCFMT_LEFT, g_FeildLen[i], -1);
	UpdateListControl();

	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("(&L)Change"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFeildEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFeildEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFeildEditorDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}




void CFeildEditorDlg::OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bool isAll(true),isShow(false);
	if (pNMItemActivate->iItem != -1)
	{
		isShow = true;
	}
	else
	{
		if (pNMItemActivate->iSubItem >= FeildColumn_PwdLogin && pNMItemActivate->iSubItem <=FeildColumn_PwdLogin)
		{
			isShow = true;
			isAll = false;
		}
	}
		

	if (isShow)
	{
			DWORD dwpos = GetMessagePos();
			CPoint points(LOWORD(dwpos), HIWORD(dwpos));
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_USER_INFO));
			CMenu* popup = menu.GetSubMenu(isAll?1:0);
			if (popup)
				popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, points.x, points.y, this);
	}

	*pResult = 0;



}


void CFeildEditorDlg::OnMenuClickPeepFeildInfo()
{
	// TODO:  �ڴ���������������
	int a = 9;
	a = a;
}


void CFeildEditorDlg::OnMenuClickPeepPwd()
{
	// TODO:  �ڴ���������������
	int a = 9;
	a = a;
}

void CFeildEditorDlg::UpdateListControl()
{
	m_ListInfo.DeleteAllItems();
	uint16 iCount = UserFeildManage::Share()->GetFeildRow();
	for (int iRow(0), iColumn(0); iRow < iCount; ++iRow)
	{
		if (UserFeildManage::Share()->IsShowRow(iRow))
		{
			const void* pData = UserFeildManage::Share()->GetItem(iRow);
			if (pData)
			{
				m_ListInfo.SetItemData(iRow, (DWORD)pData);
				for (iColumn = 0; iColumn < FeildColumn_Max; ++iColumn)
				{
					if (iColumn == 0)
						m_ListInfo.InsertItem(iRow, UserFeildManage::Share()->GetFeildItemCS(iRow, iColumn));
					else
						m_ListInfo.SetItemText(iRow, iColumn, UserFeildManage::Share()->GetFeildItemCS(iRow, iColumn));

				}
			}// end if (pData)

		}//end if if (UserFeildManage::Share()->IsShowRow(iRow))

	}
}


void CFeildEditorDlg::OnBnClickedLogoin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}


void CFeildEditorDlg::OnBnClickedInsertInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFeildEditorDlg::OnBnClickedSetting()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFeildEditorDlg::OnBnClickedCreateUser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
