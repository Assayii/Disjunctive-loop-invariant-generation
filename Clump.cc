
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


#include "Clump.h"

extern int clump_prune_count;

void Clump::initialize(var_info * fd){
      nd=fd->get_dimension();
      this->fd=fd;
      gli=0;
}

int Clump::get_count(){
   return vp.size();
}

Clump::Clump(var_info * fd){
   initialize(fd);
}

void Clump::insert(C_Polyhedron const & p){
   vector<C_Polyhedron>::iterator vi;

   for (vi=vp.begin();vi<vp.end();++vi){
      if ((*vi).contains(p))
         return;
      else if (p.contains(*vi)){
         vi=vp.erase(vi);
         vi--;
       
      }
   }
   
   vp.push_back(p);
   return;
}

void Clump::prune(C_Polyhedron & p){
   //vector<C_Polyhedron>::iterator vi;
   int i;
   for (i=0; i < (int) vp.size();++i){
      if (p.contains(vp[i])){
         clump_prune_count++;
         if (gli>=i){
            gli--;
            if (gli <0)
               gli=-1; // this could work but also dump core!
            
         }
         
         vp.erase(vp.begin()+i);
         i--;
      }
   }

}

bool Clump::contains(C_Polyhedron & what){
   vector<C_Polyhedron>::iterator vi;

   for (vi=vp.begin();vi<vp.end();++vi){
      if ((*vi).contains(what))
         return true;
   }
   
   return false;
}
