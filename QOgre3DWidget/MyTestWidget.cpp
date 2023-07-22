/*
 * MyTestWidget.cpp
 *
 *  Created on: May 6, 2023
 *      Author: khuongnv/0971388386
 */

#include "MyTestWidget.h"
#include "helper/KGridObject.h"
#include "helper/KMeshObject.h"

namespace KEngine
{

MyTestWidget::MyTestWidget(QWidget* parent)
: KOgre3DWidget(parent)
{
	// Load my resource
	this->loadNewResource("./resources/my_resources.cfg");

	setupGizmoViewport();

	// Setup gizmo manipulator
	this->showFrameStats(true, OgreBites::TL_BOTTOMRIGHT);
	this->setDefaultCameraDistanse(10,  2000000);
	this->setDefaultCameraManPose(Ogre::Degree(0), Ogre::Degree(-70), 250);
	createGrid2d();

	testRender();
}

MyTestWidget::~MyTestWidget()
{
}

void MyTestWidget::createGrid2d()
{
	new KEngine::KGridObject(
			m_sceneManager,
			Ogre::ColourValue(90.0/255, 90.0/255, 90.0/255),
			Ogre::ColourValue(255/255.0, 54/255.0, 83/255.0),
			Ogre::ColourValue(117/255.0, 177/255.0, 22/255.0),
			20, 20, 10, 10);
}

void MyTestWidget::testRender()
{
	Ogre::SceneNode* parentNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    new KEngine::KMeshObject(m_sceneManager, "ogrehead.mesh", Ogre::String(), "MyGroup", parentNode);
}

void MyTestWidget::setupGizmoViewport()
{

}

} /* namespace KEngine */
