// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class VillageStart {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_VILLAGESTART
public:
    class VillageStart& operator=(class VillageStart const&) = delete;
    VillageStart(class VillageStart const&) = delete;
    VillageStart() = delete;
#endif

public:
    /*0*/ virtual ~VillageStart();
    /*1*/ virtual bool postProcess(class BlockSource&, class Random&, class BoundingBox const&);
    /*2*/ virtual bool isValid() const;
    /*3*/ virtual enum StructureFeatureType getType() const;
    MCAPI VillageStart(class Dimension&, class BiomeSource const&, class Random&, int, int, class IPreliminarySurfaceProvider const&);

protected:

private:

};