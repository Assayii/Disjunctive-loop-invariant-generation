%{
#include <iostream>
#include "var-info.h"
#include "Location.h"
#include "PolyUtils.h"
#include "TransitionRelation.h"
#include "InvariantMap.h"
#include "DualInvariantMap.h"
#include "System.h"
#include "Timer.h"
#include "ppl.hh"
   
   
   using namespace std;
   using namespace Parma_Polyhedra_Library;
   using namespace Parma_Polyhedra_Library::IO_Operators;

   bool gendrop;
   int num_context;
   bool zero;
   bool one;
   int prop_steps;
   int weave_time;
   bool ch79,bhrz03,dual;
   
   C_Polyhedron * trivial, *dualp;
   
#ifndef MAX_ID_SIZE
#define MAX_ID_SIZE 100
#endif
   
#define ONECONTEXT 0
#define GENDROP 1
#define MANYCONTEXT 2
#define BULLSHIT 3
#define RESIDUAL_TR_SYS 4
#define ZERO_ONLY 5
#define ONE_ONLY 6
#define ZERO_ONE 7
#define NO_INSTANTIATION 8
#define NO_CH79 9
#define NO_BHRZ03 10
#define NO_DUAL 11
#define YES_CH79 12
#define YES_BHRZ03 13
#define YES_DUAL 14
#define INV_CHECK 15
#define NO_INV_CHECK 16
   
   
   
   char err_str[100];
   extern int linenum;
   int dimension;
   var_info * f, *fd, *fm;
   vector<Location *> * loclist;
   vector<TransitionRelation *> * trlist;
   Context *glc;// The global context
   vector<Context *>* children;
   vector<System *> * global_sub_system_list;
   System * global_system;
   Timer weave_timer;
   int * tt;
   C_Polyhedron * invd;

   bool inv_check;
   
   
   extern int yyparse();
   extern int yylex();
   void yyerror(char const * x);
   void yyerror(string  const & x);
   void parseinit();
   void collect_generators(vector<Context *> * children , Generator_System & g);
   int parse_cmd_line(char * x);
   int weave_count;
   int bang_count;
   int prune_count;
   int clump_prune_count;
   int context_count;
   bool search_location(char * w, Location ** m);
   bool search_transition_relation(char * w, TransitionRelation ** m);
   int find_variable( char* what);
   void add_preloc_invariants_to_transitions();
   void print_status();
   void print_bake_off(InvariantMap const & what);
   
   void check_invariant_ok();
   
%}

%union{
   char * string;
   var_info * v;
   int dummy;
   int integer;
   char identifier[MAX_ID_SIZE];
   var_info * vi;
   Location *ll;
   TransitionRelation * tt;
   Linear_Expression * li;
   Constraint * cc;
   C_Polyhedron * pp;
   vector<int> * vv;
}


%token <integer> INT
%token <identifier> IDENT
%token PRIME END VARIABLED LOCATION TRANSITION
%token EQ LEQ GEQ LE GE
%token PRES PROPS INVARIANT

%type<vi> dimvector
%type<identifier> identifier
%type<ll> location_identifier location_descriptor
%type<tt> transition_identifier transition_descriptor
%type<li> linear_expression primed_linear_expression linear_term primed_term
%type<cc> linear_inequality primed_linear_inequality
%type<pp> linear_assertion primed_linear_assertion preservative
%type<vv> variable_list


%start program

%nonassoc GEQ LEQ EQ
%left '+' '-'
%left '*'
%right UMINUS


%%

program: header optional_commands system_descriptor END{
   // just print it for the fun of it
};

header: VARIABLED {
} '[' dimvector ']'{
   f=$4; // This is the main dimvector
   dimension=f->get_dimension();
}
;

optional_commands: PROPS '(' INT ')' {
   prop_steps=$3;
   
} | {}
;

dimvector: dimvector identifier {
   $$=$1;
   $$->search_and_insert($2);
}
| identifier {
   $$=new var_info();
   $$->search_and_insert($1);
};

system_descriptor:location_descriptor system_descriptor{
   
}
| transition_descriptor system_descriptor{

}
| location_descriptor{

}
| transition_descriptor{
   
}
| invariant_descriptor system_descriptor{}
| invariant_descriptor{}
;

location_descriptor: LOCATION location_identifier{
   $$=$2;
}
| LOCATION location_identifier linear_assertion{
   $$=$2;
   $$->set_polyhedron($3);
}
;

transition_descriptor: TRANSITION transition_identifier ':' location_identifier ',' location_identifier ',' primed_linear_assertion{
   $$=$2;
   $$->set_locs($4,$6);
   $$->set_relation($8);
}
| TRANSITION  transition_identifier ':' location_identifier ',' primed_linear_assertion{
   $$=$2;
   $$->set_locs($4,$4);
   $$->set_relation($6);
}
;

invariant_descriptor: INVARIANT location_identifier linear_assertion {
   $2->set_invariant_polyhedron($3);
}
| INVARIANT location_identifier ':' linear_assertion{
     $2->set_invariant_polyhedron($4);
}
;


location_identifier: identifier{
   // search loclist for the identifier
   Location * what;
   if (!search_location($1, &what)){
      $$=new Location(dimension,f,fd,fm,$1);
      loclist->push_back($$);
   } else
      $$=what;
}
;

transition_identifier: identifier{
      // search loclist for the identifier
   TransitionRelation * what;
   if (!search_transition_relation($1, &what)){
      $$=new TransitionRelation(dimension,f,fd,fm,$1);
      trlist->push_back($$);
   } else {
      cout<<"Error: Already Encountered transition name #"<<what<<$1;
      $$=what;
   }
};

linear_assertion: linear_inequality linear_assertion{
   $$=$2;
   //$$->add_constraint_and_minimize(*$1);
   $$->add_constraint(*$1);
   delete($1);
}
| linear_inequality{
   $$= new C_Polyhedron(dimension, UNIVERSE);
   //$$->add_constraint_and_minimize(*$1);
   $$->add_constraint(*$1);
   delete($1);
};

linear_inequality:  linear_expression LEQ linear_expression{
   $$=new Constraint(*$1 <= *$3);
   delete($1);
   delete($3);
}
|  linear_expression GEQ linear_expression{
   $$=new Constraint(*$1 >= *$3);
   delete($1);
   delete($3);
}
|  linear_expression EQ linear_expression{
   $$=new Constraint(*$1 == *$3);
   delete($1);
   delete($3);
   };

linear_term: identifier {
   int i =f->search($1);
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ $1 + string(" not found");
      yyerror(x);
      exit(1);
   }
   $$=new Linear_Expression(Variable(i));
}
| INT {
   $$= new Linear_Expression($1);
}
| INT '*' identifier{
   int i =f->search($3);
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ $3 + string(" not found");
      yyerror(x);
      exit(1);
   }
   $$=new Linear_Expression($1 * Variable(i));
};

linear_expression: linear_term{
   $$=$1;
}
| linear_expression '+' linear_term {
   $$=$1;
   (*$1)+=(*$3);
   delete($3);
   
}
| linear_expression '-' linear_term {
   $$=$1;
   (*$1)-=(*$3);
   delete($3);
}
| '-' linear_term %prec UMINUS{
   $$=$2;
   (*$2)=-(*$2);
}
;

primed_linear_assertion: primed_linear_inequality primed_linear_assertion{
   $$=$2;
   //$$->add_constraint_and_minimize(*$1);
   $$->add_constraint(*$1);
   delete($1);
}
| primed_linear_inequality{
   $$= new C_Polyhedron(2*dimension,UNIVERSE);
   //$$->add_constraint_and_minimize(*$1);
   $$->add_constraint(*$1);
   delete($1);
}
| preservative{
   $$=$1;
}
| preservative primed_linear_assertion{
   $$=$2;
   $$->intersection_assign(*$1);
   delete($1);
}
;

preservative: PRES '[' variable_list ']'{
   $$= new C_Polyhedron(2*dimension,UNIVERSE);
   vector<int>::iterator vi=$3->begin();
   for (; vi < $3->end(); ++vi){
      Linear_Expression ll=Variable((*vi)) - Variable((*vi)+dimension);
      //$$->add_constraint_and_minimize(ll ==0);
      $$->add_constraint(ll ==0);
   }

   delete($3);
   
}
;

variable_list: identifier variable_list {
   int i=find_variable($1);
   $$=$2;
   $$->push_back(i);
}
| identifier ',' variable_list {
   int i=find_variable($1);
   $$=$3;
   $$->push_back(i);
}
| identifier{
   int i=find_variable($1);
   $$=new vector<int>();
   $$->push_back(i);
}
;
primed_linear_inequality: primed_linear_expression LEQ primed_linear_expression{
   $$=new Constraint(*$1 <= *$3);
   delete($1);
   delete($3);
}
| primed_linear_expression EQ primed_linear_expression {
   $$=new Constraint(*$1== *$3);
   delete($1);
   delete($3);
}
| primed_linear_expression GEQ primed_linear_expression {
   $$= new Constraint(*$1 >= *$3);
   delete($1);
   delete($3);
};

primed_term: identifier {
   int i= find_variable($1);
   $$=new Linear_Expression(Variable(i));
}
| PRIME identifier{
   int i= find_variable($2);
   $$=new Linear_Expression(Variable(i+dimension));
}
| INT {
   $$=new Linear_Expression($1);
}
| INT '*' identifier{
   int i= find_variable($3);
   $$=new Linear_Expression($1 * Variable(i));
}
| INT '*' PRIME identifier{
   int i= find_variable($4);
   $$=new Linear_Expression($1 * Variable(i+dimension));
};

primed_linear_expression: primed_term{
   $$=$1;
}
| primed_linear_expression '+' primed_term{
   $$=$1;
   (*$1)+= (*$3);
   delete($3);
}

| primed_linear_expression '-' primed_term {
   $$=$1;
   (*$1)-= (*$3);
   delete($3);
}
| '-' primed_term %prec UMINUS{
   $$=$2;
   (*$2)= -(*$2);
}
;

identifier: IDENT{
  strcpy($$,$1);
}
;


%%

void do_some_propagation(){
   // try and fire each transition relation

   
   vector<TransitionRelation*>::iterator vi;
   int fired_up=0;
   int ntrans=trlist->size();


   while (fired_up < prop_steps * ntrans){
      for (vi=trlist->begin();vi < trlist->end(); vi++){
         (*vi)->fire();
         fired_up++;
      }
   }

}

int find_variable(char * what){
   int i=f->search(what);
   if (i==VAR_NOT_FOUND){
      string x=string("Error:: Variable ")+ what + string(" not found");
      yyerror(x);
      exit(1);
   }

   return i;
}

void parseinit(){
   weave_count=bang_count=0;
   linenum=0;
   inv_check=false;
   clump_prune_count=prune_count=0;
   context_count=0;
   fm=new var_info();
   fd=new var_info();
   loclist= new vector<Location *>();
   trlist=new vector<TransitionRelation *>();
   num_context=2;
   gendrop=false;
   global_sub_system_list=new vector<System *> ();
   zero=one=true;
   prop_steps=2;
   weave_time=360000;
   ch79=true;
   bhrz03=true;
   dual=false;
}

bool search_location( char * name, Location ** what){
   vector<Location*>::iterator vi;
   string nstr(name);
   for(vi=loclist->begin();vi< loclist->end();vi++){
      if ((*vi)->matches(nstr)){
         *what=(*vi);
         return true;
      }
   }

   return false;
}


bool search_transition_relation( char * name, TransitionRelation ** what){
   vector<TransitionRelation*>::iterator vi;
   string nstr(name);
   for(vi=trlist->begin();vi< trlist->end();vi++){
      if ((*vi)->matches(nstr)){
         *what=(*vi);
         return true;
      }
   }
   
   return false;
}

void yyerror(char const * x){
   yyerror(string(x));
}

void yyerror(string const & x){

   cerr<<x<<endl;
   cerr<<"Line number::"<<linenum<<endl;
   exit(1);
   
}

int parse_cmd_line(char * x){
   
   if (strcmp(x,"one")==0) return ONECONTEXT;
   if (strcmp(x,"many")==0) return MANYCONTEXT;
   if (strcmp(x,"gendrop")==0) return GENDROP;
   if (strcmp(x,"zero_only")==0) return ZERO_ONLY;
   if (strcmp(x,"one_only")==0) return ONE_ONLY;
   if (strcmp(x,"zero_one")==0) return ZERO_ONE;
   if (strcmp(x,"noinst")==0) return NO_INSTANTIATION;
   if (strcmp(x,"noch79")==0) return NO_CH79;
   if (strcmp(x,"nobhrz03")==0) return NO_BHRZ03;
   if (strcmp(x,"ch79")==0) return YES_CH79;
   if (strcmp(x,"bhrz03")==0) return YES_BHRZ03;
   if (strcmp(x,"invcheck")==0) return INV_CHECK;
   if (strcmp(x,"noinvcheck")==0) return NO_INV_CHECK;
   
  
   
   return BULLSHIT;
}

void collect_invariants(C_Polyhedron & cpoly, C_Polyhedron & invd){

   /*
    *  Collect invariants
    */
   
   vector<Location * >::iterator vl;
   
   invd=C_Polyhedron(fd->get_dimension(),UNIVERSE);

   for (vl=loclist->begin();vl<loclist->end();vl++){
      (*vl)->extract_invariants_and_update(cpoly,invd);
   }

   return;

}


void prune_clumps(vector<Clump>& vcl){
   
   C_Polyhedron pp(fd->get_dimension(),UNIVERSE);

   vector<Clump>::iterator vi;
   vector<Location *>::iterator vl;
   
   for (vl=loclist->begin(); vl < loclist->end(); vl++){
      pp=C_Polyhedron(fd->get_dimension(),UNIVERSE);
      (*vl)->update_dual_constraints(pp);
      
      for (vi=vcl.begin();vi < vcl.end();vi++)
         (*vi).prune(pp);
      
   }
      
}


void dfs_traverse_recursive(int depth, vector<Clump> & vcl, C_Polyhedron & cpoly, C_Polyhedron & invd){
   
   
   if (invd.contains(cpoly)){
      bang_count++;
      return;
   }
   
   if (depth==0){
      weave_count++;
      collect_invariants(cpoly,invd);
      //    prune_clumps(vcl);
      return;
   }

   if (weave_timer.compute_time_elapsed() >= weave_time){
      cout<< "Time is up!"<<endl;
      return;
   }
   
   vcl[depth-1].clear();
   while(vcl[depth-1].has_next()){
      
      C_Polyhedron p(cpoly);

      p.intersection_assign(vcl[depth-1].get_reference());

      dfs_traverse_recursive(depth-1,vcl,p,invd);

      vcl[depth-1].next();
   }

   return;
  
   
}

void dfs_traverse(vector<Clump> & vcl, C_Polyhedron & initp){
   // first find out the number of clumps
   // a polyhedron containing the solutions contained to date
   // initiate a dfs traversal.
   // write an invariant extraction function at depth 0

   C_Polyhedron  invd(*trivial);
   int ncl=0;
   vector<Clump>::iterator vi;
   for (vi=vcl.begin();vi < vcl.end();vi++){
      ncl++;
      (*vi).clear();
   }

   weave_timer.restart();
  
   dfs_traverse_recursive(ncl,vcl,initp,invd);
   
}


int main(int argc, char * argv[]){
   // measure total time
   Timer total_time;
   
   parseinit();

   if (argc<=1){
      // by default one context and no gendrop
      num_context=2;
      gendrop=false;
   } else {
      for (int k=1;k<argc;k++){
         switch(parse_cmd_line(argv[k])){
            case GENDROP:
               gendrop=true;
               break;
            case ONECONTEXT:
               num_context=1;
               break;
            case MANYCONTEXT:
               num_context=2;
               break;
            case RESIDUAL_TR_SYS:
               num_context=3;
               break;
            case ZERO_ONLY:
               one=false;
               zero=true;
               break;
            case ONE_ONLY:
               one=true;
               zero=false;
               break;
            case ZERO_ONE:
               zero=one=true;
               break;

            case NO_INSTANTIATION:
               zero=one=false;
               break;
            case NO_CH79:
               ch79=false;
               break;
            case YES_CH79:
               ch79=true;
               break;

            case NO_BHRZ03:
               bhrz03=false;
               break;
            case YES_BHRZ03:
               bhrz03=true;
               break;

            case NO_DUAL:
               dual=false;
               break;
            case YES_DUAL:
               dual=true;
               break;
            case INV_CHECK:
               inv_check=true;
               break;
            case NO_INV_CHECK:
               inv_check=false;
               break;
            default:
               cerr<<"Illegal option:"<<argv[k]<<" ignored."<<endl;
               cerr<<"Usage:"<<argv[0]<<" [one,many,ch,noch,bhrz03,nobhrz03,invcheck,noinvcheck] [ < input file ] [> output file ] "<<endl;
               break;
         }
      }
   }
   
   
   
   vector<Location *>::iterator vi;
   vector<TransitionRelation *>::iterator vj;
   
   yyparse();

   print_status();

   add_preloc_invariants_to_transitions();
   
   global_system= new System(f,fd,fm);

   
   for (vi=loclist->begin();vi< loclist->end();vi++){
      global_system->add_location((*vi));  
   }

   for (vj=trlist->begin();vj< trlist->end();vj++){
      global_system->add_transition((*vj));
   }

   global_system->compute_duals();
   
   tt= new int[fm->get_dimension()];

   //
   // start a timer
   //

   Timer my_time;
   
   
   if (num_context==1){
      
      glc=global_system->get_context();

      glc->simplify_repeat();
      
      
      int ndd=fd->get_dimension();
      
      trivial=new C_Polyhedron(ndd,UNIVERSE);
      
      dualp=new C_Polyhedron(ndd,UNIVERSE);
      
      for (vi=loclist->begin();vi< loclist->end();vi++)
         (*vi)->add_to_trivial(trivial);
      
      invd=new C_Polyhedron(*trivial);

      glc->recursive_strategy(loclist,invd,weave_time,true);

      my_time.stop();
      
   } else if (num_context==2) {
      // manycontexts
      
      // dualize using a clump

      int nd=fd->get_dimension();

      // obtain a polyedron characterizing "trivial"
      
      trivial=new C_Polyhedron(nd,UNIVERSE);

      vector<Location *>::iterator vi;
      for (vi=loclist->begin();vi< loclist->end();vi++)
         (*vi)->add_to_trivial(trivial);

      // now dualize each location
      
      C_Polyhedron initp(nd,UNIVERSE); // for the dualized initial conditions
      cout<<endl;
      cout<<"1."<<endl;
      cout<<"The locations read in are:"<<endl<<endl;
      
      
      for (vi=loclist->begin();vi< loclist->end();vi++){
         cout<<*(*vi)<<endl;
         (*vi)->make_context();
         cout<<"Dualizing....(in location)"<<endl;
         (*vi)->compute_dual_constraints(initp);
      }

      // now dualize the transition systems and collect the "clumps"

      vector<Clump> vcl;
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"2."<<endl;
      cout<<"The transitions read in are::"<<endl<<endl;
      
      vector<TransitionRelation *>::iterator vj;
      for (vj=trlist->begin();vj< trlist->end();vj++){
         cout<<*(*vj)<<endl;
         cout<<"Dualizing....(in transitionrelation)"<<endl;
         (*vj)->compute_consecution_constraints(vcl,initp);
      }
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"3."<<endl;
      for (vi=loclist->begin();vi< loclist->end();vi++){
         (*vi)->add_clump(vcl);
         // this also should trigger the simplification of the context
      }
      
      // now perform a dfs traversal with clump
      cout<<"----------------------------------------------"<<endl;
      cout<<endl;
      cout<<"4."<<endl;
      dfs_traverse(vcl,initp);
      
      my_time.stop();

      cout<<"strategy ID 2 ending (num_context==2)"<<endl;
      
   } else if (num_context==3){
      //
      // This strategy is no longer useful
      // need to clean this up
      //
      
      glc=global_system->get_context();

            
      cout<<"The populated context is "<<endl;
      cout<<(*glc);
      cout<<endl;

      invd=new C_Polyhedron(fd->get_dimension());
      
      global_system->obtain_trivial_polyhedron(*invd);
      
      glc->recursive_strategy((*global_system), invd);

      // finally print the transition systems generated
      my_time.stop();
   }
   cout<<"----------------------------------------------"<<endl;
   cout<<endl;
   cout<<"5."<<endl;
   cout<<"The locations read in are:"<<endl<<endl;
   vector<Location *>::iterator vl;
   for(vl=loclist->begin();vl< loclist->end();vl++){
      cout<<*(*vl);
   }
   cout<<"----------------------------------------------"<<endl;

   
      
   cout<<" # of Contexts generated ="<<context_count<<endl;
   cout<<" # pruned by inclusion tests = "<<prune_count<<endl;
   cout<<" # of invariants *weav*ed="<<weave_count<<endl;
   cout<<" #  *bang*ed="<<bang_count<<endl;
   cout<<" # Pruned in Cump.cc ="<<clump_prune_count<<endl;
   cout<<" Time Taken (0.01S)="<<my_time.compute_time_elapsed()<<endl;

   if (inv_check)
      check_invariant_ok();
   
   cout<<endl<<endl;
   
   cout<<" Doing Initial Propagation"<<endl;
   Timer prop_timer;
   do_some_propagation();
   prop_timer.stop();

   cout<< "Propagation done -- Time Taken (0.01S):" <<
      prop_timer.compute_time_elapsed()<<endl;
   
   if (dual){
      cout<<"---- Running Cousot-Halbwachs dual propagation/narrowing----"<<endl;
      Timer dual_time;
      
      InvariantMap dualmap(f, *loclist);
      global_system->compute_dual_invariant(dualmap);
      
      dual_time.stop();
      cout<<" Time taken for Dual (0.01 S)"<<dual_time.compute_time_elapsed()<<endl;
      cout<<"--------------------------------------------------------"<<endl;
   }

   InvariantMap h79map(f, *loclist);
      
   if (ch79){
      cout<<"---- Running Cousot-Halbwachs with H79 widening ----"<<endl;
      
      Timer h79_time;
      
   
      
      global_system->compute_invariant_h79(h79map);

      h79_time.stop();
      
      cout<<" Time taken for Cousot-Halbwachs Widening (0.01 S)"<<h79_time.compute_time_elapsed()<<endl;
      
      cout<< " The bake-off results vs. CH79"<<endl;
      print_bake_off(h79map);
      
      if (inv_check){
         cout<<"Checking...."<<endl;
         h79map.check_consecution(trlist);
         cout<<"Done!"<<endl;
      }
      
      cout<<"--------------------------------------------------------"<<endl;
   }
   
   InvariantMap bhrz03map(f, *loclist);
      
   if (bhrz03){
      
      cout<<"---- Running Cousot-Halbwachs with BHRZ03 widening ----"<<endl;
      Timer bhrz03_time;
      
      global_system->compute_invariant(bhrz03map);
      
      bhrz03_time.stop();

      cout<<" Time taken for BHRZ03 (0.01 S)"<<bhrz03_time.compute_time_elapsed()<<endl;

      cout<< " The bake-off results vs. BHRZ03"<<endl;
      print_bake_off(bhrz03map);

      if (inv_check){
         cout<<"Checking...."<<endl;
         bhrz03map.check_consecution(trlist);
         cout<<"Done!"<<endl;
       }
      
      cout<<"--------------------------------------------------------"<<endl;
   }
   
   cout<<" Time taken for the initial propagation (0.01 S)"<<prop_timer.compute_time_elapsed()<<endl;
   cout<<" Time taken for the quantifier elimination (0.01 S)"<<my_time.compute_time_elapsed()<<endl;
   cout<<" Total Time taken (0.01S) "<<total_time.compute_time_elapsed()<<endl;
   
   return 0;
}



void collect_generators(vector<Context *> * children , Generator_System & g){
   vector<Context *>::iterator vk;
    for(vk=children->begin();vk < children->end(); vk++){
       (*vk)->collect_generators(g);
    }
}


void add_preloc_invariants_to_transitions(){
   vector<TransitionRelation *>::iterator vtr;
   for (vtr=trlist->begin(); vtr < trlist->end(); ++vtr){
      (*vtr)->add_preloc_invariant();
   }
   return;
}

void print_status(){

   cout<<"---------------------------------------------------"<<endl;
   cout<<" Local invariants to be generated : "<<zero<<endl;
   cout<<" Increasing invariants to be generated : "<<zero<<endl;
   cout<<" Strategy ID #"<<num_context<<endl;
   cout<<" # of initial propagation steps:"<<prop_steps<<endl;
   cout<<" Weave Time allowed:"<<weave_time<<endl;
   cout<<" Cousot-Halbwachs to be performed:"<<ch79<<endl;
   cout<<" BHRZ03 to be performed:"<<bhrz03<<endl;
   cout<<"----------------------------------------------------"<<endl;
}

void print_bake_off( InvariantMap const & invmap){
   bool disjoint;
   int r2;

   vector<Location *>::iterator vl;
   
   for (vl=loclist->begin(); vl <loclist->end(); vl ++){
      r2=0;
      disjoint=true;
      
      string const & what=(*vl)->get_name();
      C_Polyhedron & loc_inv= (*vl)->invariant_reference();
      C_Polyhedron const & other_inv = invmap(what);
      
      cout<<"Location :"<<what<<" ";
      
      // Am I stronger   
      if (other_inv.contains(loc_inv)){
         r2++; // I am one up
         disjoint=false;
      }
      // Is the other_inv stronger?
      
      if (loc_inv.contains(other_inv)){
            r2--; // h79 is one up
            disjoint=false;
      }

      if (disjoint) {
         cout<<"Disjoint"<<endl;
      } else if (r2 > 0){
         cout<<" + "<<endl;
      } else if (r2 <0 ){
         cout<<" - "<<endl;
      } else if (r2==0){
         cout<<" == "<<endl;
      } else {
         // this is unreachable (or is it? :-)
         cout<<" <<Unknown Relation>>"<<endl;
      }
        
   }
}

void check_invariant_ok(){
   cerr<<" Checking..."<<endl;
   vector<TransitionRelation *>::iterator vi;
   for (vi=trlist->begin(); vi != trlist->end(); ++vi){
      (*vi)->check_map();
   }
   cerr<<"done!"<<endl;
   
}
