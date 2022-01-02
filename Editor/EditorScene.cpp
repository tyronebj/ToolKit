#include "stdafx.h"
#include "EditorScene.h"
#include "Util.h"
#include "GlobalDef.h"
#include "EditorViewport.h"
#include "DebugNew.h"

namespace ToolKit
{
  namespace Editor
  {

    const EntityId FixedLayerIds[2] = { g_3dLayerId, g_2dLayerId };
    const String FixedLayerNames[2] = { g_3dLayerStr, g_2dLayerStr };

    EditorScene::EditorScene()
    {
      m_newScene = true;
      m_fixedLayerNodes.reserve(2);
      for (int i = 0; i < 2; i++)
      {
        EntityNode* layerNode = new EntityNode(FixedLayerNames[i]);
        layerNode->m_id = FixedLayerIds[i];
        m_fixedLayerNodes.push_back(layerNode);
        AddEntity(layerNode);
      }
    }

    EditorScene::EditorScene(const String& file)
      : EditorScene()
    {
      m_file = file;
      m_newScene = false;
    }

    EditorScene::~EditorScene()
    {
    }

    void EditorScene::AddEntity(Entity* entity)
    {
      auto isFixedLayerFn = [](Entity* entity) -> bool
      {
        return entity->m_id == FixedLayerIds[0] || entity->m_id == FixedLayerIds[1];
      };

      // Make layer assignment.
      if 
      (
        entity->m_node->m_parent == nullptr &&
        !isFixedLayerFn(entity)
      )
      {
        int layerIndex = 0;
        if (entity->GetType() == EntityType::Entity_Surface)
        {
          layerIndex = 1;
          m_fixedLayerNodes[1]->m_node->AddChild(entity->m_node);
        }
        else if (entity->GetType() == EntityType::Entity_Node)
        {
          if (EditorViewport* vp = g_app->GetActiveViewport())
          {
            if (vp->GetType() == Window::Type::Viewport2d)
            {
              layerIndex = 1;
            }
            else
            {
              layerIndex = 0;
            }
          }
        }
        else
        {
          layerIndex = 0;
        }

        m_fixedLayerNodes[layerIndex]->m_node->AddChild(entity->m_node);
      }

      Scene::AddEntity(entity);
    }

    bool EditorScene::IsSelected(EntityId id) const
    {
      return std::find(m_selectedEntities.begin(), m_selectedEntities.end(), id) != m_selectedEntities.end();
    }

    void EditorScene::RemoveFromSelection(EntityId id)
    {
      auto nttIt = std::find(m_selectedEntities.begin(), m_selectedEntities.end(), id);
      if (nttIt != m_selectedEntities.end())
      {
        m_selectedEntities.erase(nttIt);
      }
    }

    void EditorScene::AddToSelection(EntityId id, bool additive)
    {
      assert(!IsSelected(id));
      if (!additive)
      {
        m_selectedEntities.clear();
      }
      m_selectedEntities.push_back(id);
    }

    void EditorScene::AddToSelection(const EntityIdArray& entities, bool additive)
    {
      EntityId currentId = NULL_ENTITY;
      if (entities.size() > 1)
      {
        for (const EntityId& id : entities)
        {
          if (id != NULL_ENTITY)
          {
            if (IsCurrentSelection(id))
            {
              currentId = id;
            }
          }
        }
      }

      // Start with a clear selection list.
      if (!additive)
      {
        ClearSelection();
      }

      for (const EntityId& id : entities)
      {
        if (id == NULL_ENTITY)
        {
          continue;
        }

        // Add to selection.
        if (!additive)
        {
          AddToSelection(id, true);
        }
        else // Add, make current or toggle selection.
        {
          if (IsSelected(id))
          {
            if (GetSelectedEntityCount() > 1)
            {
              if (entities.size() == 1)
              {
                if (IsCurrentSelection(id))
                {
                  RemoveFromSelection(id);
                }
                else
                {
                  MakeCurrentSelection(id, false);
                }
              }
            }
            else
            {
              RemoveFromSelection(id);
            }
          }
          else
          {
            AddToSelection(id, true);
          }
        }
      }

      MakeCurrentSelection(currentId, true);
    }

    void EditorScene::AddToSelection(const EntityRawPtrArray& entities, bool additive)
    {
      EntityIdArray ids;
      ToEntityIdArray(ids, entities);
      AddToSelection(ids, additive);
    }

    void EditorScene::ClearSelection()
    {
      m_selectedEntities.clear();
    }

    bool EditorScene::IsCurrentSelection(EntityId id) const
    {
      if (!m_selectedEntities.empty())
      {
        return m_selectedEntities.back() == id;
      }

      return false;
    }

    void EditorScene::MakeCurrentSelection(EntityId id, bool ifExist)
    {
      EntityIdArray::iterator itr = std::find(m_selectedEntities.begin(), m_selectedEntities.end(), id);
      if (itr != m_selectedEntities.end())
      {
        std::iter_swap(itr, m_selectedEntities.end() - 1);
      }
      else
      {
        if (!ifExist)
        {
          m_selectedEntities.push_back(id);
        }
      }
    }

    uint EditorScene::GetSelectedEntityCount() const
    {
      return (uint)m_selectedEntities.size();
    }

    Entity* EditorScene::GetCurrentSelection() const
    {
      if (!m_selectedEntities.empty())
      {
        return GetEntity(m_selectedEntities.back());
      }

      return nullptr;
    }

    bool EditorScene::IsMaterialInUse(const MaterialPtr& material) const
    {
      for (Entity* ntt : m_entitites)
      {
        if (ntt->IsDrawable())
        {
          if (static_cast<Drawable*> (ntt)->IsMaterialInUse(material))
          {
            return true;
          }
        }
      }

      return false;
    }

    bool EditorScene::IsMeshInUse(const MeshPtr& mesh) const
    {
      for (Entity* ntt : m_entitites)
      {
        if (ntt->IsDrawable())
        {
          if (static_cast<Drawable*> (ntt)->IsMeshInUse(mesh))
          {
            return true;
          }
        }
      }

      return false;
    }

    void EditorScene::Save(bool onlyIfDirty)
    {
      Scene::Save(onlyIfDirty);
      m_newScene = false;
    }

    void EditorScene::Load()
    {
      if (m_loaded)
      {
        return;
      }

      for (int i = 0; i < 2; i++)
      {
        RemoveEntity(FixedLayerIds[i]);
      }

      Scene::Load();

      for (int i = 0; i < 2; i++)
      {
        if (Entity* node = GetEntity(FixedLayerIds[i]))
        {
          SafeDel(m_fixedLayerNodes[i]);
          m_fixedLayerNodes[i] = node;
        }
        else
        {
          AddEntity(m_fixedLayerNodes[i]);
        }
      }
    }

    Entity* EditorScene::RemoveEntity(EntityId id)
    {
      Entity* removed = nullptr;
      if ((removed = Scene::RemoveEntity(id)))
      {
        RemoveFromSelection(removed->m_id);
      }

      return removed;
    }

    void EditorScene::Destroy(bool removeResources)
    {
      Scene::Destroy(removeResources);
      m_fixedLayerNodes = { nullptr, nullptr };
      m_selectedEntities.clear();
    }

    void EditorScene::GetSelectedEntities(EntityRawPtrArray& entities) const
    {
      for (EntityId id : m_selectedEntities)
      {
        Entity* e = GetEntity(id);
        assert(e);

        entities.push_back(e);
      }
    }

    void EditorScene::GetSelectedEntities(EntityIdArray& entities) const
    {
      entities = m_selectedEntities;
    }

    void EditorScene::SelectByTag(const String& tag)
    {
      AddToSelection(GetByTag(tag), false);
    }

    void EditorScene::CopyTo(Resource* other)
    {
      Scene::CopyTo(other);
      EditorScene* cpy = static_cast<EditorScene*> (other);
      cpy->m_newScene = true;
    }

  }
}
