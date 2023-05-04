
/*
 * lsting: Invariant Generation using Constraint Solving. 
 * Copyright (C) 2005 Sriram Sankaranarayanan < srirams@theory.stanford.edu>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/* 
 * Filename: Clump.cc
 * Author: Sriram Sankaranarayanan<srirams@theory.stanford.edu>
 * Comments: Clump module holds a disjunction of polyhedral constraints.
 * Copyright: Please see README file.
 */


#ifndef __CLUMP__H_
#define __CLUMP__H_


#include <vector>
#include <iostream>
#include <var-info.h>
#include <ppl.hh>


using namespace std;
using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::IO_Operators;



class Clump{

  private:
   /*
    * nd = num of dual dimensions (depends on what mode the
    *                              analyzer is operated in ) 
    * fd = var_info for dual -- standard pointer for printing purposes
    *                            that should not be touched
    * vp = vector of polyhedra
    *
    * gli = a pointer to some position in vp.. some sort of a poor
    *        man's iterator. In a future version, this will be made into a
    *        full fledged iterator. Do not see the need for that now.
    *          
    */
   
   int nd; 
   var_info * fd;
   vector<C_Polyhedron> vp;
   int gli;
   
   // Sriram - Aug 2004 - Old Code: PWC.
   void initialize(var_info * fd);

  public:
   // added by Hongming
   void print_vector_of_poly(){
      int clump_poly_count = 0;
      for (vector<C_Polyhedron>::iterator j = vp.begin(); j < vp.end(); j++ ){
        cout<<endl<<"clump_poly_count is "<<++clump_poly_count<<endl;
        cout<<(*j)<<endl;
      }
      return;
   }

   Clump(var_info * fd);
   
   int get_count();

   // Insert a polyhedron
   void insert(C_Polyhedron const & p);

   // Remove any polyhedron that is contained inside dualp
   // Sriram - Aug 2004 - Old Code: PWC.
   void prune(C_Polyhedron & dualp);

   // Is there a disjunct that contains "what"
   bool contains(C_Polyhedron & what);


   // operations on gli -- the java style is just co-incidental. ;-)
   // self-explanatory :-)
   
   void clear();
   
   bool has_next();

   C_Polyhedron & get_reference();

   void next();
};

inline void Clump::clear(){
   gli=0;
}

inline bool Clump::has_next(){
   return ( vp.size()> 0) && ( gli < (int) vp.size() );
}

inline C_Polyhedron & Clump::get_reference(){
   if (gli <0){
      // This should not happen.
      // I suck.
      cerr<<" Sloppy programming pays off.. Invariants could be lost!!"<<endl;
      return vp[0];
   }
      
   return vp[gli];
}

inline void Clump::next(){
   gli++;
}

#endif
