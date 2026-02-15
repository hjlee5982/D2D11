#pragma once
#include "TypeRegistry.h"

#define COMPONENT_BODY(TYPE) \
public:\
    TYPE();\
    static const char* StaticTypeName() { return #TYPE; } \
    virtual const char* GetTypeName() const override { return StaticTypeName(); } \
    static TypeInfo* GetStaticTypeInfo(); \
    static std::unique_ptr<TestComponent> CreateInstance() { return std::make_unique<TYPE>(); } \
private:\
    static TypeRegistrar _registrar;

#define COMPONENT_IMPL(TYPE) \
TYPE::TYPE(){}\
\
static bool TYPE##_TypeInit = []()\
{\
    TypeInfo* type = TypeRegistry::RegisterType(TYPE::StaticTypeName(), &TYPE::CreateInstance);\
    TYPE::RegisterFields(type);\
    return true;\
}();

#define REGISTER_FIELD(TYPE, FIELD) \
RegisterField<TYPE>(type, #FIELD, &TYPE::FIELD);

#define PROPERTY_FIELD static void RegisterFields(TypeInfo* type)