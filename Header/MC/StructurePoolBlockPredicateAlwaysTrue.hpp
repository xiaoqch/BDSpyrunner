// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class StructurePoolBlockPredicateAlwaysTrue {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_STRUCTUREPOOLBLOCKPREDICATEALWAYSTRUE
public:
    class StructurePoolBlockPredicateAlwaysTrue& operator=(class StructurePoolBlockPredicateAlwaysTrue const&) = delete;
    StructurePoolBlockPredicateAlwaysTrue(class StructurePoolBlockPredicateAlwaysTrue const&) = delete;
#endif

public:
    /*0*/ virtual ~StructurePoolBlockPredicateAlwaysTrue();
    /*
    inline bool test(class BlockPos const& a0, class BlockPos const& a1, class Randomize& a2) const{
        bool (StructurePoolBlockPredicateAlwaysTrue::*rv)(class BlockPos const&, class BlockPos const&, class Randomize&) const;
        *((void**)&rv) = dlsym("?test@StructurePoolBlockPredicateAlwaysTrue@@UEBA_NAEBVBlockPos@@0AEAVRandomize@@@Z");
        return (this->*rv)(std::forward<class BlockPos const&>(a0), std::forward<class BlockPos const&>(a1), std::forward<class Randomize&>(a2));
    }
    inline bool test(class Block const& a0, class Randomize& a1) const{
        bool (StructurePoolBlockPredicateAlwaysTrue::*rv)(class Block const&, class Randomize&) const;
        *((void**)&rv) = dlsym("?test@StructurePoolBlockPredicateAlwaysTrue@@UEBA_NAEBVBlock@@AEAVRandomize@@@Z");
        return (this->*rv)(std::forward<class Block const&>(a0), std::forward<class Randomize&>(a1));
    }
    */
    MCAPI StructurePoolBlockPredicateAlwaysTrue();

protected:

private:

};