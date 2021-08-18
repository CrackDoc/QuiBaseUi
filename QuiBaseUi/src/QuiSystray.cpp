#include "QuiSystray.h"

#include <QPixmap>
#include <QMenu>
#include <QIcon>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>

CQuiSystray::CQuiSystray(QWidget*parent)
	: QWidget(parent)
	, m_pTrayIconMenu(new QMenu(parent))
{
	parentWidget = (QWidget*)parent;

	m_pTrayIconMenu->addAction(tr("Èí¼þ¹ºÂò(&B)"),this, SLOT(slotBuySites()));
	m_pTrayIconMenu->addAction(tr("Èí¼þ×¢²á(&R)"));
	m_pTrayIconMenu->addAction(tr("¹Ù·½ÍøÕ¾(&S)"), this, SLOT(slotOfficialSites()));
	m_pTrayIconMenu->addSeparator();
	m_pTrayIconMenu->addAction(tr("ÍË³ö³ÌÐò(&X)"), this, SIGNAL(closed()));


	m_TrayIcon = new QSystemTrayIcon(QApplication::desktop());

	m_TrayIcon->setIcon(QPixmap(":/resource/TrayIcon.png"));

	m_TrayIcon->setContextMenu(m_pTrayIconMenu);

	connect(m_TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));

	m_TrayIcon->show();
}

CQuiSystray::~CQuiSystray()
{
	delete m_TrayIcon;
	m_TrayIcon = NULL;
}
void CQuiSystray::slotActivated(QSystemTrayIcon::ActivationReason reason)
{
	parentWidget->activateWindow();
	parentWidget->show();
	//parentWidget->showMaximized();
	//switch (reason)
	//{
	//case QSystemTrayIcon::Trigger:
	//case QSystemTrayIcon::DoubleClick:
	//	parentWidget->show();
	//	break;
	//default:
	//	break;
	//}
}