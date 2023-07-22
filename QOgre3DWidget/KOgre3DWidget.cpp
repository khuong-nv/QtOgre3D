/*
 * KOgre3DWidget.cpp
 *
 *  Created on: Apr 1, 2023
 *      Author: khuongnv/0971388386
 */

#include "KOgre3DWidget.h"
#include <iostream>
#include "KApplicationContext.h"

namespace KEngine
{
using namespace std;

KOgre3DWidget::KOgre3DWidget(QWidget* parent)
: QWidget(parent)
, m_context(new KApplicationContext())
{    
    m_ogreRoot = m_context->getRoot();
    m_context->attachWidget(this);
    m_renderWindow = m_context->getRenderWindow();
    m_context->setup();

    // Create a new OGRE3D scene manager
    m_sceneManager = m_ogreRoot->createSceneManager();

    // Setup camera and viewport
    setupLightAndCamera();
    setupViewport();

    // Setup tray/overlay
    setupTrays();

    m_context->useQtEventLoop(true);
    connect(&m_timer, &QTimer::timeout, this, &KOgre3DWidget::render);
    m_timer.start(15);
}

KOgre3DWidget::~KOgre3DWidget()
{
	delete m_viewport;
	delete m_camera;
	delete m_renderWindow;
	delete m_ogreRoot;
	delete m_sceneManager;
	delete m_context;
	delete m_cameraMan;
	delete m_trayManager;
}

void KOgre3DWidget::setBackGroundColor(Ogre::ColourValue color)
{
    m_viewport->setBackgroundColour(color);
}

void KOgre3DWidget::setupLightAndCamera()
{
	// Create a new directional light
    Ogre::Light* light = m_sceneManager->createLight("MainLight");
    Ogre::SceneNode* lightNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    lightNode->attachObject(light);

    // Create a camera
    Ogre::SceneNode* camNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    m_camera = m_sceneManager->createCamera("myCam");
    m_camera->setNearClipDistance(5);
    m_camera->setFarClipDistance(1000000);
    m_camera->setAutoAspectRatio(true);
    camNode->attachObject(m_camera);

    // Create a camera man
    m_cameraMan = new KEngine::KCameraMan(camNode, m_camera, light);
    m_cameraMan->setYawPitchDist(Ogre::Degree(0), Ogre::Degree(-70), 250);
    m_context->addInputListener(m_cameraMan);

    light->setDirection(m_camera->getDerivedDirection());
}

void KOgre3DWidget::setupViewport()
{
    // Create a new OGRE3D viewport
    m_viewport = m_renderWindow->addViewport(m_camera);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
}

void KOgre3DWidget::startRender()
{
	m_context->getRoot()->startRendering();
}

void KOgre3DWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
    m_camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
    m_renderWindow->resize(width(), height());
}

void KOgre3DWidget::setupTrays()
{
    m_sceneManager->addRenderQueueListener(m_context->getOverlaySystem());
    m_trayManager = new OgreBites::TrayManager("TrayKhuongNV", m_renderWindow);
    m_trayManager->showFrameStats(OgreBites::TrayLocation::TL_BOTTOMLEFT);
    m_trayManager->hideCursor();
    m_context->addInputListener(m_trayManager);
}

void KOgre3DWidget::render()
{
	m_ogreRoot->renderOneFrame();
}

void KOgre3DWidget::setupTimeUpdateInterval(int ms)
{
	m_timer.setInterval(ms);
}

void KOgre3DWidget::showFrameStats(bool isShow,
		OgreBites::TrayLocation location)
{
	if(isShow)
	{
	    m_trayManager->showFrameStats(location);
	}
	else
	{
		m_trayManager->hideFrameStats();
	}
}

void KOgre3DWidget::setDefaultCameraDistanse(float near, float far)
{
	m_camera->setNearClipDistance(near);
	m_camera->setFarClipDistance(far);
}

void KOgre3DWidget::setDefaultCameraManPose(const Ogre::Degree &yaw,
		const Ogre::Degree &pitch, Ogre::Real dist)
{
    m_cameraMan->setYawPitchDist(yaw, pitch, dist);
}

void KOgre3DWidget::loadNewResource(const Ogre::String &resourcePath)
{
	m_context->loadNewResources(resourcePath);
}

}
