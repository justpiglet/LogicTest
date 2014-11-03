
// FieldEditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "FieldEditorDlg.h"
#include "afxdialogex.h"
#include "depend/cantools/jsoncpp/json/reader.h"
#include "Field/UserFieldManage.h"
#include "Field/GobalConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFieldEditorDlg �Ի���



CFieldEditorDlg::CFieldEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldEditorDlg::IDD, pParent)
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFieldEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
}

BEGIN_MESSAGE_MAP(CFieldEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFieldEditorDlg::OnBnClickedOk)

	ON_NOTIFY(NM_RCLICK, IDC_LIST_INFO, &CFieldEditorDlg::OnNMRClickListInfo)
	ON_COMMAND(ID_FEILD_INFO_PEEP, &CFieldEditorDlg::OnMenuClickPeepFieldInfo)
	ON_COMMAND(ID_SINGLE_PEEP, &CFieldEditorDlg::OnMenuClickPeepPwd)
	ON_BN_CLICKED(IDC_BUTTON2, &CFieldEditorDlg::OnBnClickedLogoin)
	ON_BN_CLICKED(IDC_BUTTON3, &CFieldEditorDlg::OnBnClickedInsertInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CFieldEditorDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BUTTON1, &CFieldEditorDlg::OnBnClickedCreateUser)
END_MESSAGE_MAP()


// CFieldEditorDlg ��Ϣ�������

BOOL CFieldEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	UserFieldManage::Share()->InitData();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	for (int i(0); i < FieldColumn_Max;++i)
		m_ListInfo.InsertColumn(i, g_FieldName[i], LVCFMT_LEFT, g_FieldLen[i], -1);
	UpdateListControl();

	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("(&L)Change"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFieldEditorDlg::OnPaint()
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
HCURSOR CFieldEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFieldEditorDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}




void CFieldEditorDlg::OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		if (pNMItemActivate->iSubItem >= FieldColumn_PwdLogin && pNMItemActivate->iSubItem <=FieldColumn_PwdLogin)
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


void CFieldEditorDlg::OnMenuClickPeepFieldInfo()
{
	// TODO:  �ڴ���������������
	int a = 9;
	a = a;
}


void CFieldEditorDlg::OnMenuClickPeepPwd()
{
	// TODO:  �ڴ���������������
	int a = 9;
	a = a;
}

void CFieldEditorDlg::UpdateListControl()
{
	m_ListInfo.DeleteAllItems();
	const CField* pField=UserFieldManage::Share()->GetCurUserFields();
	if (!pField)
		return;

	uint16 iCount = pField->GetFieldRow();
	for (int iRow(0), iColumn(0); iRow < iCount; ++iRow)
	{
		if (pField->IsShowRow(iRow))
		{
			const void* pData = pField->GetItem(iRow);
			if (pData)
			{
				m_ListInfo.SetItemData(iRow, (DWORD)pData);
				for (iColumn = 0; iColumn < FieldColumn_Max; ++iColumn)
				{
					if (iColumn == 0)
						m_ListInfo.InsertItem(iRow, pField->GetFieldItemCS(iRow, iColumn,true));
					else
						m_ListInfo.SetItemText(iRow, iColumn, pField->GetFieldItemCS(iRow, iColumn, true));

				}
			}// end if (pData)

		}//end if if (UserFieldManage::Share()->IsShowRow(iRow))

	}
}


void CFieldEditorDlg::OnBnClickedLogoin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}


void CFieldEditorDlg::OnBnClickedInsertInfo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFieldEditorDlg::OnBnClickedSetting()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFieldEditorDlg::OnBnClickedCreateUser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
