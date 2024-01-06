#include "usifTest.h"

#include <pxr/usdImaging/usdImaging/modelSchema.h>
#include <pxr/usdImaging/usdImaging/usdPrimInfoSchema.h>
#include <pxr/imaging/hd/primvarsSchema.h>

#include <iostream>

usifTestRefPtr usifTest::New(
    const pxr::HdSceneIndexBaseRefPtr& inputSceneIndex,
    const pxr::HdContainerDataSourceHandle& inputArgs)
{
    return pxr::TfCreateRefPtr( new usifTest(inputSceneIndex, inputArgs) );
}

usifTest::usifTest(
    const pxr::HdSceneIndexBaseRefPtr& inputSceneIndex,
    const pxr::HdContainerDataSourceHandle& inputArgs)
    : pxr::HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
{
    const pxr::SdfPath& rootPath = pxr::SdfPath::AbsoluteRootPath();
    const pxr::HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(rootPath);

    std::cout << __FUNCTION__ << " usifTest loaded" << std::endl;
}

usifTest::~usifTest() = default;

pxr::HdSceneIndexPrim usifTest::GetPrim(const pxr::SdfPath& primPath) const
{
    return _GetInputSceneIndex()->GetPrim(primPath);
}

pxr::SdfPathVector usifTest::GetChildPrimPaths(const pxr::SdfPath& primPath) const
{
    return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
}

void usifTest::_PrimsAdded(
    const pxr::HdSceneIndexBase& sender,
    const pxr::HdSceneIndexObserver::AddedPrimEntries& entries)
{
    for (const pxr::HdSceneIndexObserver::AddedPrimEntry& entry : entries)
    {
        const pxr::SdfPath& path = entry.primPath;
        std::cout << __FUNCTION__ << " " << path << std::endl;

        // check for a specific primvar named 'primvars:usifText:myVar' on newly added prims 
        if (pxr::HdSampledDataSourceHandle countDs =
            pxr::HdPrimvarsSchema::GetFromParent(_GetInputSceneIndex()->GetPrim(entry.primPath).dataSource)
            .GetPrimvar(pxr::TfToken("usifText:myVar"))
            .GetPrimvarValue()) 
        {
            VtValue v = countDs->GetValue(0.0f);
            if (v.IsHolding<int>()) {
                std::cout << " --- '" << entry.primPath << "' has primvar usifText:myVar=" << v.UncheckedGet<int>() << std::endl;
            }
        }
    }

#if 0
    pxr::HdSceneIndexObserver::AddedPrimEntries newEntries;
    pxr::HdSceneIndexObserver::RemovedPrimEntries removedEntries;
    if (!removedEntries.empty()) {
        _SendPrimsRemoved(removedEntries);
    }
    if (!newEntries.empty()) {
        _SendPrimsAdded(newEntries);
    }
#endif

    _SendPrimsAdded(entries);
}

void usifTest::_PrimsRemoved(
    const pxr::HdSceneIndexBase& sender,
    const pxr::HdSceneIndexObserver::RemovedPrimEntries& entries)
{
    if (!_IsObserved()) {
        return;
    }

    for (const pxr::HdSceneIndexObserver::RemovedPrimEntry& entry : entries)
    {
        const pxr::SdfPath& path = entry.primPath;
        std::cout << __FUNCTION__ << " " << path << std::endl;
    }

    _SendPrimsRemoved(entries);
}

void usifTest::_PrimsDirtied(
    const pxr::HdSceneIndexBase& sender,
    const pxr::HdSceneIndexObserver::DirtiedPrimEntries& entries)
{
    for (const pxr::HdSceneIndexObserver::DirtiedPrimEntry& entry : entries)
    {
        const pxr::SdfPath& path = entry.primPath;
        std::cout << __FUNCTION__ << " " << path << std::endl;
    }

#if 0
    pxr::HdSceneIndexObserver::RemovedPrimEntries removedEntries;
    pxr::HdSceneIndexObserver::AddedPrimEntries addedEntries;
    pxr::HdSceneIndexObserver::DirtiedPrimEntries dirtiedEntries;
    if (!removedEntries.empty()) {
        _SendPrimsRemoved(removedEntries);
    }
    if (!addedEntries.empty()) {
        _SendPrimsAdded(addedEntries);
    }
    if (!dirtiedEntries.empty()) {
        _SendPrimsDirtied(dirtiedEntries);
    }
#endif

    _SendPrimsDirtied(entries);
}