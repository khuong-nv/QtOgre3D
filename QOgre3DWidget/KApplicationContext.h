/*
 * KApplicationContext.h
 *
 *  Created on: Mar 25, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef KAPPLICATIONCONTEXT_H_
#define KAPPLICATIONCONTEXT_H_
#include <QObject>
#include <QWindow>
#include <QWidget>
#include <OgreRoot.h>
#include <OGRE/Bites/OgreApplicationContextBase.h>
namespace KEngine
{

class KApplicationContext : public QObject, public OgreBites::ApplicationContextBase
{
	Q_OBJECT
public:
	using ApplicationContextBase::setWindowGrab;
	using ApplicationContextBase::addInputListener;
	using ApplicationContextBase::removeInputListener;
public:
	explicit KApplicationContext(const Ogre::String& appName = "Ogre3D");
	virtual ~KApplicationContext();

	void setWindowGrab(OgreBites::NativeWindowType* win, bool grab);
	void addInputListener(OgreBites::NativeWindowType* win, OgreBites::InputListener* lis) override;
	void removeInputListener(OgreBites::NativeWindowType* win, OgreBites::InputListener* lis) override;

	void pollEvents() override;
	void shutdown() override;

    /**
     * signal that you want to use the Qt event loop
     *
     * aka QApplication::exec() instead of Root::startRendering.
     * In this case you may want to call startTimer on this QObject
     * which ensures that Root::renderOneFrame is called periodically.
     * @param enable
     */
    void useQtEventLoop(bool enable) { m_qtEventLoop = enable; }

    virtual OgreBites::NativeWindowPair createWindow(const Ogre::String& name, uint32_t w = 0, uint32_t h = 0,
                 Ogre::NameValuePairList miscParams = Ogre::NameValuePairList()) override;

    void loadNewResources(const Ogre::String& resourcePath);
public:
	void attachWidget(QWidget* widget);
	void setup() override;

private:
	void timerEvent(QTimerEvent *e) override;
	bool eventFilter(QObject *obj, QEvent *event) override;
	bool m_qtEventLoop;
	QWidget* m_parentWidget;
};

} /* namespace OgreBites */

#endif /* KAPPLICATIONCONTEXT_H_ */
