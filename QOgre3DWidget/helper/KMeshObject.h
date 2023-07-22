/*
 * KMeshObject.h
 *
 *  Created on: Apr 9, 2023
 *      Author: khuongnv/0971388386
 */

#ifndef QOGRE3DWIDGET_HELPERS_KMESHOBJECT_H_
#define QOGRE3DWIDGET_HELPERS_KMESHOBJECT_H_
#include "KBaseObject.h"

namespace KEngine
{

class KMeshObject : public KBaseObject
{
public:
	KMeshObject(Ogre::SceneManager* sceneManager, const Ogre::String& meshName,
			const Ogre::String& nameObject = Ogre::String(), const Ogre::String& group = Ogre::RGN_AUTODETECT,
			Ogre::SceneNode* parentNode = nullptr);
	virtual ~KMeshObject();

public:
	virtual void setOffset(const Ogre::Vector3& offset) override;
	Ogre::Entity* entity() const {return m_entity;}
	Ogre::SceneNode* offsetNode() {return m_offsetNode;}
protected:
	Ogre::SceneNode* m_offsetNode;
	Ogre::Entity* m_entity;

};

} /* namespace KEngine */

#endif /* QOGRE3DWIDGET_HELPERS_KMESHOBJECT_H_ */
