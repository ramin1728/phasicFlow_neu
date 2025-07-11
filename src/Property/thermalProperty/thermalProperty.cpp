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

#include "thermalProperty.hpp"
#include "dictionary.hpp"

bool pFlow::thermalProperty::readDictionary()
{
  
  heatCapacities_     = getVal<realVector>("heatCapacities");
  
  heatConductivities_ = getVal<realVector>("heatConductivities");

  if(materials().size() != heatCapacities_.size() )
  {
    fatalErrorInFunction<<
    "  number of elements in material (" << materials().size() <<
    ") is not equal to number of elements in heat capacities (" << heatCapacities_.size() << ") in dictionary " << globalName() << endl;
    return false;
  }

  if(materials().size() != heatConductivities_.size() )
  {
    fatalErrorInFunction<<
    "  number of elements in material (" << materials().size() <<
    ") is not equal to number of elements in heat conductivities (" << heatConductivities_.size() << ") in dictionary " << globalName() << endl;
    return false;
  }

  return true;
}

bool pFlow::thermalProperty::writeDictionary()
{

  if(!add("heat capacities", heatCapacities_))
  {
    fatalErrorInFunction<<
    "  error in writing heat capacities to dictionary "<< globalName()<<endl;
    return false;
  }

  if(!add("heat conductivities", heatConductivities_))
  {
    fatalErrorInFunction<<
    "  error in writing heat conductivities to dictionary "<< globalName()<<endl;
    return false;
  }

  return true;
}

pFlow::thermalProperty::thermalProperty(const word& fileName, repository* owner) :
property(fileName, owner)
{
  if(!readDictionary())
  {
    fatalExit;
  }
}

pFlow::thermalProperty::thermalProperty(const word &fileName, const fileSystem &dir) :
property(fileName, nullptr)
{
  if(!readDictionary())
  {
    fatalExit;
  }
}

pFlow::thermalProperty::thermalProperty(const word& fileName, const wordVector& materials, const realVector& densities, 
                                                                                           const realVector& heatCapacities, 
                                                                                           const realVector& heatConductivities) :
property(fileName, materials, densities, nullptr),
heatCapacities_(heatCapacities),
heatConductivities_(heatConductivities)
{
  if(!writeDictionary())
  {
    fatalExit;
  }
}
