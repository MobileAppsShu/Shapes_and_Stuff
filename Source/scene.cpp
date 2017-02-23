#include "scene.h"
#include "IwGx.h"
#include "input.h"

SceneManager* g_pSceneManager = 0;


//
//
// Scene class
//
//

Scene::Scene() : m_NameHash(0), m_IsActive(true), m_IsInputActive(false)
{
	m_IsVisible = false;
}

Scene::~Scene()
{
}

void Scene::SetName(const char* name)
{
	m_NameHash = IwHashString(name);
}

void Scene::Init()
{
}

void Scene::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	CNode::Update(deltaTime, alphaMul);
}

void Scene::Render()
{
	CNode::Render();
}

//
//
// SceneManager class
//
//
SceneManager::SceneManager() : m_Current(0), m_Next(0)
{
}

SceneManager::~SceneManager()
{
	for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
		delete *it;
}

void SceneManager::Add(Scene* scene)
{
	m_Scenes.push_back(scene);
	scene->SetManager(this);
}

void SceneManager::Remove(Scene* scene)
{
	m_Scenes.remove(scene);
}

Scene* SceneManager::Find(const char* name)
{
	unsigned int name_hash = IwHashString(name);
	for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	{
		if ((*it)->GetNameHash() == name_hash)
			return *it;
	}

	return 0;
}

void SceneManager::Update(float deltaTime)
{
	for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
		(*it)->Update(deltaTime);
}

void SceneManager::Render()
{
	for (std::list<Scene*>::iterator it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
		(*it)->Render();
}

void SceneManager::SwitchTo(Scene* scene)
{
	m_Next = scene;
	if (m_Current == 0)
	{
		// Activate and make visible the new scene
		m_Current = m_Next;
		m_Current->SetActive(true);
		m_Current->m_IsVisible = true;
		m_Current->SetInputActive(true);
		m_Next = 0;
	}
	else
	{
		// Activate and make visible the new scene
		m_Next->SetActive(true);
		m_Next->SetInputActive(true);
		m_Next->SetActive(true);
		m_Next->m_IsVisible = true;
		// Deactivate and hide the old scene
		m_Current->SetInputActive(false);
		m_Current->SetActive(false);
		m_Current->m_IsVisible = false;
		m_Current = m_Next;
		m_Next = 0;
	}
}