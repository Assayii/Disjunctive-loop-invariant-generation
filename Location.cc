
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

#include "funcs.h"
#include "PolyUtils.h"
#include "Location.h"
#include "Context.h"



void Location::initialize(int n, var_info *f, var_info * fd, var_info *fm,C_Polyhedron * p, string  name){
   this->n=n;
   this->f=f;
   this->fd=fd;
   this->fm=fm;
   this->p=p;
   this->name=name;
   this->loc_inv=new C_Polyhedron(n,UNIVERSE);
   populate_coefficients();
   invariant=new C_Polyhedron(n,UNIVERSE);
   context_made=false;
}


void Location::initialize_without_populating(int n, var_info *f, var_info * fd, var_info *fm,C_Polyhedron * p, string  name, int left){
   this->n=n;
   this->f=f;
   this->fd=fd;
   this->fm=fm;
   this->p=p;
   this->name=name;
   this->loc_inv= new C_Polyhedron(n,UNIVERSE);
   l=left;
   invariant=new C_Polyhedron(n,UNIVERSE);
   context_made=false;
}

Context * Location::get_context(){
   return c;
}


void Location::make_context(){
   c=new Context(f,fd,fm);
   context_made=true;
}

Location::Location(int n, var_info *f, var_info * fd, var_info *fm, C_Polyhedron * p, string name){
   initialize(n,f,fd,fm,p,name);
   polyset=true;
}

Location::Location(int n, var_info *f, var_info * fd, var_info *fm, string name){
   C_Polyhedron * init = new C_Polyhedron(n, UNIVERSE);
   initialize(n,f,fd,fm,init,name);
   polyset=false;
}


Location::Location(int n, var_info *f, var_info * fd, var_info *fm,
                   string name, int left){

   C_Polyhedron * init = new C_Polyhedron(n, UNIVERSE);
   initialize_without_populating(n,f,fd,fm,init,name, left);
   polyset=false;

}


Location::Location(int n, var_info *f, var_info * fd, var_info *fm,
                   C_Polyhedron *p, string name, int left){

   initialize_without_populating(n,f,fd,fm,p,name, left);

   polyset=true;

}

void Location::set_polyhedron(C_Polyhedron * q){
   if (!polyset){
      p->intersection_assign(*q);
      polyset=true;
   } else{
      //p->poly_hull_assign_and_minimize(*q);
      p->poly_hull_assign(*q);
   }
}

C_Polyhedron * Location::get_initial(){
   return p;
}

bool Location::has_initial(){
   return polyset;
}

int Location::get_dimension() const{
   return n;
}

const var_info *   Location::get_var_info() const{
   return f;
}
const var_info * Location::get_dual_var_info() const{
   return fd;
}
int Location::get_range_left() const{
   return l;
}

void Location::add_clump(vector<Clump> & vcl){
   Clump cl(fd);
   c->recursive_strategy(cl);
   cout<<"Location::"<<name<<" pushing back clump with "<<cl.get_count()<<" Polyhedra"<<endl;
   cout<<endl<<"In add_clump, the new clump cl is ... "<<endl; cl.print_vector_of_poly();
   vcl.push_back(cl);
   cout<<"... done"<<endl;
}


bool Location::matches(string nam) const{
   return (name==nam);
}

void Location::populate_coefficients(){
   l=fd->get_dimension();
   int i;
   string dvi;
   for (i=0;i<n;i++){
      // dual_variable_i will be called c + location_name + i
      dvi="c_"+name+"_"+int_to_str(i);
      fd->insert(dvi.c_str());     
   }
   dvi="d_"+name;
   fd->insert(dvi.c_str());
   
}


string const& Location::get_name() const {
   return name;
}

ostream & operator << (ostream & in, Location const & l){
   // details of the location should go in here
   int n= l.get_dimension();
   
   const var_info * f= l.get_var_info();
   //const var_info * fd = l.get_dual_var_info();
   string name=l.get_name();
   // The rest to be completed later
   
  
   in<<"Location:"<<name<<endl;
   in << "# of variables"<<n<<endl;

   if (l.initial_poly_set()){
      in<<" Initial Condition: [[ "<<endl;
      in<<endl;
      print_polyhedron(in, l.get_poly_reference(), f);
      in <<endl;
      in <<"]]"<<endl;
   }else {
      in<<" [ no initial condition set]"<<endl;
   }
   in<<" Invariant: [[ "<<endl;
   in<<endl;
   print_polyhedron(in, l.get_invariant(), f);
   in <<endl;
   in <<"]]"<<endl;
   return in;
}

C_Polyhedron const & Location::get_invariant() const{
   return *invariant;
}

void Location::compute_dual_constraints(){
   compute_dual_constraints(*c);
   
}
void Location::compute_dual_constraints(Context & cc) {
   // Inefficient solution for the time being
   // Just build a polyhedron with the right coefficient variables
   //   and adding dimensions for the multipliers
   // Later expunge the multipliers
   // use >= as the default constraint state.
   // First obtain the number of constraints
   if (!polyset)
      return;
   Constraint_System  cs = p->minimized_constraints();
   Constraint_System::const_iterator vi ;
   cout<<"Current Constraint_System is: "<<endl;
   for (vi=cs.begin(); vi!=cs.end(); ++vi){
      cout<<(*vi)<<endl;
   }
   C_Polyhedron * result;
   
   int i,j,nc,nd;

   //count the number of multiplier variables required
   nc=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi)
      nc++;
   cout<<"nc: "<<nc<<endl;
   nd=fd->get_dimension();
   cout<<"nd: "<<nd<<endl;
   
   result=new C_Polyhedron(nd+nc,UNIVERSE); // create a universe polyhedron of nd +nc dimensions
   Linear_Expression lin(0);

   // Now build the constraints
   cout<<(*result)<<endl;
   cout<<"Now build the constraints: "<<endl;
   for (i=0;i<n;i++){
      lin=Linear_Expression(0);
      lin=lin- Variable(l+i); // add -c_i to the constraint
      cout<<"index l is: "<<l<<endl;
      cout<<"index n is: "<<n<<endl;
      cout<<"-c_i"<<Variable(l+i)<<endl;
      j=0;
      for (vi=cs.begin();vi!=cs.end(); ++vi){
         lin=lin + (*vi).coefficient(Variable(i)) * Variable(nd+j);
         j++;
      }
      cout<<lin<<endl;
      result->add_constraint(lin == 0); // Add the constraint lin==0 to the result
   }
   
   // Now the constraints on the constant
   cout<<(*result)<<endl;
   cout<<"Now the constraints on the constant: "<<endl;
   lin=Linear_Expression(0);
   lin=lin- Variable(l+n); // add -d to the constraint
   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      lin=lin + (*vi).inhomogeneous_term() * Variable(nd+j);
      j++;
   }
   cout<<"lin is: "<<lin<<endl;
   result->add_constraint(lin <= 0);
   
   // Now the constraints on the multipliers
   cout<<(*result)<<endl;
   cout<<"Now the constraints on the multipliers: "<<endl;
   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         result->add_constraint(Variable(nd+j) >= 0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         
         result->add_constraint(Variable(nd+j) >= 0); // Just handle it as any other inequality 
      }
      
      j++;
   }

   // Now those are all the constraints.
   cout<<(*result)<<endl;
   cout<<"Now those are all the constraints."<<endl;

#ifdef __DEBUG__D_
   print_polyhedron(cout,*result,fd);
#endif   
   result->remove_higher_space_dimensions(nd);// Remove the excess dimensions to obtain a new Polyhedron
   cout<<"After remove_higher_space_dimensions: "<<endl;
   cout<<"result is: "<<(*result)<<endl;
   cs = result->minimized_constraints();
   cout<<"After cs=result->minimized_constraints: "<<endl;
   for (vi=cs.begin();vi!=cs.end();vi++){
      cout<<"cs is:"<<(*vi)<<endl;
      cc.add_to_poly_store((*vi));
   }
   return;
}



void Location::compute_dual_constraints(C_Polyhedron & initp) {

   // solution for the time being
   // Just build a polyhedron with the right coefficient variables
   //   and adding dimensions for the multipliers
   // Later expunge the multipliers
   // use >= as the default constraint state.
   // First obtain the number of constraints

   // nothing to be done if polyhedra not set

   if (!polyset) {
      return;
   }
   if (p->is_empty()){
      return;
   }
   Constraint_System  cs = p->minimized_constraints();
   Constraint_System::const_iterator vi ;

   int i,j,nc,nd;

   //count the number of multiplier variables required
   nc=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi)
      nc++;

   nd=fd->get_dimension();
   
   C_Polyhedron result(nd+nc,UNIVERSE); // create a universe polyhedron of nd +nc dimensions
   Linear_Expression lin(0);

   // Now build the constraints
   for (i=0;i<n;i++){
      lin=Linear_Expression(0);
      lin=lin- Variable(l+i); // add -c_i to the constraint
      j=0;
      for (vi=cs.begin();vi!=cs.end(); ++vi){
         lin=lin + (*vi).coefficient(Variable(i)) * Variable(nd+j);
         j++;
      }

      result.add_constraint(lin == 0); // Add the constraint lin==0 to the result
      
   }

   // Now the constraints on the constant
   lin=Linear_Expression(0);
   lin=lin- Variable(l+n); // add -d to the constraint
   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      lin=lin + (*vi).inhomogeneous_term() * Variable(nd+j);
      j++;
   }

   result.add_constraint(lin <= 0);

   // Now the constraints on the multipliers

   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         result.add_constraint(Variable(nd+j) >= 0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         
         result.add_constraint(Variable(nd+j) >= 0); // Just handle it as any other inequality 
      }
      
      j++;
   }

   // Now those are all the constraints.

#ifdef __DEBUG__D_
   print_polyhedron(cout,result,fd);
#endif   
   cout<<endl<<"- 1.Before remove_higher_space_dimension(nd), result(based on cs) is : "<<endl<<result<<endl;
   result.remove_higher_space_dimensions(nd);// Remove the excess dimensions to obtain a new Polyhedron
   cout<<endl<<"- 2.After remove_higher_space_dimension(nd), result(based on cs) is : "<<endl<<result<<endl;

   // now add result
   if (context_made){
      cs=result.minimized_constraints();
      for (vi=cs.begin(); vi !=cs.end(); ++vi){
         c->add_to_poly_store((*vi));
      }
   }
   
   initp.intersection_assign(result);

   
   return;
}



void Location::initialize_invariant(){
   invariant=new C_Polyhedron(n, UNIVERSE);
}


void Location::extract_invariant_from_generator(Generator const & g){

   // Extract coefficients from l to r of the generators and make a constraint
   // Add this constraint to the invariant polyhedron

   cout<<endl<<"- In extract_invariant_from_generator(Generator const & g): "<<endl;
   cout<<endl<<"- Generator const & g is "<<g<<endl;
   Linear_Expression lin;
   cout<<endl<<"- g.space_dimension() is "<<g.space_dimension()<<endl;
   for (dimension_type i = g.space_dimension(); i-- >0; ){
      cout<<endl<<"- Variable("<<i<<") is "<<Variable(i);
      cout<<endl<<"- g.coefficient("<<Variable(i)<<") is "<<g.coefficient(Variable(i));
      lin += g.coefficient(Variable(i)) * Variable(i);
      cout<<endl<<"- lin is "<<lin<<endl;
   }

   Linear_Expression lin1;
   int c;
   bool flag=true;
   for(int i=0;i<n;i++){
      cout<<endl<<"- handle_integers("<<lin.coefficient(Variable(l+i))<<") is "<<handle_integers(lin.coefficient(Variable(l+i)) , c);
      cout<<endl<<"- lin.coefficient(Variable(l+i)) is "<<lin.coefficient(Variable(l+i));
      cout<<endl<<"- Variable("<<(l+i)<<") is "<<Variable(l+i);
      cout<<endl<<"- l is "<<l;
      cout<<endl<<"- i is "<<i;
      cout<<endl<<"- c is "<<c;
      if (! handle_integers(lin.coefficient(Variable(l+i)) , c)){
         flag = false;
         cout<<endl<<"- flag turns to false!"<<endl;
      }
      lin1+= c * Variable(i);
      cout<<endl<<"- lin1 is "<<lin1<<endl;
   }
   cout<<endl<<"- handle_integers("<<lin.coefficient(Variable(l+n))<<") is "<<handle_integers(lin.coefficient(Variable(l+n)) , c);
   cout<<endl<<"- lin.coefficient(Variable(l+i)) is "<<lin.coefficient(Variable(l+n));
   cout<<endl<<"- Variable("<<(l+n)<<") is "<<Variable(l+n);
   cout<<endl<<"- l is "<<l;
   cout<<endl<<"- n is "<<n;
   cout<<endl<<"- c is "<<c;
   if (! handle_integers(lin.coefficient(Variable(l+n)) ,c )){
      flag = false;
      cout<<endl<<"- flag turns to false!"<<endl;
   }
   lin1+=c;
   cout<<endl<<"- lin1 is "<<lin1<<endl;
   
   cout<<name<<"=>";
   print_lin_expression(cout,lin1,f);
   
   if (g.is_point() || g.is_ray()){
      if (flag){
         //invariant->add_constraint_and_minimize(lin1>=0);
         invariant->add_constraint(lin1>=0);
         cout<<"(add_to_invariant!)";
      }
      cout<<">=0"<<endl;
   }
   else if (g.is_line()) {
      if (flag){
         //invariant->add_constraint_and_minimize(lin1==0);
         invariant->add_constraint(lin1==0);
         cout<<"(add_to_invariant!)";
      }
      cout<<"==0"<<endl;
   }
   cout<<"invariant is "<<(*invariant)<<endl;
}


void Location::extract_invariant_from_generator(Generator_System const & gs){
   Generator_System::const_iterator vi=gs.begin();
   for (;vi!=gs.end();vi++)
      extract_invariant_from_generator(*vi);
}

void Location::add_to_trivial(C_Polyhedron * trivial){
   // add c_l=0
   for (int i=0;i<n;i++)
      //trivial->add_constraint_and_minimize(Variable(l+i)==0);
      trivial->add_constraint(Variable(l+i)==0);
   return;
}


void Location::add_to_trivial(C_Polyhedron & trivial){
   // add c_l=0
   for (int i=0;i<n;i++)
      //trivial.add_constraint_and_minimize(Variable(l+i)==0);
      trivial.add_constraint(Variable(l+i)==0);
   return;
}


void Location::extract_invariants_and_update(C_Polyhedron & pp, C_Polyhedron & dualp){
   cout<<endl<<"- In extract_invariant_and_update(C_Polyhedron & pp, & dualp) : "<<endl;
   cout<<endl<<"- For location "<<name<<endl;
   cout<<endl<<"- pp is "<<pp<<endl;
   cout<<endl<<"- pp.minimized_generators() is "<<pp.minimized_generators()<<endl;
   extract_invariant_from_generator(pp.minimized_generators());
   update_dual_constraints(dualp);
}

void Location::update_dual_constraints(C_Polyhedron & dualp){
   
   // now add the invariant information back to dualp
   Constraint_System  cs = invariant->minimized_constraints();
   Constraint_System::const_iterator vi ;
   C_Polyhedron * result;

   int i,j,nc,nd;
   
   //count the number of multiplier variables required
   nc=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi)
      nc++;

   nd=fd->get_dimension();
   
   result=new C_Polyhedron(nd+nc,UNIVERSE); // create a universe polyhedron of nd +nc dimensions
   Linear_Expression lin(0);

   // Now build the constraints
   for (i=0;i<n;i++){
      lin=Linear_Expression(0);
      lin=lin- Variable(l+i); // add -c_i to the constraint
      j=0;
      for (vi=cs.begin();vi!=cs.end(); ++vi){
         lin=lin + (*vi).coefficient(Variable(i)) * Variable(nd+j);
         j++;
      }

      result->add_constraint(lin == 0); // Add the constraint lin==0 to the result
      
   }

   // Now the constraints on the constant
   lin=Linear_Expression(0);
   lin=lin- Variable(l+n); // add -d to the constraint
   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      lin=lin + (*vi).inhomogeneous_term() * Variable(nd+j);
      j++;
   }

   result->add_constraint(lin <= 0);

   // Now the constraints on the multipliers

   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         result->add_constraint(Variable(nd+j) >= 0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         
         result->add_constraint(Variable(nd+j) >= 0); // Just handle it as any other inequality 
      }
      
      j++;
   }

   // Now those are all the constraints.

   result->remove_higher_space_dimensions(nd);// Remove the excess dimensions to obtain a new Polyhedron


   
   dualp.intersection_assign(*result);
   delete(result);
}
