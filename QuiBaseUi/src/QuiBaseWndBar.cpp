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
		//const QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
		const QRect screenRect = desktopWidget->availableGeometry();  //屏幕区域
		int w = screenRect.width() + 18;
		int h = screenRect.height() + 18;
		m_pGeometryWidget->setGeometry(-9, -9, w, h);
		m_bMaxCurWndState = true;
	}
}
void CQuiBaseWndBar::mouseMoveEvent(QMouseEvent* event)
{
	QWidget* mWidParent = m_pGeometryWidget;
	// 持续按住才做对应事件
	if (mWidParent && m_bKeepPressed)
	{
		// 将父窗体移动到父窗体之前的位置加上鼠标移动的位置【event->globalPos()- mPntStart】
		mWidParent->move(mWidParent->geometry().topLeft() + event->globalPos() - m_PntStart);
		// 将鼠标在屏幕中的位置替换为新的位置
		m_PntStart = event->globalPos();
	}

	// 设置当前的鼠标箭头符号
	setCursor(Qt::ArrowCursor);
	//向其他窗口发送移动事件

	//QWidget::mouseMoveEvent(event);

}
void CQuiBaseWndBar::mousePressEvent(QMouseEvent* event)
{
	// 首先判断当前鼠标点在什么位置 
	// 鼠标左键按下事件

	QRect rBarRect = geometry();
	QPoint objectPoint = this->mapTo(this, event->pos());
	if (!rBarRect.contains(objectPoint))
	{
		m_bKeepPressed = false;
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		// 记录鼠标状态
		m_bKeepPressed = true;
		// 记录鼠标在屏幕中的位置
		m_PntStart = event->globalPos();
	}
	//向其他窗口发送移动事件

	//QWidget::mousePressEvent(event);
	

}

void CQuiBaseWndBar::mouseReleaseEvent(QMouseEvent* event)
{
	// 鼠标左键释放
	if (event->button() == Qt::LeftButton)
	{
		// 记录鼠标状态
		m_bKeepPressed = false;
	}
	//向其他窗口发送移动事件
	
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
	//向其他窗口发送移动事件
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

