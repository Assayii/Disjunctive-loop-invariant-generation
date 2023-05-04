
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

#include "myassertions.h"
#include "PolyUtils.h"
#include "TransitionRelation.h"
#include "DualTransitionRelation.h"

extern bool zero;
extern bool one;

void TransitionRelation::initialize(int n, var_info *f, var_info * fd,var_info * fm,
                                    Location * preloc, Location * postloc, C_Polyhedron *rel,string name){
   this->n=n;
   this->f=f;
   fp=f->prime();
   this->fd=fd;
   
   this->fm=fm;
   this->preloc=preloc;
   this->postloc=postloc;
   this->rel=rel;
   this->name=name;
   populate_multipliers();
   fired=0;
   
   guard=new C_Polyhedron(n, UNIVERSE);
   update=new C_Polyhedron(2*n, UNIVERSE);
   
}

void TransitionRelation::initialize(int n, var_info *f, var_info *fd, var_info * fm, string name){
   this->n=n;
   this->f=f;
   fp=f->prime();
   this->fd=fd;
   
   this->fm=fm;
   
   this->name=name;
   populate_multipliers();
   fired=0;

   
   guard=new C_Polyhedron(n, UNIVERSE);
   update=new C_Polyhedron(2*n, UNIVERSE);
   
}

void TransitionRelation::initialize_without_populating(int n, var_info *f, var_info * fd,var_info * fm,
                                                       Location * preloc, Location * postloc,
                                                       C_Polyhedron *rel,
                                                       string name, int index){
   this->n=n;
   this->f=f;
   fp=f->prime();
   this->fd=fd;
   
   this->fm=fm;
   this->preloc=preloc;
   this->postloc=postloc;
   this->rel=rel;
   this->name=name;
   this->index=index;
   fired=0;

   
   guard=new C_Polyhedron(n, UNIVERSE);
   update=new C_Polyhedron(2*n, UNIVERSE);
   
}

void TransitionRelation::initialize_without_populating(int n, var_info *f, var_info *fd,
                                                       var_info * fm, string name, int index ){
   this->n=n;
   this->f=f;
   fp=f->prime();
   this->fd=fd;
   
   this->fm=fm;
   this->index=index;
   this->name=name;
   fired=0;

   
   guard=new C_Polyhedron(n, UNIVERSE);
   update=new C_Polyhedron(2*n, UNIVERSE);
   
}


bool TransitionRelation::add_guard( Constraint const & ccs ){

   int i,j;
   bool flag=true;

   /*
    * Check that all the coefficients of the primed part are zero
    */
   
   for (i=n;i < 2*n ;++i){
      flag =handle_integers(ccs.coefficient(Variable(i)),j);
      if (j!=0 || !flag)
         return false;
      
   }

   /*
    * Add the constraints to the guard
    */
   
   flag=handle_integers(ccs.inhomogeneous_term(),j);

   // the use of flag captures overflows
   
   Linear_Expression ll(j);
 
   for (i=0;i<n;++i){
      flag &= handle_integers(ccs.coefficient(Variable(i)),j);
      ll+=j*Variable(i);
   }
   if (flag){
      if (ccs.is_equality()){
         guard->add_constraint(ll == 0);
      } else if (ccs.is_nonstrict_inequality()){
         guard->add_constraint(ll>=0);
      } else{
         guard->add_constraint(ll > 0);
      }
   }
   return flag;
}

bool TransitionRelation::add_preservation_relation( Constraint const & cc){
   int pres=-1;
   int i,j,j1;
   bool flag=true;
   if (!cc.is_equality())
      return false;
   flag=handle_integers(cc.inhomogeneous_term(),j);

   if (!flag) return false;

   if (j!=0) return false;
   
   for (i=0;i<n;++i){
      // Look at the coefficient of  i and i+n terms
      
      flag &= handle_integers(cc.coefficient(Variable(i)), j);
      flag &= handle_integers(cc.coefficient(Variable(i+n)), j1);
      // overflow?
      if (!flag) return false;
      // both are zero?
      if (j==0 && j1==0) continue;
      
      // both are non-zero and I have not seen any other candidate so far?

      if ((j+j1==0) && pres==-1){
         pres=i;
         continue;
      }
      // none of the above
      return false;
   }

   if (pres==-1)
      return false;

   preserved.insert(pres);
   return true;
}

bool TransitionRelation::split_relation(){

   Constraint_System cs=rel->minimized_constraints();
   
   // try to add it under guard if not
   // add it under preserved expressions
   // if not add it
   //
   
   Constraint_System::const_iterator vi;
   for (vi=cs.begin(); vi !=cs.end(); ++vi){
      if (add_guard((*vi)) || add_preservation_relation((*vi)))
         continue;
      update->add_constraint((*vi));
   }

   return true;
}

bool TransitionRelation::is_preserved(int i) const {
   if (preserved.find(i)==preserved.end())
      return false;
   return true;
}


void TransitionRelation::compute_post_new(const C_Polyhedron *p, C_Polyhedron & q) const{

   

   q= *p;

   //
   // q is a n dimensional polyhedron for which one needs to
   // compute the post operation
   //
   
   q.intersection_assign((*guard));
   
   if (q.is_empty())
      return;
   
   q.add_space_dimensions_and_embed(n);

   
   // now transform q for each preserved relation
   set<int>::iterator vi;
   
   for (vi=preserved.begin(); vi !=preserved.end(); ++vi){
      Linear_Expression ll= Variable((*vi));
      q.affine_image(Variable((*vi)+n), ll); // transforming
      //each preserved relation
   }


   q.intersection_assign((*update));
   
   Variables_Set vs;

   int i;
   for (i=0;i<n;i++) {
      vs.insert(Variable(i));
   }
   q.remove_space_dimensions(vs);
}



void TransitionRelation::set_locs(Location * preloc, Location * postloc){
   this->preloc=preloc;
   this->postloc=postloc;
}
void TransitionRelation::set_relation(C_Polyhedron * rel){
   this->rel=rel;
   compute_nc();
   split_relation();
}


void TransitionRelation::compute_nc(){
   Constraint_System cs = rel->minimized_constraints();
   Constraint_System::const_iterator vi;
   string str;
   nc=0;
   
   for(vi=cs.begin();vi!=cs.end();++vi)
      nc++;
}

TransitionRelation::TransitionRelation(int n, var_info * f, var_info * fd, var_info * fm, string name){
   initialize(n,f,fd,fm,name);
}

TransitionRelation::TransitionRelation(int n, var_info * f, var_info * fd, var_info * fm,
                                       Location * preloc, Location * postloc, C_Polyhedron * rel,string name){
   initialize(n,f,fd,fm,preloc,postloc,rel,name);
}


TransitionRelation::TransitionRelation(int n, var_info * f, var_info * fd, var_info * fm, string name, int index){
   initialize_without_populating(n,f,fd,fm,name,index);
}

TransitionRelation::TransitionRelation(int n, var_info * f, var_info * fd, var_info * fm,
                                       Location * preloc, Location * postloc, C_Polyhedron * rel,string name, int index){
   initialize_without_populating(n,f,fd,fm,preloc,postloc,rel,name, index);
}

void TransitionRelation::strengthen(const C_Polyhedron * p){

   guard->intersection_assign(*p); // update the guard
   
   C_Polyhedron * q = new C_Polyhedron(*p);
   q->add_space_dimensions_and_embed(n);
   rel->intersection_assign(*q);
   delete(q);

   compute_nc();
   split_relation();
}


void TransitionRelation::compute_post(const C_Polyhedron * p, C_Polyhedron & q) const{
   // assume that q=*p
   q= *p;
   
   q.add_space_dimensions_and_embed(n);

   q.intersection_assign(*rel);

   
   Variables_Set vs;

   int i;
   for (i=0;i<n;i++)
      vs.insert(Variable(i));

   q.remove_space_dimensions(vs);

   
}

/*
TransitionRelation * TransitionRelation::compose(TransitionRelation * t){
  // not implemented for the time being
}

*/

void TransitionRelation::compute_consecution_constraints( Context & c){
   // Use two expression stores. One for the equations and
   // the other for the inequations
   
   int r = fm->get_dimension(); // the number of multiplier variables
   int nd= fd->get_dimension();
   
   Constraint_System cs=rel->minimized_constraints();
   Constraint_System::const_iterator vi;
   int l1=preloc->get_range_left(), l2=postloc->get_range_left();
   
   int i,j;

   C_Polyhedron polyd(2*n+2+nc, UNIVERSE);
   int offset1=n+1, offset2=2*n+2;
   Linear_Expression ll(0);
   // first the constraints on the unprimed variables
   for(i=0;i<n;i++){
      
      ll=Variable(i); // place holder for \mu * c_i
      
      j=0;
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      //polyd.add_constraint_and_minimize(ll==0);
      polyd.add_constraint(ll==0);
   }

   // constraints on the primed variable
   for(i=0;i<n;i++){
    
      ll= -1* Variable(offset1+i); // - c_postloc_i 

      j=0;
      
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(n+i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      //polyd.add_constraint_and_minimize(ll==0);
      polyd.add_constraint(ll==0);
   }
   
   // Constraints on the constant variable

   
   ll=-Variable(n); // -M * d_preloc 
   
   j=0;
   for(vi=cs.begin();vi != cs.end(); vi++){
      ll+= - handle_integers((*vi).inhomogeneous_term())*Variable(offset2+j); // -coefficient for \lambda_j
      j++;
   }
   ll+=Variable(offset1+n); // + d_preloc
      
   //polyd.add_constraint_and_minimize(ll>=0) ;
   polyd.add_constraint(ll>=0) ;

   // Now for the positivity constraint

   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         //polyd.add_constraint_and_minimize(Variable(offset2+j)>=0);
         polyd.add_constraint(Variable(offset2+j)>=0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         //polyd.add_constraint_and_minimize(Variable(offset2+j)>0);
         polyd.add_constraint(Variable(offset2+j)>0);
         
      }
      
      j++;
   }


   polyd.remove_higher_space_dimensions(2*n+2);
   cout<<"After remove_higher_space_dimensions: "<<endl;
   cout<<"polyd is: "<<(polyd)<<endl;
   // now populate the context
   cs=polyd.minimized_constraints();
   cout<<"After cs=polyd.minimized_constraints: "<<endl;
   Expression e(nd,r,fd,fm);
   
   for (vi=cs.begin();vi !=cs.end();++vi){
      cout<<"cs is: "<<(*vi)<<endl;
      for(i=0;i<=n;i++)
         e[index].set_coefficient(l1+i,
                                  handle_integers((*vi).coefficient(Variable(i)))
                                  );

      for(i=0;i<=n;i++)
         e[r].set_coefficient( l2+i,
                               handle_integers((*vi).coefficient(Variable(offset1+i)))
                               );
      
      if ((*vi).is_inequality())
         c.add_inequality_expression(Expression(e));
      else if ((*vi).is_equality())
         c.add_equality_expression(Expression(e));
      
   }
   
#ifdef __DEBUG__D_
   cout<<"Test Message from TransitionRelation::compute_constraints(Context &)"<<endl;
   cout<<c;
   cout<<"Message ends"<<endl<<endl;
#endif
}

void TransitionRelation::compute_consecution_01(vector<Clump> & vcl, C_Polyhedron & initp){

   Clump cl(fd);
   Constraint_System cs;
   Constraint_System::const_iterator vi;
   int nd= fd->get_dimension();
   
   cout<<endl<<"- Before cs=rel->minimized_constraints(), rel is : "<<endl<<(*rel)<<endl;
   cs=rel->minimized_constraints();
   cout<<endl<<"- After cs=rel->minimized_constraints(), cs is : "<<endl<<cs<<endl;
   
   int l1=preloc->get_range_left(), l2=postloc->get_range_left();
   
   int i,j;
   
   C_Polyhedron polyd(2*n+2+nc, UNIVERSE);
   int offset1=n+1, offset2=2*n+2;
   Linear_Expression ll(0);
   // first the constraints on the unprimed variables
   for(i=0;i<n;i++){
      
      ll=Variable(i); // place holder for \mu * c_i
      
      j=0;
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      //polyd.add_constraint_and_minimize(ll==0);
      cout<<endl<<"ll == 0, ll is : "<<endl<<ll<<endl;
      polyd.add_constraint(ll==0);
   }
   
   // constraints on the primed variable
   for(i=0;i<n;i++){
    
      ll= -1* Variable(offset1+i); // - c_postloc_i 

      j=0;
      
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(n+i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      //polyd.add_constraint_and_minimize(ll==0);
      cout<<endl<<"ll == 0, ll is : "<<endl<<ll<<endl;
      polyd.add_constraint(ll==0);
   }
   
   // Constraints on the constant variable

   
   ll=-Variable(n); // -M * d_preloc 
   
   j=0;
   for(vi=cs.begin();vi != cs.end(); vi++){
      ll+= - handle_integers((*vi).inhomogeneous_term())*Variable(offset2+j); // -coefficient for \lambda_j
      j++;
      cout<<endl<<ll<<endl;
   }
   ll+=Variable(offset1+n); // + d_preloc
   cout<<endl<<"ll >= 0, ll is : "<<endl<<ll<<endl;
      
   cout<<endl<<"- 3.Before remove_higher_space_dimension(2+n+2), polyd(based on cs) is : "<<endl<<polyd<<endl;
   //polyd.add_constraint_and_minimize(ll>=0) ;
   polyd.add_constraint(ll>=0) ;

   cout<<endl<<"- 2.Before remove_higher_space_dimension(2+n+2), polyd(based on cs) is : "<<endl<<polyd<<endl;

   // Now for the positivity constraint

   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         //polyd.add_constraint_and_minimize(Variable(offset2+j)>=0);
         polyd.add_constraint(Variable(offset2+j)>=0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         //polyd.add_constraint_and_minimize(Variable(offset2+j)>0);
         polyd.add_constraint(Variable(offset2+j)>0);
         
      }
      
      j++;
   }

   cout<<endl<<"- 1.Before remove_higher_space_dimension(2+n+2), polyd(based on cs) is : "<<endl<<polyd<<endl;
   polyd.remove_higher_space_dimensions(2*n+2);
   cout<<endl<<"- After remove_higher_space_dimension(2+n+2), polyd is : "<<endl<<polyd<<endl;
   // now create two input polyhedra

   cs=polyd.minimized_constraints();
   
   C_Polyhedron p0(nd,UNIVERSE), p1(nd, UNIVERSE);
   //Expression e(nd,r,fd,fm);
   // mu=1
   LinExpr ll1(nd,fd);
   
   if (one){
   
   
      for (vi=cs.begin();vi!=cs.end();++vi){
         for(i=0;i<=n;i++)
            ll1[l1+i]=handle_integers((*vi).coefficient(Variable(i)));
         
         for(i=0;i<=n;i++)
            ll1[l2+i]=handle_integers((*vi).coefficient(Variable(offset1+i)));
         
         if ((*vi).is_inequality())
            //p1.add_constraint_and_minimize((ll1.to_lin_expression()) >= 0);
            p1.add_constraint((ll1.to_lin_expression()) >= 0);
         else if ((*vi).is_equality())
            //p1.add_constraint_and_minimize((ll1.to_lin_expression()) == 0);
            p1.add_constraint((ll1.to_lin_expression()) == 0);
         
      }
      cout<<endl<<"After setting mu = 1, p1 is : "<<endl<<p1<<endl;
      cl.insert(p1);
   }
   
   if (zero){
   // mu=0
      ll1*=0;
      for (vi=cs.begin();vi !=cs.end();++vi){
         for(i=0;i<=n;i++)
            ll1[l2+i]=handle_integers((*vi).coefficient(Variable(offset1+i)));
         
         if ((*vi).is_inequality())
            //p0.add_constraint_and_minimize((ll1.to_lin_expression()) >= 0);
            p0.add_constraint((ll1.to_lin_expression()) >= 0);
         else if ((*vi).is_equality())
            //p0.add_constraint_and_minimize((ll1.to_lin_expression()) == 0);
            p0.add_constraint((ll1.to_lin_expression()) == 0);
         
      }
      
      cout<<endl<<"After setting mu = 0, p0 is : "<<endl<<p0<<endl;
      cl.insert(p0);
      
   }
   vcl.push_back(cl);
   
   
   return;
}


void TransitionRelation::compute_consecution_constraints(vector<Clump> & vcl, C_Polyhedron & initp){
   
   // First make up a context and add the initiation constraints to it
   if (preloc->get_name()!=postloc->get_name()){
      cout<<"Computing 01 consecution"<<endl;
      compute_consecution_01(vcl,initp);
      return;
   }
   
   Context * cc= preloc->get_context();
   compute_consecution_constraints(*cc);
   
   /*
   Constraint_System cs;
   

   

   Constraint_System::const_iterator vi;
      
   int r = fm->get_dimension(); // the number of multiplier variables
   int nd= fd->get_dimension();
   
   cs=rel->minimized_constraints();
   
   int l1=preloc->get_range_left(), l2=postloc->get_range_left();
   
   int i,j;

   C_Polyhedron polyd(2*n+2+nc, UNIVERSE);
   int offset1=n+1, offset2=2*n+2;
   Linear_Expression ll(0);
   // first the constraints on the unprimed variables
   for(i=0;i<n;i++){
      
      ll=Variable(i); // place holder for \mu * c_i
      
      j=0;
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      polyd.add_constraint_and_minimize(ll==0);
   }
   
   // constraints on the primed variable
   for(i=0;i<n;i++){
    
      ll= -1* Variable(offset1+i); // - c_postloc_i 

      j=0;
      
      for(vi=cs.begin();vi != cs.end(); vi++){
         ll+= handle_integers((*vi).coefficient(Variable(n+i))) * Variable(offset2+j); // coefficient for \lambda_j
         j++;
      }
      
      polyd.add_constraint_and_minimize(ll==0);
   }
   
   // Constraints on the constant variable

   
   ll=-Variable(n); // -M * d_preloc 
   
   j=0;
   for(vi=cs.begin();vi != cs.end(); vi++){
      ll+= - handle_integers((*vi).inhomogeneous_term())*Variable(offset2+j); // -coefficient for \lambda_j
      j++;
   }
   ll+=Variable(offset1+n); // + d_preloc
      
   polyd.add_constraint_and_minimize(ll>=0) ;

   // Now for the positivity constraint

   j=0;
   for (vi=cs.begin();vi!=cs.end(); ++vi){
      
      if ((*vi).type()==Constraint::NONSTRICT_INEQUALITY){
         polyd.add_constraint_and_minimize(Variable(offset2+j)>=0);
      } else if ((*vi).type()==Constraint::STRICT_INEQUALITY){
         cerr<<"Location::compute_dual_constraints -- Warning: Encountered Strict Inequality"<<endl;
         cerr<<"                "<<(*vi)<<endl;
         polyd.add_constraint_and_minimize(Variable(offset2+j)>0);
         
      }
      
      j++;
   }


   polyd.remove_higher_space_dimensions(2*n+2);
   // now populate the context

      // now populate the context
   cs=polyd.minimized_constraints();

   Expression e(nd,r,fd,fm);
   
   for (vi=cs.begin();vi !=cs.end();++vi){
      for(i=0;i<=n;i++)
         e[index].set_coefficient( l1+i,
                                   handle_integers((*vi).coefficient(Variable(i)))
                                   );
      
      for(i=0;i<=n;i++)
         e[r].set_coefficient( l2+i ,
                               handle_integers ((*vi).coefficient(Variable(offset1+i)))
                              );
      
      if ((*vi).is_inequality())
         cc->add_inequality_expression(Expression(e));
      else if ((*vi).is_equality())
         cc->add_equality_expression(Expression(e));
      
   }

    cc->simplify_repeat();
   */
   // nothing to be done with the clump in this case
   return;
}


void TransitionRelation::populate_multipliers(){
  
   /*
   // Disabled. Implementing alternative strat.
   // nc is the number of linear multipliers that we need to add
   mult_left=fd->get_dimension();
   mult_right=mult_left+nc;

   for(i=0;i<nc;i++){
      str="L_"+ name+"_"+ int_to_str(i);
      fd->insert(str.c_str());
      
   }
   */
   index=fm->get_dimension();
   string str="M_"+name;
   fm->insert(str.c_str());
   
 
}

int TransitionRelation::get_range_left() const{
   return mult_left;
}

int TransitionRelation::get_range_right() const{
   return mult_right;
}

const string &  TransitionRelation::get_name() const{
   return name;
}

const string & TransitionRelation::get_preloc_name() const{
   return preloc->get_name();
}


const string & TransitionRelation::get_postloc_name() const{
   return postloc->get_name();
}

const C_Polyhedron & TransitionRelation::get_relation() const{
   return *rel;
}

const var_info * TransitionRelation::get_varinfo() const{
   return fp;
}

ostream & operator << (ostream & in, TransitionRelation const & t){
   // Just print the transition relation
   var_info const *ff=t.get_varinfo();
   
   in<<"Transition Relation"<<endl;
   in<<"Name: "<<t.get_name()<<endl;
   in<<"Pre-Location:"<<t.get_preloc_name()<<"  Post-Location:"<<t.get_postloc_name()<<endl;
   in<<"Transition Relation [["<<endl;
   print_polyhedron(in,t.get_relation(),ff);
   in <<" ]]"<<endl;

   in<< "Guard [["<<endl;
   print_polyhedron(in, t.get_guard_poly(), ff);
   in <<" ]]"<<endl;

   in<< "Update [["<<endl;
   print_polyhedron(in, t.get_update_poly(), ff);
   in <<" ]]"<<endl;

   in<<"Preserved [["<<endl;
   set<int> const & st= t.get_preserved_set();
   set<int>::iterator vxx;
   for (vxx=st.begin(); vxx !=st.end(); ++vxx){
      in << "  "<< ff->get_name((*vxx))<<"  ";
   }
   in << "]]"<<endl;
   
   
   in<<"Transition Relation Ends"<<endl;
   return in;   
}


bool TransitionRelation::matches(string & nam) const{
   return (name==nam);
}


bool TransitionRelation::fire(){
   if (!preloc->has_initial()){
      return false;
   }
   C_Polyhedron *pre_p=preloc->get_initial();
   C_Polyhedron post_p(n,UNIVERSE);
   compute_post_new(pre_p, post_p);
   
   postloc->set_polyhedron(&post_p);

   fired++;
   return true;
}

int TransitionRelation::get_firing_count(){
   return fired;
}

void TransitionRelation::add_preloc_invariant(){
   C_Polyhedron temp(preloc->inv_poly_reference());
   guard->intersection_assign(temp);
   temp.add_space_dimensions_and_embed(n);
   rel->intersection_assign(temp);
   compute_nc();
   return;
}


DualTransitionRelation TransitionRelation::get_dual_relation() const{
   // build the sat and the unsat polyhedron
   // first the sat polyhedron
   C_Polyhedron sat (2*n+2,UNIVERSE);
   dualize_standard(sat);
   int i,j;
   // now the signs of the first n+1 dimensions [0..n] to the negation of their
   // signs

   for (i=0;i<=n;++i) {
      Linear_Expression ll = -Variable(i);
      sat.affine_image(Variable(i),ll);
   }

   // that should take care of sat

   // now for unsat

   // use sat and set the variables from [n+1.. 2n+1] to [0...-1]
   C_Polyhedron unsat(n+1, UNIVERSE);
   Constraint_System cs=sat.minimized_constraints();
   Constraint_System::const_iterator vi;
   bool flag=true;
   for (vi= cs.begin(); vi !=cs.end(); ++vi){
      flag = handle_integers( (*vi).inhomogeneous_term(),j);
      Linear_Expression ll(j);
      for (i=0;i<=n;++i){
         flag &= handle_integers( (*vi).coefficient(Variable(i)),j);
         ll+= j * Variable(i);
      }
      flag &= handle_integers( (*vi).coefficient(Variable( 2*n+1)),j);
      ll-= j;
      INVARIANT( flag, "TransitionRelation::get_dual_relation() fatal failure ");
      if ((*vi).is_equality())
         unsat.add_constraint(ll==0);
      else if ((*vi).is_nonstrict_inequality())
         unsat.add_constraint(ll>=0);
      else
         unsat.add_constraint(ll==0);
   }

   return DualTransitionRelation(f,unsat,sat,preloc,postloc);
}


void TransitionRelation::dualize_standard(C_Polyhedron & result) const{

   result=C_Polyhedron (2*n+2+nc,UNIVERSE);
   Constraint_System cs=rel->minimized_constraints();
   Constraint_System::const_iterator vi;
   bool flag=true;
   int i;
   int j,k;

   //
   // dualize & build the constraints
   // \rho \models c_1 x_1 + ... + c_{n+2} x_1' + .. + c_{2n+1} x_n' + c_{n+1} + c_{2n+2} >=0
   //
   
   for (i=0;i<n ; ++i){
      Linear_Expression ll;
      ll+= -1 *Variable(i);
      flag=true;
      for (k=0,vi=cs.begin(); vi !=cs.end(); ++k,++vi){
         flag &= handle_integers((*vi).coefficient(Variable(i)),j);
         ll+= j * Variable(2*n+2+k);
      }
      INVARIANT ( flag, " Fatal overflow in TransitionRelation::dualize_standard ");
      
      result.add_constraint(ll==0);
   }

   
   for (i=n+1;i<2*n+1 ; ++i){
      Linear_Expression ll;
      ll+= -1 *Variable(i);
      flag=true;
      for (k=0,vi=cs.begin(); vi !=cs.end(); ++k,++vi){
         flag &= handle_integers((*vi).coefficient(Variable(i-1)),j);
         ll+= j * Variable(2*n+2+k);
      }
      INVARIANT ( flag, " Fatal overflow in TransitionRelation::dualize_standard ");
      
      result.add_constraint(ll==0);
   }

   
   // now for the constraint on the constant term
   Linear_Expression ll1;
   ll1= -1 *Variable(n) - Variable( 2*n +1);
   flag=true;
   for (k=0,vi=cs.begin(); vi !=cs.end(); ++k,++vi){
      flag &= handle_integers((*vi).inhomogeneous_term(),j);
      ll1+= j * Variable(2*n+2+k);
   }
   INVARIANT ( flag, " Fatal overflow in TransitionRelation::dualize_standard ");
   
   result.add_constraint(ll1<=0);

   // now add the constraints on the multipliers
   for (k=0,vi=cs.begin(); vi!=cs.end(); ++vi,++k){
      if ((*vi).is_equality()) continue;
      if ((*vi).is_nonstrict_inequality ())
         result.add_constraint( Variable(2*n + 2+k) >=0);
      else
         result.add_constraint( Variable(2*n + 2+k) > 0);
   }

   // project off the dimension..

   result.remove_higher_space_dimensions(2*n +2);
   return;
}

void TransitionRelation::check_map() {
   
   C_Polyhedron & pre_invariant = preloc->invariant_reference();
   C_Polyhedron & post_invariant = postloc->invariant_reference();

   C_Polyhedron temp(n, UNIVERSE);

   compute_post_new(&pre_invariant, temp);

   if (!post_invariant.contains(temp)){
      cerr<< " consecution failed for transition:"<<*this<<endl;
   }
   return;
}
