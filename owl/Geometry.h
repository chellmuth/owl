// ======================================================================== //
// Copyright 2019-2020 Ingo Wald                                            //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "RegisteredObject.h"
#include "SBTObject.h"
#include "Module.h"
#include "Buffer.h"

namespace owl {

  struct Geom;

  struct ProgramDesc {
    Module::SP  module;
    std::string progName;
  };
  
  struct GeomType : public SBTObjectType {
    typedef std::shared_ptr<GeomType> SP;
    
    /*! any device-specific data, such as optix handles, cuda device
        pointers, etc */
    struct DeviceData : public RegisteredObject::DeviceData {
      typedef std::shared_ptr<DeviceData> SP;

      DeviceData(const DeviceContext::SP &device)
        : RegisteredObject::DeviceData(device)
      {};
      
      void buildHitGroupPrograms(GeomType *gt);
      
      virtual void fillPGDesc(OptixProgramGroupDesc &pgDesc,
                              GeomType *gt,
                              int rayType);
      
      // void writeSBTHeader(uint8_t *const sbtRecord,
      //                     Device *device,
      //                     int rayTypeID);
      
      /*! hit group program groups, per ray type */
      std::vector<OptixProgramGroup> hgPGs;
    };

    
    GeomType(Context *const context,
             size_t varStructSize,
             const std::vector<OWLVarDecl> &varDecls);
    
    virtual std::string toString() const { return "GeomType"; }

    DeviceData &getDD(const DeviceContext::SP &device) const
    {
      assert(device->ID < deviceData.size());
      return *deviceData[device->ID]->as<DeviceData>();
    }
    /*! creates the device-specific data for this group */
    RegisteredObject::DeviceData::SP createOn(const DeviceContext::SP &device) override
    { return std::make_shared<DeviceData>(device); }
    
    
    virtual std::shared_ptr<Geom> createGeom() = 0;
    
    virtual void setAnyHitProgram(int rayType,
                                  Module::SP module,
                                  const std::string &progName);
    virtual void setClosestHitProgram(int rayType,
                                      Module::SP module,
                                      const std::string &progName);

    std::vector<ProgramDesc> anyHit;
    std::vector<ProgramDesc> closestHit;

  };

  struct Geom : public SBTObject<GeomType> {
    typedef std::shared_ptr<Geom> SP;

    Geom(Context *const context,
         GeomType::SP geomType);
    virtual std::string toString() const { return "Geom"; }

    void writeSBTRecord(uint8_t *const sbtRecord,
                        const DeviceContext::SP &device,
                        int rayTypeID);
    
    GeomType::SP geomType;
  };

} // ::owl