/*
 * MyTestWidget.h
 *
 *  Created on: May 6, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef MYTESTWIDGET_H_
#define MYTESTWIDGET_H_
#include "KOgre3DWidget.h"

namespace KEngine
{

class MyTestWidget : public KOgre3DWidget
{
public:
	MyTestWidget(QWidget* parent = nullptr);
	virtual ~MyTestWidget();

protected:
    void createGrid2d();
    void testRender();
    void setupGizmoViewport();

};

} /* namespace KEngine */

#endif /* MYTESTWIDGET_H_ */
