/*------------------------------- phasicFlow ---------------------------------
      O        C enter of
     O O       E ngineering and
    O   O      M ultiscale modeling of
   OOOOOOO     F luid flow       
------------------------------------------------------------------------------
  Copyright (C): www.cemf.ir
  email: hamid.r.norouzi AT gmail.com
------------------------------------------------------------------------------  
Licence:
  This file is part of phasicFlow code. It is a free software for simulating 
  granular and multiphase flows. You can redistribute it and/or modify it under
  the terms of GNU General Public License v3 or any other later versions. 
 
  phasicFlow is distributed to help others in their research in the field of 
  granular and multiphase flows, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

-----------------------------------------------------------------------------*/

#ifndef __thermalProperty_hpp__
#define __thermalProperty_hpp__

#include "Vectors.hpp"
#include "hashMap.hpp"
#include "fileDictionary.hpp"
#include "iFstream.hpp"
#include "property.hpp"

namespace pFlow
{
/** 
 * thermalProperty holds the thermal properties of materials.
 * 
 * This class holds a list of  heat capacities and heat conductivities that are 
 * used in the simulation: for walls and particles.  
 */

class thermalProperty
:
  public property
  {
      private :

          /// list of heat capacities of materials 
          realVector    heatCapacities_;

          /// list of heat conductivities of materials 
          realVector    heatConductivities_;

          /// read from dict
          bool readDictionary();

          /// write to dict
          bool writeDictionary();

      public:

          /// Type info
          TypeInfo("thermalProperty");

          // - Constructors 

          explicit thermalProperty(const word& fileName, repository* owner=nullptr);


          thermalProperty(const word& fileName, const fileSystem& dir);

          thermalProperty(const word& fileName, const wordVector& materials, const realVector& densities, 
                                                                             const realVector& heatCapacities, 
                                                                             const realVector& heatConductivities);

          /// Default copy
          thermalProperty(const thermalProperty& ) = default;

          /// Default move
          thermalProperty(thermalProperty&& ) = default;

          /// Default copy assignment
          thermalProperty& operator= (const thermalProperty&) = default;

          /// Default move assignment
          thermalProperty& operator= (thermalProperty&&) = default;

          /// Default destructor 
          ~thermalProperty() override = default;

          inline const auto& heatCapacities()  const
          {
              return heatCapacities_;
          }

          inline const auto& heatConductivity()  const
          {
              return heatConductivities_;
          }

          /// Return density of material i
          inline real heatCapacity(uint32 i)   const 
          {
              return heatCapacities_[i];
          }

          inline real heatConductivity(uint32 i)   const 
          {
              return heatConductivities_[i];
          }

          inline bool heatCapacity(uint32 i, real& rho)const
          {
                if(i<numMaterials())
              {
                    rho = heatCapacity(i);
        
                    return true;
              }
              else
              {
                    rho = 0.00001;
        
                    return false;
              } 
          }

          inline bool heatConductivity(uint32 i, real& rho)const
          {
                if(i<numMaterials())
              {
                    rho = heatConductivity(i);
        
                    return true;
              }
              else
              {
                    rho = 0.00001;
        
                    return false;
              } 
          }
  };

} // pFlow

#endif  // __thermalProperty_hpp__