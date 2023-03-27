#ifndef QOGRE3DWIDGET_H
#define QOGRE3DWIDGET_H
#include <QWidget>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreTrays.h>
#include <OgreOverlaySystem.h>
#include <OgreRenderWindow.h>
#include "KApplicationContext.h"
#include <memory.h>


class QOgre3DWidget : public QWidget
{
    Q_OBJECT
public:
    QOgre3DWidget(OgreBites::KApplicationContext* context, QWidget* parent = nullptr);

    void startRender();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void setupTrays();
    void testRender();
protected:
    OgreBites::KApplicationContext* m_context;
    Ogre::Root* m_ogreRoot;
    Ogre::RenderWindow* m_renderWindow;
    Ogre::SceneManager* m_sceneManager;
    Ogre::Camera* m_camera;
    std::shared_ptr<OgreBites::TrayManager> m_trayManager;
};

#endif // QOGRE3DWIDGET_H
