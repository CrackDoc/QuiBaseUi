#include "QuiTabDockWidget.h"
#include "QuiDockTitleBar.h"
#include <QLayout>

CQuiTabDockWidget::CQuiTabDockWidget(CQuiDockTitleBar::E_BAR_TYPE type,QString strTitle,QWidget* parant)
	:QDockWidget(parant)
	, m_strTitleName(strTitle)
	, m_DocTitleBar(new CQuiDockTitleBar(type,false,strTitle,this))
	, m_EmptyWidget(new QWidget(this))
{
	setMouseTracking(true);
	Initialize();
}
CQuiTabDockWidget::~CQuiTabDockWidget()
{
	if (m_EmptyWidget != nullptr)
	{
		delete m_EmptyWidget;
		m_EmptyWidget = nullptr;
	}

	if (m_DocTitleBar != nullptr)
	{
		delete m_DocTitleBar;
		m_DocTitleBar = nullptr;
	}

}

void CQuiTabDockWidget::Initialize()
{
	this->setTitleBarWidget(m_DocTitleBar);
}

void CQuiTabDockWidget::SetDockTitle(const QString& strTitle)
{
	this->setWindowTitle(strTitle);

	m_DocTitleBar->SetBarTitle(strTitle);
}
void CQuiTabDockWidget::SetDockWidget(QWidget* pDocWidget)
{
	this->setWidget(pDocWidget);
}

void CQuiTabDockWidget::SetTitleBarEnabled(bool bEnable)
{
	this->setTitleBarWidget(m_EmptyWidget);
}

void CQuiTabDockWidget::SetWidgetEnabled(bool bEnable)
{
	m_EmptyWidget->setFixedHeight(0);
	this->setWidget(m_EmptyWidget);
}

QPushButton* CQuiTabDockWidget::AppendAction(QIcon InIcon, QString text)
{
	return m_DocTitleBar->AppendAction(InIcon,text);
}

void CQuiTabDockWidget::EnabledMove(bool bMove)
{
	m_DocTitleBar->EnabledMove(bMove);
}

void CQuiTabDockWidget::mouseMoveEvent(QMouseEvent* event)
{
	setCursor(Qt::ArrowCursor);
	QDockWidget::mouseMoveEvent(event);
}

void CQuiTabDockWidget::mousePressEvent(QMouseEvent* event)
{
	// 这个信号重子窗口过来的信号,不继续向上传递,如果外面的父窗口需要这个
	// 信号就继续向上发送信号
	if (m_DocTitleBar->GetKeepMousePressed() && !this->isFloating())
	{
		this->setFloating(true);
	}
}
