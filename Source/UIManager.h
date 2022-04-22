#pragma once
#include "Viewport.h"
#include "Directional.h"
#include "Surface.h"
#include "Events.h"
#include "Types.h"

namespace ToolKit
{
	class TK_API UILayer
	{
	public:
		virtual void Init() = 0;
		virtual void Uninit() = 0;
		virtual void Update(float deltaTime, Camera* cam, Viewport* vp);
		virtual void PostUpdate();
		virtual void Render(Viewport* vp);
		Entity* FetchEntity(const String& entityName);
		Entity* GetLayer(const String& layerName);

	protected:
		void UpdateSurfaces(Viewport* vp);
		bool CheckMouseClick(Surface* surface, Event* e, Viewport* vp);
		bool CheckMouseOver(Surface* surface, Event* e, Viewport* vp);

	public:
		String m_layerName; //Should be the name of root entity of layout.
		ScenePtr m_layout = nullptr;
		Camera* m_cam = nullptr;
		Viewport* m_viewport = nullptr;
		Camera* m_lastCamEntity = nullptr;
	};

	class TK_API UIManager
	{
	public:
		UILayer* m_rootLayer;
		UILayerPtrArray m_childLayers;
		UILayerPtrArray m_allLayers;

		void SetRootLayer(UILayer* newRootLayer);
		void AddChildLayer(UILayer* newChildLayer);
		void RemoveChildLayer(String layerName);
		void RemoveAllChilds();

		void UpdateLayers(float deltaTime, Viewport* vp);
		void RenderLayers(Viewport* vp);
	};

}

