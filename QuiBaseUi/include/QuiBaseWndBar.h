#ifndef QuiBaseWndBar_h__
#define QuiBaseWndBar_h__

#include <QtWidgets/QWidget>
#include <QPainter>
#include "QuiBaseUiExport.h"
#include <QMouseEvent>

class QMenu;

namespace Ui {
	class QuiBaseWndBar;
}
class QuiBaseUi_EXPORT CQuiBaseWndBar : public QWidget
{
    Q_OBJECT

public:
    CQuiBaseWndBar(QWidget *parent = Q_NULLPTR);
	~CQuiBaseWndBar();
    /**
     * @fn       Initialize()
     * @author   Crack
     * @brief       
     * @date     2021/8/19 11:14
     * @param    
     * @return   
    */
    bool Initialize();

    /**
     * @fn       AppendWidget()
     * @author   Crack
     * @brief       
     * @date     2021/8/19 11:22
     * @param    
     * @return   
    */
    bool AppendWidget(QWidget *widget);
    /**
    * @fn       SetGeometryWidget
    * @author   Crack
    * @brief       
    * @date     2021/8/17 18:27
    * @param    
    * @return   
    */
    void SetGeometryWidget(QWidget* widget);
    /**
     * @fn       SetMaxWindow
     * @author   Crack
     * @brief       
     * @date     2021/8/19 14:02
     * @param    
     * @return   
    */
    void SetMaxWindow(bool bMaxWnd);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
public slots:
    void SlotMenuClicked();
private:
    Ui::QuiBaseWndBar *ui;
    QColor m_BackGroundColor;
	// 鼠标上次移动开始时相对屏幕的位置
	QPoint m_PntStart;
	// 鼠标是否持续按下
	bool m_bKeepPressed;

	QWidget* m_pGeometryWidget;
	bool m_bMaxWindow;
    bool m_bMaxCurWndState;
    QMap<QString, QMenu*> m_MapMenu;
    QRect m_FrontRect;
signals:
    void SignalShowMinWindow();
    void SignalShowMaxWindow();
    void SignalCloseWindow();
};
#endif // QuiBaseWndBar_h__
