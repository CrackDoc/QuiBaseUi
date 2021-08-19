#include "QuiBaseWndBar.h"
#include "ui_QuiBaseWndBar.h"
#include <QMenu>
#include <QDesktopWidget>
CQuiBaseWndBar::CQuiBaseWndBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QuiBaseWndBar)
	, m_pGeometryWidget(parent)
	, m_bMaxWindow(false)
	, m_bMaxCurWndState(false)
{
    ui->setupUi(this);

	m_FrontRect = m_pGeometryWidget->geometry();
}
CQuiBaseWndBar::~CQuiBaseWndBar()
{
	
}
bool CQuiBaseWndBar::Initialize()
{
	ui->MinBtn->setIcon(QPixmap(":/resource/win_min.png"));
	ui->MaxBtn->setIcon(QPixmap(":/resource/win_remax.png"));
	ui->CloseBtn->setIcon(QPixmap(":/resource/win_close.png"));

	connect(ui->MinBtn, SIGNAL(clicked()), this, SIGNAL(SignalShowMinWindow()));

	connect(ui->MaxBtn, SIGNAL(clicked()), this, SIGNAL(SignalShowMaxWindow()));

	connect(ui->CloseBtn, SIGNAL(clicked()), this, SIGNAL(SignalCloseWindow()));

	return true;
}

bool CQuiBaseWndBar::AppendWidget(QWidget* widget)
{
	QHBoxLayout* layout = (QHBoxLayout*)ui->HWndBarBox->layout();
	if (layout)
	{
		int nSize = layout->count();
		QMenu* pQMenu = qobject_cast<QMenu*>(widget);
		QString strMenuModuleName = pQMenu->title();
		QPushButton* btn = new QPushButton(strMenuModuleName, pQMenu);
		btn->setParent(pQMenu);
		btn->setFlat(true);
		connect(btn, &QPushButton::clicked, this, &CQuiBaseWndBar::SlotMenuClicked);
		btn->setFixedSize(QSize(70, 25));
		layout->insertWidget(nSize - 1, btn);
		m_MapMenu[strMenuModuleName] = pQMenu;
		return true;
	}
	return false;
}

void CQuiBaseWndBar::SetGeometryWidget(QWidget* widget)
{
	m_pGeometryWidget = widget;
}

void CQuiBaseWndBar::SetMaxWindow(bool bMaxWnd)
{
	if (m_bMaxCurWndState == bMaxWnd)
	{
		return;
	}
	if (!bMaxWnd)
	{
		m_pGeometryWidget->setGeometry(m_FrontRect);
		m_bMaxCurWndState = false;
	}
	else 
	{
		m_FrontRect = m_pGeometryWidget->geometry();
		QDesktopWidget* desktopWidget = QApplication::desktop();
		//const QRect screenRect = desktopWidget->screenGeometry();  //��Ļ����
		const QRect screenRect = desktopWidget->availableGeometry();  //��Ļ����
		int w = screenRect.width() + 18;
		int h = screenRect.height() + 18;
		m_pGeometryWidget->setGeometry(-9, -9, w, h);
		m_bMaxCurWndState = true;
	}
}
void CQuiBaseWndBar::mouseMoveEvent(QMouseEvent* event)
{
	QWidget* mWidParent = m_pGeometryWidget;
	// ������ס������Ӧ�¼�
	if (mWidParent && m_bKeepPressed)
	{
		// ���������ƶ���������֮ǰ��λ�ü�������ƶ���λ�á�event->globalPos()- mPntStart��
		mWidParent->move(mWidParent->geometry().topLeft() + event->globalPos() - m_PntStart);
		// ���������Ļ�е�λ���滻Ϊ�µ�λ��
		m_PntStart = event->globalPos();
	}

	// ���õ�ǰ������ͷ����
	setCursor(Qt::ArrowCursor);
	//���������ڷ����ƶ��¼�

	//QWidget::mouseMoveEvent(event);

}
void CQuiBaseWndBar::mousePressEvent(QMouseEvent* event)
{
	// �����жϵ�ǰ������ʲôλ�� 
	// �����������¼�

	QRect rBarRect = geometry();
	QPoint objectPoint = this->mapTo(this, event->pos());
	if (!rBarRect.contains(objectPoint))
	{
		m_bKeepPressed = false;
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		// ��¼���״̬
		m_bKeepPressed = true;
		// ��¼�������Ļ�е�λ��
		m_PntStart = event->globalPos();
	}
	//���������ڷ����ƶ��¼�

	//QWidget::mousePressEvent(event);
	

}

void CQuiBaseWndBar::mouseReleaseEvent(QMouseEvent* event)
{
	// �������ͷ�
	if (event->button() == Qt::LeftButton)
	{
		// ��¼���״̬
		m_bKeepPressed = false;
	}
	//���������ڷ����ƶ��¼�
	
	//QWidget::mouseReleaseEvent(event);
	
}

void CQuiBaseWndBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	QWidget* mWidParent = m_pGeometryWidget;

	if (mWidParent)
	{
		m_bMaxWindow = !m_bMaxWindow;
		SetMaxWindow(m_bMaxWindow);
	}
	//���������ڷ����ƶ��¼�
	//QWidget::mouseDoubleClickEvent(event);
	
}
void CQuiBaseWndBar::SlotMenuClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());

	if (btn)
	{
		QMenu* pQMenu = m_MapMenu[btn->text()];
		if (pQMenu)
		{
			QPoint globalPos = this->mapToGlobal(btn->pos());
			globalPos = QPoint(globalPos.x(), globalPos.y()+ btn->height());
			pQMenu->exec(globalPos);
		}
	}
}

