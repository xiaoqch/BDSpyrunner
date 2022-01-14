// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "BlockActor.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ItemFrameBlockActor : public BlockActor {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ITEMFRAMEBLOCKACTOR
public:
    class ItemFrameBlockActor& operator=(class ItemFrameBlockActor const&) = delete;
    ItemFrameBlockActor(class ItemFrameBlockActor const&) = delete;
    ItemFrameBlockActor() = delete;
#endif

public:
    /*0*/ virtual ~ItemFrameBlockActor();
    /*1*/ virtual void load(class Level&, class CompoundTag const&, class DataLoadHelper&);
    /*2*/ virtual bool save(class CompoundTag&) const;
    /*3*/ virtual void saveBlockData(class CompoundTag&, class BlockSource&) const;
    /*4*/ virtual void loadBlockData(class CompoundTag const&, class BlockSource&, class DataLoadHelper&);
    /*5*/ virtual void onCustomTagLoadDone(class BlockSource&);
    /*6*/ virtual void tick(class BlockSource&);
    /*7*/ virtual void onChanged(class BlockSource&);
    /*8*/ virtual void onPlace(class BlockSource&);
    /*9*/ virtual void __unk_vfn_0();
    /*10*/ virtual void onRemoved(class BlockSource&);
    /*11*/ virtual void triggerEvent(int, int);
    /*12*/ virtual void clearCache();
    /*13*/ virtual void __unk_vfn_1();
    /*14*/ virtual float getShadowRadius(class BlockSource&) const;
    /*15*/ virtual bool hasAlphaLayer() const;
    /*16*/ virtual void __unk_vfn_2();
    /*17*/ virtual std::string const& getCustomName() const;
    /*18*/ virtual std::string getName() const;
    /*19*/ virtual std::string getImmersiveReaderText(class BlockSource&);
    /*20*/ virtual int getRepairCost() const;
    /*21*/ virtual class PistonBlockActor* getOwningPiston(class BlockSource&);
    /*22*/ virtual void __unk_vfn_3();
    /*23*/ virtual void __unk_vfn_4();
    /*24*/ virtual float getDeletionDelayTimeSeconds() const;
    /*25*/ virtual void __unk_vfn_5();
    /*26*/ virtual void __unk_vfn_6();
    /*27*/ virtual void __unk_vfn_7();
    /*28*/ virtual std::unique_ptr<class BlockActorDataPacket> _getUpdatePacket(class BlockSource&);
    /*29*/ virtual void _onUpdatePacket(class CompoundTag const&, class BlockSource&);
    /*30*/ virtual bool _playerCanUpdate(class Player const&) const;
    /*
    inline  ~ItemFrameBlockActor(){
         (ItemFrameBlockActor::*rv)();
        *((void**)&rv) = dlsym("??1ItemFrameBlockActor@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ItemFrameBlockActor(class BlockPos);
    MCAPI ItemFrameBlockActor(class BlockPos, enum BlockActorType, std::string);
    MCAPI void actuallyDropItem(class BlockSource&, bool);
    MCAPI void dropFramedItem(class BlockSource&, bool);
    MCAPI class ItemInstance& getFramedItem();
    MCAPI float getRotation();
    MCAPI void rotateFramedItem();
    MCAPI void setItem(class BlockSource&, class ItemInstance const&);
    MCAPI void updateNameTag();
    MCAPI static float const ROTATION_DEGREES;

protected:

private:
    MCAPI void _checkMapRemoval(class BlockSource&, class ItemInstance&);
    MCAPI void _updateBit(class BlockSource&, class ItemStateVariant<bool> const&, class HashedString const&);

};