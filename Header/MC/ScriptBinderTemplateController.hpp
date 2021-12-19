// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ScriptApi.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptBinderTemplateController {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTBINDERTEMPLATECONTROLLER
public:
    class ScriptBinderTemplateController& operator=(class ScriptBinderTemplateController const&) = delete;
    ScriptBinderTemplateController(class ScriptBinderTemplateController const&) = delete;
#endif

public:
    MCAPI ScriptBinderTemplateController();
    MCAPI std::unique_ptr<class ScriptObjectBinder> deserialize(class ScriptEngine&, class ScriptApi::ScriptObjectHandle const&) const;
    MCAPI ~ScriptBinderTemplateController();

protected:

private:
    MCAPI void _initialize();

};