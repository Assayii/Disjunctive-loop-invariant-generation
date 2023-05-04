
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
 * Filename: Location
 * Author: Sriram Sankaranarayanan< srirams@theory.stanford.edu>
 * Comments:
 * A location contains information about a location.
 * Information includes outgoing transitions
 * The location specific dual variables are all kept in
 * a var-info created for that purpose
 * a range of indices [l,r) is specified over that locations specific
 * variables
 * Post-Comments: SACRED CODE. Reimplemented for the DUCHESS project.
 * Copyright: see README file for the copyright.
 */

#ifndef __LOCATION__H_
#define __LOCATION__H_

#include <iostream>
#include <string>
#include <ppl.hh>
#include "var-info.h"
#include "Context.h"
#include "Clump.h"

using namespace std;
using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::IO_Operators;



class Location{
  private:

   int n; // the number of variables in the location
   var_info * f, *fd, *fm ; // the primal and dual var-infos
   bool polyset; // has the initial condition been set
   string name;// name
   Context *c; // the solver for inter-location transitions
   C_Polyhedron * p; // the initial condition
   // If there is none, then initialized to false

   // the final invariant that I will compute for the location
   // Post-comments: To do.. change this into an invariant map. I did this initially
   // so that I could run auto-strengthening. But this is to cumbersome.
   C_Polyhedron * invariant;

   // A pre-assigned invariant that i will use to strengthen transitions.
   C_Polyhedron * loc_inv;

   // has context been made
   bool context_made;

   // the left-most index of the coefficient variable.. the coefficients for
   // the parametric invariants for the location span the range [l.. l+n]
   int l;
   
   // Initialize and form parametric coefficients for the invariant
   void initialize(int n, var_info *f,
                   var_info * fd, var_info *fm,
                   C_Polyhedron * p, string  name);
   // Initialize but do not form new coefficients
   void initialize_without_populating(int n, var_info *f, var_info * fd,
                                      var_info *fm,C_Polyhedron * p,
                                      string  name, int left);

 
   
  public:
   Location(int n, var_info *f, var_info * fd,
            var_info *fm, C_Polyhedron * p, string name);

   Location(int n, var_info *f, var_info * fd,
            var_info *fm, string name);

   // A location with preset var-infos and a given starting point
   
   Location(int n, var_info *f, var_info * fd, var_info *fm,
            string name, int left);
   
   Location(int n, var_info *f, var_info * fd, var_info *fm,
            C_Polyhedron *p, string name, int left);
   

   // set the initial polyhedron to p
   void set_polyhedron(C_Polyhedron * p);
   // has the inital been set
   bool has_initial();


   void add_clump(vector<Clump> & vcl);
   void make_context();

   void compute_dual_constraints() ; 
   void compute_dual_constraints(Context & cc ) ; // the dual constraints
   void compute_dual_constraints(C_Polyhedron & cc ) ; // the dual constraints

   int get_dimension() const;
   const var_info *   get_var_info() const;
   const var_info * get_dual_var_info() const;
   int get_range_left() const;
   
   bool matches(string name) const;

   C_Polyhedron const & get_poly_reference() const{
      if (polyset)
         return (*p);
      cerr<<" asked reference when poly is not set "<<endl;
      abort();
   }
   
      
   C_Polyhedron & invariant_reference(){
      return (*invariant);
   }

   C_Polyhedron * get_initial();
   
   Context * get_context();

   bool initial_poly_set()const{
      return polyset;
   }
   
   void force_polyset(){
      cerr<<" Encountered a call to Location::force_poly_set()"<<endl;
      abort();
      polyset=true;
   }

   C_Polyhedron & get_non_const_poly_reference(){
      return *p;
   }

   void set_invariant_polyhedron(C_Polyhedron * what){
      loc_inv->intersection_assign((*what));
   }

   C_Polyhedron const & inv_poly_reference() const{
      return (*loc_inv);
   }
   
   
   void extract_invariants_and_update(C_Polyhedron & pp, C_Polyhedron & dualp);
   
   string const & get_name() const;
   
   void populate_coefficients(); // compute the coefficients required and add them to the constraint store
   void add_to_trivial(C_Polyhedron * trivial);
   void add_to_trivial(C_Polyhedron & trivial);
   
   void initialize_invariant();
   void extract_invariant_from_generator(Generator_System const & g);
   void extract_invariant_from_generator(Generator const & g);
   C_Polyhedron const & get_invariant() const;
   void update_dual_constraints(C_Polyhedron & dualp);
};

ostream & operator << (ostream & in, Location const & l); // print the location

#endif
