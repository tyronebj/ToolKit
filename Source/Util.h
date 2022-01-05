#pragma once

#include "MathUtil.h"
#include "Types.h"

#include <assert.h>
#include <string.h>
#include <vector>

namespace ToolKit
{

  template<typename T>
  void ReadVec(XmlNode* node, T& val);
  template<typename T>
  void WriteVec(XmlNode* node, XmlDocument* doc, const T& val);
  TK_API void WriteAttr(XmlNode* node, XmlDocument* doc, const String& name, const String& val);

  TK_API void ReadAttr(XmlNode* node, const String& name, bool& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, float& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, int& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, uint& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, Byte& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, UByte& val);
  TK_API void ReadAttr(XmlNode* node, const String& name, String& val);
  TK_API XmlNode* Query(XmlDocument* doc, const StringArray& path);

  TK_API void WriteMaterial(XmlNode* parent, XmlDocument* doc, const String& file);
  TK_API MaterialPtr ReadMaterial(XmlNode* parent);

  // File path operations.
  TK_API bool CheckFile(const String& path);
  TK_API String CreateCopyFileFullPath(const String& fullPath);
  TK_API void DecomposePath(const String& fullPath, String* path, String* name, String* ext);
  TK_API void NormalizePath(String& path);
  TK_API void UnixifyPath(String& path);
  TK_API String ConcatPaths(const StringArray& entries);
  TK_API String GetRelativeResourcePath(const String& path);
  
  enum class ResourceType;
  TK_API String CreatePathFromResourceType(const String& file, ResourceType type);
  TK_API ResourceType GetResourceType(const String& ext);
  TK_API String GetTypeString(ResourceType type);
  TK_API String GetExtFromType(ResourceType type);
  TK_API String GetResourcePath(ResourceType type);
  
  TK_API char GetPathSeparator();
  TK_API String GetPathSeparatorAsStr();
  TK_API bool SupportedImageFormat(const String& ext);
  TK_API bool SupportedMeshFormat(const String& ext);

  // String operations.
  TK_API void Split(const String& s, const String& sep, StringArray& v);
  TK_API void ReplaceStringInPlace(String& subject, const String& search, const String& replace);
  TK_API String ToLower(const String& str);
  TK_API String Format(const char* msg, ...);

  // Debug geometries.
  class LineBatch;
  TK_API LineBatch* CreatePlaneDebugObject(PlaneEquation plane, float size);
  TK_API LineBatch* CreateLineDebugObject(const Vec3Array& corners);
  TK_API LineBatch* CreateBoundingBoxDebugObject(const BoundingBox& box, const Mat4* transform = nullptr);

  // Entity operations.
  TK_API void ToEntityIdArray(EntityIdArray& idArray, const EntityRawPtrArray& ptrArray);
  TK_API bool IsInArray(const EntityRawPtrArray& nttArray, Entity* ntt);
  TK_API void GetRootEntities(const EntityRawPtrArray& entities, EntityRawPtrArray& roots);
  TK_API void GetParents(const Entity* ntt, EntityRawPtrArray& parents);
  TK_API void GetChildren(const Entity* ntt, EntityRawPtrArray& children);
  TK_API Entity* DeepCopy(Entity* root, EntityRawPtrArray& copies); // copies: First one is the copy root, fallowings are attached children.
  TK_API Entity* DeepInstantiate(Entity* root, EntityRawPtrArray& instances);

  // Vector operations.
  TK_API int IndexOf(Entity* ntt, const EntityRawPtrArray& entities);

  template<typename T>
  void pop_front(std::vector<T>& vec)
  {
    assert(!vec.empty());
    vec.erase(vec.begin());
  }

}
