// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BlockClimberSystem {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BLOCKCLIMBERSYSTEM
public:
    class BlockClimberSystem& operator=(class BlockClimberSystem const&) = delete;
    BlockClimberSystem(class BlockClimberSystem const&) = delete;
    BlockClimberSystem() = delete;
#endif

public:
    /*0*/ virtual ~BlockClimberSystem();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual void tick(class EntityRegistry&);

protected:

private:

};