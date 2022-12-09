#pragma once

#include <TiltedCore/Platform.hpp>
#include <resources/Manifest.h>

#include "PluginAPI/PluginAPI.h"

class ScriptExecutor
{
  public:
    ScriptExecutor();
    ~ScriptExecutor();

    void RegisterRuntime(const char* const apExtension, IPluginInterface* apInterface);

    void Execute(const char* aScript);
    void ExecuteFile(const std::filesystem::path& aPath, const Resources::Manifest001& aManifest);

    void Bind(const char* const apSymbolName);

  private:
    IPluginInterface* SelectRuntimeForExtension(const std::string_view acExtension);

    template <typename T> T* CastInterfaceVersion(IPluginInterface *apInterface, int version)
    {
        return apInterface->GetVersion() == version ? reinterpret_cast<T*>(apInterface) : nullptr;
    }

  private:
    TiltedPhoques::Map<TiltedPhoques::String, IPluginInterface*> m_scriptRuntimes;
};
