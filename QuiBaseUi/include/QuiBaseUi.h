#ifndef QuiBaseUi_h__
#define QuiBaseUi_h__

#include <QtWidgets/QWidget>
#include "QuiBaseUiExport.h"
class QuiBaseUi_EXPORT CQuiBaseUi : public QWidget
{
    Q_OBJECT

public:
    CQuiBaseUi(QWidget *parent = Q_NULLPTR);
	~CQuiBaseUi();

};
#endif // QuiBaseUi_h__
