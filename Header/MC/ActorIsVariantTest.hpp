// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "FilterTest.hpp"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ActorIsVariantTest : public FilterTest {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ACTORISVARIANTTEST
public:
    class ActorIsVariantTest& operator=(class ActorIsVariantTest const&) = delete;
    ActorIsVariantTest(class ActorIsVariantTest const&) = delete;
    ActorIsVariantTest() = delete;
#endif

public:
    /*0*/ virtual ~ActorIsVariantTest();
    /*1*/ virtual bool evaluate(struct FilterContext const&) const;
    /*2*/ virtual void finalizeParsedValue(class IWorldRegistriesProvider&);
    /*3*/ virtual class gsl::basic_string_span<char const, -1> getName() const;
    /*4*/ virtual class Json::Value _serializeValue() const;
    /*
    inline  ~ActorIsVariantTest(){
         (ActorIsVariantTest::*rv)();
        *((void**)&rv) = dlsym("??1ActorIsVariantTest@@UEAA@XZ");
        return (this->*rv)();
    }
    */

protected:

private:

};