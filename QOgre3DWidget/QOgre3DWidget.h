#ifndef QOGRE3DWIDGET_H
#define QOGRE3DWIDGET_H
#include <QWidget>
#include <QResizeEvent>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include "KApplicationContext.h"

class QOgre3DWidget : public QWidget
{
    Q_OBJECT
public:
    QOgre3DWidget(OgreBites::KApplicationContext* context, QWidget* parent = nullptr);

    void render();
    void testLoadModel();
    void startRender();
protected:
    void resizeEvent(QResizeEvent *event) override;
protected:
    OgreBites::KApplicationContext* m_context;
    Ogre::Root* m_ogreRoot;
    Ogre::RenderWindow* m_renderWindow;
    Ogre::SceneManager* m_sceneManager;
    Ogre::Camera* m_camera;
    QTimer* m_timer;

};

#endif // QOGRE3DWIDGET_H
