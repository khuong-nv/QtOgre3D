/*
 * KMeshObject.cpp
 *
 *  Created on: Apr 9, 2023
 *      Author: khuongnv/0971388386
 */

#include "KMeshObject.h"
#include <OgreEntity.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>
#include <OgreMesh.h>
#include <OgrePolygon.h>
#include <OgreTechnique.h>
#include <iostream>
#include <filesystem>
#include <filesystem>
#include "KAssimpLoader.h"
#include <OgreMeshManager.h>
using namespace std;
namespace KEngine
{

KMeshObject::KMeshObject(Ogre::SceneManager* sceneManager,
		const Ogre::String& meshName,
		const Ogre::String& nameObject,
		const Ogre::String& group,
		Ogre::SceneNode* parentNode)
: KBaseObject(sceneManager, parentNode)
{
	std::string name = "";
	if(nameObject == "")
	{
		// Generate unique shape name
		name = generateShapeName("Mesh");
	}
	else name = nameObject;

	if(std::filesystem::path(meshName.c_str()).extension() == ".mesh")
	{
		m_entity = sceneManager->createEntity(name, meshName, group);
	}
	else
	{
		// Build mesh pointer from file with assimp codec
		Ogre::MeshPtr newMesh = Ogre::MeshManager::getSingleton().createManual(name, group);
		Ogre::SkeletonPtr skeletonPtr;
		AssimpLoader assimpLoader;
		assimpLoader.load(meshName, newMesh.get(), skeletonPtr);
		m_entity = sceneManager->createEntity(Ogre::MeshPtr(newMesh));
		cout << "Create mesh done from: " << meshName << endl;
	}

	m_offsetNode = m_sceneNode->createChildSceneNode();

	if (m_entity)
		m_offsetNode->attachObject(m_entity);
}

KMeshObject::~KMeshObject()
{
	if (m_entity)
		m_sceneManager->destroyEntity(m_entity);
}

void KMeshObject::setOffset(const Ogre::Vector3 &offset)
{
	m_offsetNode->setPosition(offset);
}

} /* namespace KEngine */
