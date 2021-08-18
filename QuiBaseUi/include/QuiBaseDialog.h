#ifndef QuiBaseDialog_h__
#define QuiBaseDialog_h__

#include <QDialog>
#include <QPoint>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "QuiBaseUiExport.h"
namespace Ui 
{
	class QuiBaseDialogClass;
}
class QuiBaseUi_EXPORT CQuiBaseDialog : public QDialog
{
	Q_OBJECT

public:
	CQuiBaseDialog(QWidget *parent = 0);
	~CQuiBaseDialog();

	/**
	 * @fn       SetDialogTitle
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:08
	 * @param    
	 * @return   
	*/
	void SetDialogTitle(const QString& strTitle);

	/**
	 * @fn       SetDialogWidget(QWidget *widget)
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:12
	 * @param    
	 * @return   
	*/
	bool SetDialogWidget(QWidget* widget);

	/**
	 * @fn       SetDialogTitleBar(QWidget* titleBar)
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:15
	 * @param    
	 * @return   
	*/
	bool SetDialogTitleBar(QWidget* titleBar);

	/**
	 * @fn       Initialize
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:17
	 * @param    
	 * @return   
	*/
	void Initialize();

	/**
	 * @fn       SetContentsMargins
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:21
	 * @param    
	 * @return   
	*/
	void SetContentsMargins(const QMargins& margins);

	/**
	 * @fn       EnableShadow(bool bEnabled)
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:22
	 * @param    
	 * @return   
	*/
	void EnableShadow(bool bEnabled);
	
	/**
	 * @fn       EnableDialogStretch
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:28
	 * @param    
	 * @return   
	*/
	void EnableDialogStretch(bool bStretch);

	/**
	 * @fn       SetQuiStyleSheet
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 10:45
	 * @param    
	 * @return   
	*/
	void SetQuiStyleSheet(const QString& strSytleSheet);

	/**
	 * @fn       EnableTitleBar
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 13:29
	 * @param    
	 * @return   
	*/
	void EnableTitleBar(bool bEnabled);

	/**
	 * @fn       EnableWidget
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/17 13:30
	 * @param    
	 * @return   
	*/
	void EnableWidget(bool bEnabled);

private:
	Ui::QuiBaseDialogClass *ui;
	// 是否可以拉伸
	bool m_bStretch;
	// 阴影
	bool m_bShadow;
	// 鼠标按下
	bool m_bLeftMousePress;
	// 鼠标拖动点
	QPoint m_MousePosOfWindow;
	bool  m_bCanDropWindow;
	// 窗口样式
	QString m_strStyleSheet;
	// 鼠标拉伸方向
	enum Direction
	{
		CENTER = 0,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		LEFT_UP,
		RIGHT_UP,
		LEFT_DOWN,
		RIGHT_DOWN
	}iDirection;
	// 获取鼠标窗口阴影
	CQuiBaseDialog::Direction GetBorderDirection(QMouseEvent * mouseEvent);
	// 设置鼠标样式
	void SetCursorStyle(Direction dir);
	// 拖动窗口
	void DropWindow(Direction, QMouseEvent *mouseEvent);
	// 绘制窗口阴影
	void PaintShadow();
protected:
	void paintEvent(QPaintEvent * event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent (QMouseEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
private slots:
	void SlotDialogClose();
signals:
	void SignalDialogClose();
};
#endif // QuiBaseDialog_h__