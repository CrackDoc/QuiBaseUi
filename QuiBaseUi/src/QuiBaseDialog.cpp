#include "QuiBaseDialog.h"
#include "ui_QuiBaseDialog.h"
#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>
#include <QBrush>
#include <QPen>
#include <qmath.h>
#include <QDesktopWidget>

#define SHADOW_WIDTH 9
#define BORDER_WIDTH 4

CQuiBaseDialog::CQuiBaseDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::QuiBaseDialogClass)
	, m_bStretch(false)
	, m_bShadow(true)
	, m_bLeftMousePress(false)
	, m_bCanDropWindow(false)
{
	ui->setupUi(this);

	//关闭windows边缘
	setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	setMouseTracking(true);
	//初始化界面
	Initialize();
}

bool CQuiBaseDialog::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui->titlebar  || watched == ui->WinCloseBtn || watched == ui->content)
	{
		setCursor(Qt::ArrowCursor);
	}
	if(watched == ui->label || watched == ui->label_2)
	{
		setCursor(Qt::ArrowCursor);
		return true;
	}
	
	return QWidget::eventFilter(watched, event);
}

CQuiBaseDialog::~CQuiBaseDialog()
{

}

void CQuiBaseDialog::SetDialogTitle(const QString& strTitle)
{
	ui->label->setText(strTitle);
	setWindowTitle(strTitle);
}

bool CQuiBaseDialog::SetDialogWidget(QWidget* widget)
{
	ui->content->layout()->addWidget(widget);

	return true;
}

bool CQuiBaseDialog::SetDialogTitleBar(QWidget* titleBar)
{
	ui->titlebar = titleBar;
	return true;
}

void CQuiBaseDialog::Initialize()
{
	ui->titlebar->installEventFilter(this);
	ui->WinCloseBtn->installEventFilter(this);

	ui->titlebar->setMouseTracking(true);
	ui->WinCloseBtn->setMouseTracking(true);
	ui->label->setMouseTracking(true);
	ui->label_2->setMouseTracking(true);
	ui->WinCloseBtn->setCursor(Qt::PointingHandCursor);

	connect(ui->WinCloseBtn, SIGNAL(clicked()), this, SLOT(SlotDialogClose()));
}

void CQuiBaseDialog::PaintShadow()
{
	//设置边框阴影
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 20, this->height() - 20);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));
	QColor color(0, 0, 0);
	for(int i=0; i<SHADOW_WIDTH; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundedRect(SHADOW_WIDTH-i, SHADOW_WIDTH-i, this->width()-(SHADOW_WIDTH-i)*2, this->height()-(SHADOW_WIDTH-i)*2, 1, 1);
		if (120 - qSqrt(i)*40*1.5 < 0)
		{
			color.setAlpha(0);
		}
		else
		{
			color.setAlpha(120 - qSqrt(i)*40*1.5);
		}
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void CQuiBaseDialog::paintEvent(QPaintEvent *e)
{
	if (m_bShadow)
	{
		PaintShadow();
	}
}

void CQuiBaseDialog::SetContentsMargins(const QMargins& margins)
{
	ui->verticalLayout->setContentsMargins(margins);
}

void CQuiBaseDialog::EnableShadow(bool bEnabled)
{
	m_bShadow = bEnabled;
}

void CQuiBaseDialog::EnableDialogStretch(bool bStretch)
{
	m_bStretch = bStretch;
}

void CQuiBaseDialog::SetQuiStyleSheet(const QString& strSytleSheet)
{
	m_strStyleSheet = strSytleSheet;
	this->setStyleSheet(m_strStyleSheet);
}

void CQuiBaseDialog::EnableTitleBar(bool bEnabled)
{
	if (!bEnabled)
	{
		ui->titlebar->hide();
	}
	else 
	{
		ui->content->show();
	}
}

void CQuiBaseDialog::EnableWidget(bool bEnabled)
{
	if (!bEnabled)
	{
		ui->content->hide();
	}
	else
	{
		ui->content->show();
	}
}

void CQuiBaseDialog::mouseMoveEvent(QMouseEvent *event)
{
	if (m_bStretch)
	{
		if (!m_bCanDropWindow)
		{
			if (!m_bLeftMousePress)
			{
				iDirection = GetBorderDirection(event);
				SetCursorStyle(iDirection);
			}
		}
		if (m_bCanDropWindow)
		{
			DropWindow(iDirection, event);
		}
		else
		{//拖动窗口
			if(m_bLeftMousePress)
			{
				//窗口拖动
				QPoint pos = mapToGlobal(event->pos());
				int x,y;
				x=pos.x() - m_MousePosOfWindow.x();
				y=pos.y() - m_MousePosOfWindow.y();

				this->move(x,y); 
			}
		}
	}
	else
	{
		if(m_bLeftMousePress)
		{
			QPoint pos = mapToGlobal(event->pos());
			move(pos-m_MousePosOfWindow);
		}
	}

	QWidget::mouseMoveEvent(event);
}

void CQuiBaseDialog::mousePressEvent(QMouseEvent *event)
{
	if (m_bStretch)
	{
		if (event->button() == Qt::LeftButton)
		{
			iDirection = GetBorderDirection(event);
			SetCursorStyle(iDirection);
			if (CENTER != iDirection)
				m_bCanDropWindow = true;


			//拖动窗口
			int mouse_x = event->x();
			int mouse_y = event->y();

			int x1 = 0;
			int y1 = 0;
			int x2 = width();
			int y2 = 28;
			if (mouse_x>=x1 && mouse_x<x2 && mouse_y>=y1 && mouse_y<y2)
			{
				m_MousePosOfWindow = event->pos();
				m_bLeftMousePress = true;
			}
		}
	}
	else
	{
		if (event->button() == Qt::LeftButton)
		{
			int mouse_x = event->x();
			int mouse_y = event->y();

			int x1 = ui->titlebar->x();
			int y1 = ui->titlebar->y();
			int x2 = x1 + ui->titlebar->width();
			int y2 = y1 + ui->titlebar->height();
			if (mouse_x>=x1 && mouse_x<x2 && mouse_y>=y1 && mouse_y<y2)
			{
				m_MousePosOfWindow = event->pos();
				m_bLeftMousePress = true;
			}
		}
	}

	QWidget::mousePressEvent(event);
}

void CQuiBaseDialog::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_bStretch)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bCanDropWindow = false;
			SetCursorStyle(CENTER);

			//拖动窗口
			m_bLeftMousePress = false;
		}
	}
	else
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bLeftMousePress = false;
		}
	}

	QWidget::mouseReleaseEvent(event);
}

/*
*函数名称：getBorderDirection
*函数功能：获取鼠标进入边框位置
*输入参数：event 鼠标事件
*返 回 值：无
*其它说明：无
*/
CQuiBaseDialog::Direction CQuiBaseDialog::GetBorderDirection(QMouseEvent *event)
{
	Direction result = CENTER;

	if (event->globalX() >= geometry().x() && event->globalX() < geometry().x() + width())
	{
		if (event->x() < BORDER_WIDTH + 5)
		{
			if (event->y() < BORDER_WIDTH + 5)
				result = LEFT_UP;
			else if (event->y() > height() - BORDER_WIDTH - 5)
				result = LEFT_DOWN;
			else
				result = LEFT;
		}
		else if (event->x() >= width() - BORDER_WIDTH - 5)
		{
			if (event->y() < BORDER_WIDTH + 5)
				result = RIGHT_UP;
			else if (event->y() > height() - BORDER_WIDTH - 5)
				result = RIGHT_DOWN;
			else
				result = RIGHT;
		}
		else
		{
			if (event->y() < BORDER_WIDTH + 5)
				result = UP;
			else if (event->y() > height() - BORDER_WIDTH - 5)
				result = DOWN;
		}
	}

	return result;
}

/*
*函数名称：SetCursorStyle
*函数功能：设置鼠标图标
*输入参数：dir 鼠标位置所在方向
*返 回 值：无
*其它说明：无
*/
void CQuiBaseDialog::SetCursorStyle(Direction dir)
{
	switch(dir)
	{
	case UP:
	case DOWN:
		setCursor(Qt::SizeVerCursor);
		break;
	case LEFT:
	case RIGHT:
		setCursor(Qt::SizeHorCursor);
		break;
	case LEFT_UP:
	case RIGHT_DOWN:
		setCursor(Qt::SizeFDiagCursor);
		break;
	case LEFT_DOWN:
	case RIGHT_UP:
		setCursor(Qt::SizeBDiagCursor);
		break;
	default:
		setCursor(Qt::ArrowCursor);
		break;
	}
}

void CQuiBaseDialog::DropWindow(Direction dir, QMouseEvent *event)
{
	if (dir == UP)
	{
		int y = event->globalY();
		if (geometry().bottomRight().y() - event->globalY() < minimumHeight())
			y = geometry().bottomRight().y() - minimumHeight();
		QRect rectIn(QPoint(geometry().x(), y), geometry().bottomRight());
		setGeometry(rectIn);
	}
	else if (dir == DOWN)
	{
		resize(width(), event->globalY() - geometry().y());
	}
	else if (dir == LEFT)
	{
		int x = event->globalX();
		if (geometry().bottomRight().x() - event->globalX() < minimumWidth())
			x = geometry().bottomRight().x() - minimumWidth();
		QRect rect(QPoint(x, geometry().y()), geometry().bottomRight());
		setGeometry(rect);
	}
	else if (dir == RIGHT)
	{
		resize(event->globalX() - geometry().x(), height());
	}
	else if (dir == LEFT_UP)
	{
		int x = event->globalX();
		if (geometry().bottomRight().x() - event->globalX() < minimumWidth())
			x = geometry().bottomRight().x() - minimumWidth();

		int y = event->globalY();
		if (geometry().bottomRight().y() - event->globalY() < minimumHeight())
			y = geometry().bottomRight().y() - minimumHeight();

		QRect rect(QPoint(x, y), geometry().bottomRight());
		setGeometry(rect);
	}
	else if (dir == LEFT_DOWN)
	{
		int x = event->globalX();
		if (geometry().bottomRight().x() - event->globalX() < minimumWidth())
			x = geometry().bottomRight().x() - minimumWidth();

		int y2 = event->globalY();
		if (y2 < geometry().y() + minimumHeight())
			y2 = geometry().y() + minimumHeight();

		QRect rect(QPoint(x, geometry().y()), QPoint(geometry().bottomRight().x(), y2));
		setGeometry(rect);
	}
	else if (dir == RIGHT_UP)
	{
		int x2 = event->globalX();
		if (x2 < geometry().x() + minimumWidth())
			x2 = geometry().x() + minimumWidth();

		int y = event->globalY();
		if (geometry().bottomRight().y() - event->globalY() < minimumHeight())
			y = geometry().bottomRight().y() - minimumHeight();

		QRect rect(QPoint(geometry().x(), y), QPoint(x2, geometry().bottomRight().y()));
		setGeometry(rect);
	}
	else if (dir == RIGHT_DOWN)
	{
		setCursor(Qt::SizeFDiagCursor);
		resize(event->globalX() - geometry().x() , event->globalY() - geometry().y());
	}
}

void CQuiBaseDialog::SlotDialogClose()
{
	emit SignalDialogClose();
	close();
}