#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Mon Jun 29 15:52:41 2015 by mkanalyzer.py
// Author:      Daniele Marconi
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <cassert>
#include "treestream.h"

struct eventBuffer
{
  //--------------------------------------------------------------------------
  // --- Declare variables
  //--------------------------------------------------------------------------

  double	BeamSpot_x0;
  double	BeamSpot_y0;
  double	BeamSpot_z0;

  //--------------------------------------------------------------------------
  // --- Structs can be filled by calling fill(), or individual fill
  // --- methods, e.g., fillElectrons()
  // --- after the call to read(...)
  //----------- --------------------------------------------------------------



  void fillObjects()
  {
  }

  //--------------------------------------------------------------------------
  // Select objects for which the select function was called
  void saveObjects()
  {
    int n = 0;
  }

  //--------------------------------------------------------------------------
  // A read-only buffer 
  eventBuffer() : input(0), output(0) {}
  eventBuffer(itreestream& stream)
  : input(&stream),
    output(0)
  {
    if ( !input->good() ) 
      {
        std::cout << "eventBuffer - please check stream!" 
                  << std::endl;
	exit(0);
      }
    initBuffers();

    input->select("recoBeamSpot_offlineBeamSpot.x0",
                  BeamSpot_x0);
    input->select("recoBeamSpot_offlineBeamSpot.y0",
                  BeamSpot_y0);
    input->select("recoBeamSpot_offlineBeamSpot.z0",
                  BeamSpot_z0);

  }

  // A write-only buffer
  eventBuffer(otreestream& stream)
  : input(0),
    output(&stream)
  {
    initBuffers();

  
    output->add("recoBeamSpot_offlineBeamSpot.x0",
                BeamSpot_x0);
    output->add("recoBeamSpot_offlineBeamSpot.y0",
                BeamSpot_y0);
    output->add("recoBeamSpot_offlineBeamSpot.z0",
                BeamSpot_z0);

  }

  void initBuffers()
  {

  }
      
  void read(int entry)
  {
    if ( !input ) 
      { 
        std::cout << "** eventBuffer::read - first  call read-only constructor!"
                  << std::endl;
        assert(0);
      }
    input->read(entry);

    // clear indexmap
    for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
    ++item)
    item->second.clear();
  }

  void select(std::string objname)
  {
    indexmap[objname] = std::vector<int>();
  }

  void select(std::string objname, int index)
  {
    try
     {
       indexmap[objname].push_back(index);
     }
    catch (...)
     {
       std::cout << "** eventBuffer::select - first call select(""" 
                 << objname << """)" 
                 << std::endl;
       assert(0);
    }
  }

 void ls()
 {
   if( input ) input->ls();
 }

 int size()
 {
   if( input ) 
     return input->size();
   else
     return 0;
 }

 void close()
 {
   if( input )   input->close();
   if( output ) output->close();
 }

 // --- indexmap keeps track of which objects have been flagged for selection
 std::map<std::string, std::vector<int> > indexmap;

 // to read events
 itreestream* input;

 // to write events
 otreestream* output;

}; 
#endif
