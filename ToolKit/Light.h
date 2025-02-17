#pragma once

#include <string>

#include "Entity.h"
#include "Types.h"
#include "Primative.h"

namespace ToolKit
{

  enum class LightTypeEnum
  {
    LightBase,
    LightPoint,
    LightDirectional,
    LightSpot
  };

  class TK_API Light : public Entity
  {
   public:
    Light();
    virtual ~Light();

    EntityType GetType() const override;
    virtual LightTypeEnum GetLightType() const;
    void Serialize(XmlDocument* doc, XmlNode* parent) const override;
    void DeSerialize(XmlDocument* doc, XmlNode* parent) override;

    virtual void Init();

   public:
    TKDeclareParam(int, LightType);
    TKDeclareParam(Vec3, Color);
    TKDeclareParam(float, Intensity);

   protected:
    bool m_initialized = false;
  };

  class TK_API DirectionalLight : public Light
  {
   public:
     DirectionalLight();
     virtual ~DirectionalLight() {}

    LightTypeEnum GetLightType() const override;
  };

  class TK_API PointLight : public Light
  {
   public:
    PointLight();
    virtual ~PointLight() {}

    LightTypeEnum GetLightType() const override;

   public:
    TKDeclareParam(float, Radius);
  };

  class TK_API SpotLight : public Light
  {
   public:
    SpotLight();
    virtual ~SpotLight() {}

    LightTypeEnum GetLightType() const override;

   public:
    TKDeclareParam(float, Radius);
    TKDeclareParam(float, OuterAngle);
    TKDeclareParam(float, InnerAngle);
  };

}  // namespace ToolKit
