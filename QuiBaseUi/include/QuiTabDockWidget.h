#ifndef QuiTabDockWidget_h__
#define QuiTabDockWidget_h__
#include "QuiBaseUiExport.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QMouseEvent>
#include "QuiDockTitleBar.h"
#include <QIcon>

class QuiBaseUi_EXPORT CQuiTabDockWidget :public QDockWidget
{
	Q_OBJECT
public:
	CQuiTabDockWidget(CQuiDockTitleBar::E_BAR_TYPE type = CQuiDockTitleBar::e_DockBar,QString strTitle = "",QWidget* parant = 0);
	~CQuiTabDockWidget();

	/**
	 * @fn       Initialize()
	 * @author   Crack
	 * @brief       
	 * @date     2021/7/27 15:03
	 * @param    
	 * @return   
	*/
	void Initialize();
public:
	/**
	 * @fn       SetProjectName
	 * @author   Crack
	 * @brief    设置工程名称
	 * @date     2021/7/27 14:41
	 * @param    
	 * @return   
	*/
	void SetDockTitle(const QString & strTitle);

	/**
	 * @fn       SetDockWidget
	 * @author   Crack
	 * @brief       
	 * @date     2021/7/27 14:45
	 * @param    
	 * @return   
	*/
	void SetDockWidget(QWidget* pDocWidget);

	/**
	 * @fn       SetTitleBarEnabled
	 * @author   JLC
	 * @brief       
	 * @date     2021/8/4 10:51
	 * @param    
	 * @return   
	*/
	void SetTitleBarEnabled(bool bEnable);
	/**
	 * @fn       SetWidgetEnabled
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/5 13:58
	 * @param    
	 * @return   
	*/

	void SetWidgetEnabled(bool bEnable);

	/**
	 * @fn       AppendAction
	 * @author   Crack
	 * @brief       
	 * @date     2021/8/5 13:55
	 * @param    
	 * @return   
	*/
	QPushButton* AppendAction(QIcon InIcon, QString text);

	void EnabledMove(bool bMove);

protected:
	void mouseMoveEvent(QMouseEvent* event);

	void mousePressEvent(QMouseEvent* event);
private:
	QString m_strTitleName;

	CQuiDockTitleBar* m_DocTitleBar;

	QWidget* m_EmptyWidget;
};

#endif // QuiTabDockWidget_h__
