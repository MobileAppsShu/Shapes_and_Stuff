#if !defined(__SCENE_H__)
#define __SCENE_H__

#include <list>
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class SceneManager;

class Scene : public CNode
{
protected:
	unsigned int        m_NameHash;                     // Hash string representation of scene name
	bool                m_IsActive;                     // Active state
	bool                m_IsInputActive;                // Input active state
	SceneManager*       m_Manager;                      // Scene manager

public:
	bool                IsActive() const                    { return m_IsActive; }
	void                SetActive(bool active)              { m_IsActive = active; }
	void                SetName(const char* name);
	unsigned int        GetNameHash() const                 { return m_NameHash; }
	void                SetManager(SceneManager* manager)   { m_Manager = manager; }
	void                SetInputActive(bool active)         { m_IsInputActive = active; }

public:
	Scene();
	virtual ~Scene();

	virtual void    Init();
	virtual void    Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	virtual void    Render();
};

class SceneManager
{
protected:
	Scene*              m_Current;              // Currently active scene
	Scene*              m_Next;                 // Next scene (scene that is being switched to)
	std::list<Scene*>   m_Scenes;               // Scenes list
public:
	Scene*  GetCurrent()                { return m_Current; }

public:
	SceneManager();
	~SceneManager();

	void    SwitchTo(Scene* scene);
	void    Update(float deltaTime = 0.0f);
	void    Render();
	void    Add(Scene* scene);
	void    Remove(Scene* scene);
	Scene*  Find(const char* name);
};

extern SceneManager* g_pSceneManager;


#endif  // __SCENE_H__