/*
 * KOgre3DWidget.h
 *
 *  Created on: Apr 1, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef KOGRE3DWIDGET_H
#define KOGRE3DWIDGET_H
#include <QWidget>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreTrays.h>
#include <OgreRenderWindow.h>
#include <memory.h>
#include <OgreInput.h>
#include <QTimer>
#include "KCameraMan.h"
namespace KEngine
{

class KApplicationContext;
class KOgre3DWidget : public QWidget
{
    Q_OBJECT
public:
    KOgre3DWidget(QWidget* parent = nullptr);
    virtual ~KOgre3DWidget();
    virtual void setBackGroundColor(Ogre::ColourValue color);
    virtual void setupTimeUpdateInterval(int ms);
    void showFrameStats(bool isShow, OgreBites::TrayLocation location = OgreBites::TL_NONE);
    void setDefaultCameraDistanse(float near, float far);
    void setDefaultCameraManPose(const Ogre::Degree& yaw, const Ogre::Degree& pitch, Ogre::Real dist);
    void loadNewResource(const Ogre::String &resourcePath);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void setupTrays();
    void setupLightAndCamera();
    void setupViewport();
    void startRender();
protected slots:
	void render();
protected:
    KApplicationContext* m_context;
    Ogre::Root* m_ogreRoot;
    Ogre::RenderWindow* m_renderWindow;
    Ogre::SceneManager* m_sceneManager;
    Ogre::Viewport* m_viewport;
    Ogre::Camera* m_camera;
    KEngine::KCameraMan* m_cameraMan;
    OgreBites::TrayManager* m_trayManager;
    QTimer m_timer;
};
}

#endif // KOGRE3DWIDGET_H
