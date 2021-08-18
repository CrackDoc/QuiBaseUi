#ifndef QuiSystray_h__
#define QuiSystray_h__
#include "QuiBaseUiExport.h"

#include <QObject>
#include <QSystemTrayIcon>
#include <QtWidgets/QWidget>
class QWidget;
class QMenu;
class QuiBaseUi_EXPORT CQuiSystray : public QWidget
{
	Q_OBJECT

public:
	CQuiSystray(QWidget*parent = 0);
	~CQuiSystray();

private:
	QSystemTrayIcon *m_TrayIcon;
	QWidget * parentWidget;
	QMenu* m_pTrayIconMenu;

signals:
	void closed();

private slots:
	void slotActivated(QSystemTrayIcon::ActivationReason reason);
};
#endif // QuiSystray_h__
