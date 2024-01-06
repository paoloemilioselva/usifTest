#include "usifTestPlugin.h"
#include "usifTest.h"

#include <pxr/imaging/hd/sceneIndexPluginRegistry.h>
#include <pxr/imaging/hd/tokens.h>

PXR_NAMESPACE_USING_DIRECTIVE

TF_DEFINE_PRIVATE_TOKENS(
    _tokens, ((sceneIndexPluginName, "usifTestPlugin")));

TF_REGISTRY_FUNCTION(TfType)
{
    HdSceneIndexPluginRegistry::Define<usifTestPlugin>();
}

TF_REGISTRY_FUNCTION(HdSceneIndexPlugin)
{
    // https://github.com/PixarAnimationStudios/OpenUSD/blob/v23.11/pxr/imaging/hd/sceneIndexPluginRegistry.h#L95
    // Insertion phase is a broad ordering value with lower values indicating
    // earlier instantiation (possibly given render plugin-specific meaning
    // via enum values). Insertion order indicates whether this entry
    // should go at the start or end of the specified phase.
    const pxr::HdSceneIndexPluginRegistry::InsertionPhase insertionPhase = 0;
    const pxr::HdSceneIndexPluginRegistry::InsertionOrder insertionOrder = pxr::HdSceneIndexPluginRegistry::InsertionOrderAtStart;
    const std::string rendererDisplayName = "";
    pxr::HdSceneIndexPluginRegistry::GetInstance().RegisterSceneIndexForRenderer(
        rendererDisplayName, _tokens->sceneIndexPluginName, nullptr,
        insertionPhase, insertionOrder);
}

usifTestPlugin::usifTestPlugin() = default;
usifTestPlugin::~usifTestPlugin() = default;

pxr::HdSceneIndexBaseRefPtr usifTestPlugin::_AppendSceneIndex(
    const pxr::HdSceneIndexBaseRefPtr& inputSceneIndex,
    const pxr::HdContainerDataSourceHandle& inputArgs)
{
    TF_UNUSED(inputArgs);
    return usifTest::New( inputSceneIndex, {});
}
