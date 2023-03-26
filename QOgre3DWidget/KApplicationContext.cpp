/*
 * KApplicationContext.cpp
 *
 *  Created on: Mar 25, 2023
 *      Author: khuongnv/0971388386
 */

#include "KApplicationContext.h"
#include "OgreRenderWindow.h"
#include <OgreStringConverter.h>
#include <QGuiApplication>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QEvent>
#include <iostream>

using namespace std;
namespace OgreBites
{

KApplicationContext::KApplicationContext(const Ogre::String& appName)
: ApplicationContextBase(appName)
, m_qtEventLoop(false)
, m_parentWidget(nullptr)
{
	this->createRoot();
	if (!this->oneTimeConfig()) return;
	mRoot->initialise(false);
}

KApplicationContext::~KApplicationContext()
{
}

void KApplicationContext::attachWidget(QWidget *widget)
{
	assert(widget != nullptr);

	m_parentWidget = widget;

	// Create a new OGRE3D render window
	Ogre::NameValuePairList params;
	params["parentWindowHandle"] = Ogre::StringConverter::toString(widget->winId());
	params["externalWindowHandle"] = Ogre::StringConverter::toString(widget->winId());
	this->createWindow("OgreWidgetRenderWindow", widget->width(), widget->height(), params);
}

NativeWindowPair KApplicationContext::createWindow(const Ogre::String &name,
		uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams)
{
    if(mWindows.empty())
    {
        QGuiApplication::instance()->installEventFilter(this);
    }

	return ApplicationContextBase::createWindow(name, w, h, miscParams);
}

void KApplicationContext::setup()
{
	this->locateResources();
	this->initialiseRTShaderSystem();
	this->loadResources();

	// adds context as listener to process context-level (above the sample level) events
	mRoot->addFrameListener(this);
}

void KApplicationContext::setWindowGrab(NativeWindowType *win, bool grab)
{
	(void)win;
	grab ? ((QWindow*)win)->setCursor(Qt::BlankCursor) : ((QWindow*)win)->unsetCursor();
}

void KApplicationContext::addInputListener(NativeWindowType *win,
		InputListener *lis)
{
	(void)win;
	mInputListeners.insert(std::make_pair(m_parentWidget->winId(), lis));
}

void KApplicationContext::removeInputListener(NativeWindowType *win,
		InputListener *lis)
{
	(void)win;
	mInputListeners.erase(std::make_pair(m_parentWidget->winId(), lis));
}

void KApplicationContext::pollEvents()
{
	// assume events get polled by QApplication otherwise
	if(!m_qtEventLoop)
		QCoreApplication::instance()->processEvents();
}

void KApplicationContext::shutdown()
{
	ApplicationContextBase::shutdown();

	for(WindowList::iterator it = mWindows.begin(); it != mWindows.end(); ++it)
	{
		// FIXME: what if native is created externally? rather leak then risking double free
		//if(it->native)
		//    delete (QWidget*)it->native;
	}
	if(!mWindows.empty()) {
		QGuiApplication::instance()->removeEventFilter(this);
	}

	mWindows.clear();
}

void KApplicationContext::timerEvent(QTimerEvent *e)
{
	(void) e;
	getRoot()->renderOneFrame();
}

static Event convert(const QEvent* in)
{
	static QPoint lastMousePos;

	Event out;

	out.type = 0;

	switch(in->type())
	{
	case QEvent::KeyPress:
		out.type = KEYDOWN;
		OGRE_FALLTHROUGH;
	case QEvent::KeyRelease:
		// ignore auto repeated key-up events to match SDL
		if (!out.type && !static_cast<const QKeyEvent*>(in)->isAutoRepeat())
			out.type = KEYUP;
		{
			auto* key = static_cast<const QKeyEvent*>(in);
			out.key.repeat = key->isAutoRepeat();
			switch(key->key())
			{
			case Qt::Key_Escape:
				out.key.keysym.sym = SDLK_ESCAPE;
				break;
			case Qt::Key_Return:
				out.key.keysym.sym = SDLK_RETURN;
				break;
			default:
				out.key.keysym.sym = std::tolower(key->key());
				break;
			}
			// out.key.keysym.mod = key->modifiers();
		}
		break;
	case QEvent::MouseButtonRelease:
		out.type = MOUSEBUTTONUP;
		OGRE_FALLTHROUGH;
	case QEvent::MouseButtonPress:
		if(!out.type)
			out.type = MOUSEBUTTONDOWN;

		{
			auto* mouse = static_cast<const QMouseEvent*>(in);
			out.button.x = mouse->x();
			out.button.y = mouse->y();
			out.button.button = mouse->button();

			if(out.button.button == Qt::RightButton)
				out.button.button = BUTTON_RIGHT;
		}
		break;
	case QEvent::Wheel:
		out.type = MOUSEWHEEL;
		out.wheel.y = static_cast<const QWheelEvent*>(in)->angleDelta().y();
		out.wheel.y = out.wheel.y > 0 ? 1 : -1;
		break;
	case QEvent::MouseMove:
		out.type = MOUSEMOTION;
		{
			auto* mouse = static_cast<const QMouseEvent*>(in);
			out.motion.x = mouse->x();
			out.motion.y = mouse->y();
			out.motion.xrel = mouse->x() - lastMousePos.x();
			out.motion.yrel = mouse->y() - lastMousePos.y();

			lastMousePos = mouse->pos();

			//out.motion.windowID = in.motion.windowID;
		}
		break;
	case QEvent::TouchBegin:
		out.type = FINGERDOWN;
		OGRE_FALLTHROUGH;
	case QEvent::TouchEnd:
		if(!out.type)
			out.type = FINGERUP;
		OGRE_FALLTHROUGH;
	case QEvent::TouchUpdate:
		if(!out.type)
			out.type = FINGERMOTION;
		{
			auto* touch = static_cast<const QTouchEvent*>(in);
			out.tfinger.x = touch->touchPoints()[0].pos().x();
			out.tfinger.y = touch->touchPoints()[0].pos().y();
			//out.tfinger.dx = in.tfinger.dx;
			//out.tfinger.dy = in.tfinger.dy;
			out.tfinger.fingerId = touch->touchPoints()[0].id();
		}
		break;
	default:
		break;
	}
	return out;
}



bool KApplicationContext::eventFilter(QObject *obj, QEvent *event)
{
	QWidget* w = dynamic_cast<QWidget*>(obj);

	if(mWindows.empty() || !w || (w != m_parentWidget))
	{
		// not applicable
		return QObject::eventFilter(obj, event);
	}

	switch (event->type())
	{
	case QEvent::Quit:
		mRoot->queueEndRendering();
		break;
	case QEvent::UpdateRequest:
		for(auto & window : mWindows)
		{
			if(w->winId() != (m_parentWidget->winId()))
				continue;
			window.render->update();
		}
		break;
	case QEvent::Resize:
		for(auto & window : mWindows)
		{
			if(w->winId() != (m_parentWidget->winId()))
				continue;

			Ogre::RenderWindow* win = window.render;
			win->resize(w->width(), w->height());
			windowResized(win);
		}
		break;
	default:
		_fireInputEvent(convert(event), w->winId());
		break;
	}

	return QObject::eventFilter(obj, event);
}

} /* namespace OgreBites */
