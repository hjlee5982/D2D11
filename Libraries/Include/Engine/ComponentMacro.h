#pragma once
#include "TypeRegistry.h"

#define COMPONENT_BODY(TYPE) \
public: \
    static const char* StaticTypeName() { return #TYPE; } \
    virtual const char* GetTypeName() const override { return StaticTypeName(); } \
private: \
    static std::unique_ptr<TestComponent> CreateInstance() { return std::make_unique<TYPE>(); } \
    static TypeRegistrar _registrar;

#define COMPONENT_IMPL(TYPE) \
TypeRegistrar TYPE::_registrar(TYPE::StaticTypeName(), &TYPE::CreateInstance);