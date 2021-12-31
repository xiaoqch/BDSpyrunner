// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

namespace VanillaWorldSystems {

#define AFTER_EXTRA
// Add Member There
class Impl {
public:
    Impl() = delete;
    Impl(Impl const&) = delete;
    Impl(Impl const&&) = delete;
};

#undef AFTER_EXTRA
    MCAPI class std::shared_ptr<class VanillaWorldSystems::Impl> init(class Level*, class Experiments const&, class BaseGameVersion const&, class ResourcePackManager*);

};