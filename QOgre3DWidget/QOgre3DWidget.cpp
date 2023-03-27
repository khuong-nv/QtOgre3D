#include "QOgre3DWidget.h"
#include <OgreEntity.h>
#include <QTimer>
#include <iostream>
#include <OgreResourceGroupManager.h>
#include <QWidget>
#include <OgreMeshManager.h>
#include "OgreCameraMan.h"

using namespace std;
QOgre3DWidget::QOgre3DWidget(OgreBites::KApplicationContext* context, QWidget* parent)
    : QWidget(parent), m_context(context)
{    
    m_ogreRoot = context->getRoot();
    context->attachWidget(this);
    m_renderWindow = context->getRenderWindow();
    context->setup();

    // Create a new OGRE3D scene manager
    m_sceneManager = m_ogreRoot->createSceneManager();

    // without light we would just get a black screen
    Ogre::Light* light = m_sceneManager->createLight("MainLight");
    Ogre::SceneNode* lightNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 80, 50);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    m_camera = m_sceneManager->createCamera("myCam");
    m_camera->setNearClipDistance(5); // specific to this sample
    m_camera->setAutoAspectRatio(true);
    camNode->attachObject(m_camera);
    camNode->setPosition(100, 0, 500);

    OgreBites::CameraMan* cameraMan = new OgreBites::CameraMan(camNode);
    cameraMan->setStyle(OgreBites::CS_ORBIT);
    cameraMan->setYawPitchDist(Ogre::Degree(0), Ogre::Degree(30), 250);
    m_context->addInputListener(cameraMan);


    // Create a new OGRE3D viewport
    Ogre::Viewport* viewport = m_renderWindow->addViewport(m_camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    // Setup tray/overlay
    setupTrays();

    // test render
    testRender();

    std::thread(&QOgre3DWidget::startRender, this).detach();
}

void QOgre3DWidget::testRender()
{
    // finally something to render
    Ogre::Entity* ent = m_sceneManager->createEntity("ogrehead.mesh");
    Ogre::SceneNode* node = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

void QOgre3DWidget::startRender()
{
	m_context->getRoot()->startRendering();
}

void QOgre3DWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
    m_camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
    m_renderWindow->resize(width(), height());
    m_renderWindow->windowMovedOrResized();
}

void QOgre3DWidget::setupTrays()
{
    m_sceneManager->addRenderQueueListener(m_context->getOverlaySystem());
    m_trayManager = std::make_shared<OgreBites::TrayManager>("InterfaceName", m_renderWindow);
    m_trayManager->showFrameStats(OgreBites::TrayLocation::TL_BOTTOMLEFT);
    m_trayManager->showLogo(OgreBites::TrayLocation::TL_BOTTOMRIGHT);
    m_trayManager->hideCursor();
    m_context->addInputListener(m_trayManager.get());
}
