// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class StructureTemplatePool {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_STRUCTURETEMPLATEPOOL
public:
    class StructureTemplatePool& operator=(class StructureTemplatePool const&) = delete;
    StructureTemplatePool(class StructureTemplatePool const&) = delete;
    StructureTemplatePool() = delete;
#endif

public:
    MCAPI StructureTemplatePool(std::string, std::string, std::vector<struct std::pair<class StructurePoolElement const* , int>>&);
    MCAPI std::string const& getFallback() const;
    MCAPI class StructurePoolElement const* getRandomTemplate(class Random&) const;
    MCAPI std::vector<unsigned __int64> getShuffledTemplateIndexes(class Random&) const;
    MCAPI class StructurePoolElement const* getTemplate(unsigned __int64) const;
    MCAPI bool isValid() const;

protected:

private:

};