// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LootTables {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LOOTTABLES
public:
    class LootTables& operator=(class LootTables const&) = delete;
    LootTables(class LootTables const&) = delete;
    LootTables() = delete;
#endif

public:
    MCAPI class LootTable* lookupByName(std::string const&, class ResourcePackManager&);
    MCAPI ~LootTables();

protected:

private:

};