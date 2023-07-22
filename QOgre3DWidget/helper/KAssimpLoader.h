#ifndef __KAssimpLoader_h__
#define __KAssimpLoader_h__

#include <OgreMesh.h>
#include <OgrePlugin.h>

struct aiScene;
struct aiNode;
struct aiBone;
struct aiMesh;
struct aiMaterial;
struct aiAnimation;

template <typename TReal> class aiMatrix4x4t;
typedef aiMatrix4x4t<float> aiMatrix4x4;

namespace Assimp
{
class Importer;
}

namespace KEngine
{
/** \defgroup AssimpCodec AssimpCodec
* %Codec for loading geometry using the [Open-Asset-Importer](https://github.com/assimp/assimp)
* @{
*/
class AssimpLoader
{
public:
    enum LoaderParams
    {
        // 3ds max exports the animation over a longer time frame than the animation actually plays for
        // this is a fix for that
        LP_CUT_ANIMATION_WHERE_NO_FURTHER_CHANGE = 1 << 0,

        // Quiet mode - don't output anything
        LP_QUIET_MODE = 1 << 1
    };

    struct Options
    {
        float animationSpeedModifier;
        int params;
        Ogre::String customAnimationName;
        float maxEdgeAngle;

        Options() : animationSpeedModifier(1), params(0), maxEdgeAngle(30) {}
    };

    AssimpLoader();
    virtual ~AssimpLoader();

    bool load(const Ogre::String& source, Ogre::Mesh* mesh, Ogre::SkeletonPtr& skeletonPtr,
              const Options& options = Options());

    bool load(const Ogre::DataStreamPtr& source, Ogre::Mesh* mesh, Ogre::SkeletonPtr& skeletonPtr,
              const Options& options = Options());

private:
    bool _load(const char* name, Assimp::Importer& importer, Ogre::Mesh* mesh, Ogre::SkeletonPtr& skeletonPtr,
               const Options& options);
    bool createSubMesh(const Ogre::String& name, int index, const aiNode* pNode, const aiMesh* mesh,
                       const aiMaterial* mat, Ogre::Mesh* mMesh, Ogre::AxisAlignedBox& mAAB);
    Ogre::MaterialPtr createMaterial(int index, const aiMaterial* mat);
    void grabNodeNamesFromNode(const aiScene* mScene, const aiNode* pNode);
    void grabBoneNamesFromNode(const aiScene* mScene, const aiNode* pNode);
    void computeNodesDerivedTransform(const aiScene* mScene, const aiNode* pNode,
                                      const aiMatrix4x4& accTransform);
    void createBonesFromNode(const aiScene* mScene, const aiNode* pNode);
    void createBoneHiearchy(const aiScene* mScene, const aiNode* pNode);
    void loadDataFromNode(const aiScene* mScene, const aiNode* pNode, Ogre::Mesh* mesh);
    void markAllChildNodesAsNeeded(const aiNode* pNode);
    void flagNodeAsNeeded(const char* name);
    bool isNodeNeeded(const char* name);
    void parseAnimation(const aiScene* mScene, int index, aiAnimation* anim);
    typedef std::map<Ogre::String, bool> boneMapType;
    boneMapType boneMap;
    // aiNode* mSkeletonRootNode;
    int mLoaderParams;

    Ogre::String mCustomAnimationName;

    typedef std::map<Ogre::String, const aiNode*> BoneNodeMap;
    BoneNodeMap mBoneNodesByName;

    typedef std::map<Ogre::String, const aiBone*> BoneMap;
    BoneMap mBonesByName;

    typedef std::map<Ogre::String, Ogre::Affine3> NodeTransformMap;
    NodeTransformMap mNodeDerivedTransformByName;

    Ogre::SkeletonPtr mSkeleton;

    static int msBoneCount;

    bool mQuietMode;
    Ogre::Real mTicksPerSecond;
    Ogre::Real mAnimationSpeedModifier;
};
} // namespace KEngine

#endif // __KAssimpLoader_h__
