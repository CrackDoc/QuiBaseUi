#ifndef QuiDockTitleBar_h__
#define QuiDockTitleBar_h__
#include "QuiBaseUiExport.h"
#include <QtWidgets/QWidget>
#include <QString>
#include <QPainter>

class QHBoxLayout;
class QLabel;
class QPushButton;

class QuiBaseUi_EXPORT CQuiDockTitleBar : public QWidget
{
    Q_OBJECT

public:
	enum E_BAR_TYPE
	{
		e_DockBar,
		e_ToolBar
	};

public:
	CQuiDockTitleBar(E_BAR_TYPE type = e_DockBar,bool bFloatWnd = true, QString strTitle = "", QWidget* parent = Q_NULLPTR);

	~CQuiDockTitleBar();

	void Initialize(E_BAR_TYPE type);
		
	void SetBarTitle(const QString& strTitle);

	bool GetKeepMousePressed() { return m_bKeepPressed;}

	void SetFloatWindow(bool bFloat);

	bool GetFloatWindow() { return m_bFloatWindow; }

	E_BAR_TYPE GetBarType(){ return m_eBarType;}

	void SetBarSytle(QString style);

	/**
	 * @fn       EnabledMove
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/5 13:44
	 * @param    
	 * @return   
	*/
	void EnabledMove(bool bMove);
	/**
	 * @fn       AppendAction
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/5 13:33
	 * @param    
	 * @return   
	*/
	QPushButton* AppendAction(QIcon InIcon,QString text);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);

	void paintEvent(QPaintEvent* event);

private:
	// 鼠标上次移动开始时相对屏幕的位置
	QPoint m_PntStart;
	// 鼠标是否持续按下
	bool m_bKeepPressed;

signals:
	void SignalMiniWindow();
	void SignalMaxWindow();
	void SignalCloseWindow();

private:
	bool m_bFloatWindow;
	QHBoxLayout* m_HLayout;
	E_BAR_TYPE m_eBarType;
	QLabel* m_TitleLbl;
	bool m_bEnabledMove;
};
#endif // QuiDockTitleBar_h__
