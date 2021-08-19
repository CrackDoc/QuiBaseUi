#include "QuiDockTitleBar.h"
#include <QEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>

QString QSTR_BAR_STYLE = "QPushButton{"
"border: 0px solid #9EA0A4;"
"background - color: #8B8B8B;"
"border - radius: 0px;"
"}"
"QPushButton:pressed{"
"padding - right:0px;"
"padding - bottom:0px;"
"padding - top:0px;"
"padding - left:0px;"
"border: 0px solid #5388f3;"
"	background:#F0F0F0;"
"}"
"QPushButton:!hover{"
"border: 0px solid #5388f3;"
"background:#8B8B8B;"
"}"
"QPushButton:hover{"
"border: 0px solid #5388f3;"
"background:#F0F0F0;"
"}"
"QLabel"
"{"
"color: rgb(255, 255, 255);"
"}";
CQuiDockTitleBar::CQuiDockTitleBar(E_BAR_TYPE type,bool bFloatWnd,QString strTitle,QWidget *parent)
    : QWidget(parent)
	, m_bKeepPressed(false)
	, m_TitleLbl(new QLabel(strTitle,this))
	, m_bFloatWindow(bFloatWnd)
	, m_eBarType(type)
	, m_bEnabledMove(true)
{
	m_HLayout = new QHBoxLayout(this);

	m_HLayout->setContentsMargins(2, 1, 1, 1);

	m_HLayout->setSpacing(1);

	Initialize(m_eBarType);

}
CQuiDockTitleBar::~CQuiDockTitleBar()
{
	
}
void CQuiDockTitleBar::Initialize(E_BAR_TYPE type)
{
	int size = m_HLayout->count();
	for (int i = 0; i < size; ++i)
	{
		QLayoutItem* item = m_HLayout->itemAt(i);
		m_HLayout->removeItem(item);
		if (item != nullptr)
		{
			delete item;
			item = nullptr;
		}
	}
	m_HLayout->addWidget(m_TitleLbl);
	QSpacerItem* SpaceItem = new QSpacerItem(40, 24, QSizePolicy::Expanding);
	m_HLayout->addSpacerItem(SpaceItem);
	if (type == e_DockBar)
	{
		QPushButton* MinBtn = new QPushButton(this);
		MinBtn->setFlat(true);
		MinBtn->resize(QSize(20, 20));
		QPushButton* MaxBtn = new QPushButton(this);
		MaxBtn->setFlat(true);
		MaxBtn->resize(QSize(20, 20));
		QPushButton* ClosBtn = new QPushButton(this);
		ClosBtn->setFlat(true);
		ClosBtn->resize(QSize(20, 20));

		MinBtn->setIcon(QPixmap(":/resource/win_min.png"));
		MaxBtn->setIcon(QPixmap(":/resource/win_remax.png"));
		ClosBtn->setIcon(QPixmap(":/resource/win_close.png"));

		connect(MinBtn, SIGNAL(clicked()), this, SIGNAL(SignalMiniWindow()));

		connect(ClosBtn, SIGNAL(clicked()), this, SIGNAL(SignalMaxWindow()));

		connect(MaxBtn, SIGNAL(clicked()), this, SIGNAL(SignalCloseWindow()));

		m_HLayout->addWidget(MinBtn);
		m_HLayout->addWidget(MaxBtn);
		m_HLayout->addWidget(ClosBtn);

		
	}
	SetBarSytle(QSTR_BAR_STYLE);
}

void CQuiDockTitleBar::SetBarTitle(const QString& strTitle)
{
	m_TitleLbl->setText(strTitle);
}

void CQuiDockTitleBar::SetFloatWindow(bool bFloat)
{
	m_bFloatWindow = bFloat;
}
void CQuiDockTitleBar::SetBarSytle(QString style)
{
	this->setStyleSheet(style);
}

void CQuiDockTitleBar::EnabledMove(bool bMove)
{
	m_bEnabledMove = bMove;
}

QPushButton* CQuiDockTitleBar::AppendAction(QIcon InIcon,QString text)
{
	QIcon icon = InIcon;
	QPushButton* btn = new QPushButton("", this);
	btn->setIcon(icon);
	btn->setIconSize(QSize(20, 20));
	btn->setFlat(true);
	btn->resize(QSize(20, 20));
	btn->setToolTip(text);

	int size = m_HLayout->count();

	m_HLayout->insertWidget(size - 1, btn);

	return btn;
}

void CQuiDockTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	// 持续按住才做对应事件
	if (m_bKeepPressed)
	{
		QWidget* mWidParent = qobject_cast<QWidget*>(parentWidget());
		if (mWidParent)
		{
			mWidParent->move(mWidParent->geometry().topLeft() + event->globalPos() - m_PntStart);
			// 将鼠标在屏幕中的位置替换为新的位置
			m_PntStart = event->globalPos();
		}
	}
	QWidget::mouseMoveEvent(event);
}

void CQuiDockTitleBar::mousePressEvent(QMouseEvent* event)
{
	if (!m_bEnabledMove)
	{
		return;
	}
	// 鼠标左键按下事件
	if (event->button() == Qt::LeftButton)
	{
		// 记录鼠标状态
		m_bKeepPressed = true;
		m_bFloatWindow = true;
		// 记录鼠标在屏幕中的位置
		m_PntStart = event->globalPos();
	}
	QWidget::mousePressEvent(event);
}

void CQuiDockTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	// 鼠标左键释放
	if (event->button() == Qt::LeftButton)
	{
		// 记录鼠标状态
		m_bKeepPressed = false;
	}
	QWidget::mouseReleaseEvent(event);
}

void CQuiDockTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QWidget* mWidParent = qobject_cast<QWidget*>(parentWidget());
		if (mWidParent)
		{
			bool bFloat = m_bFloatWindow;
			if (bFloat)
			{
				if (mWidParent->isMaximized())
				{
					mWidParent->showNormal();
				}
				else
				{
					mWidParent->showMaximized();
				}
			}
		}
	}
	QWidget::mouseDoubleClickEvent(event);
}
void CQuiDockTitleBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter p(this);

	p.setPen(Qt::NoPen);

	p.setBrush(QColor(139, 139, 139));

	p.drawRect(rect());
}
