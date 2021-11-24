

#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;
bool bReevaluate = false;
typedef float TO;
typedef float TV;

#include "EZ_EDTIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;


CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL


// User declarations
#line 26 "EZ_EDT.ez"
 

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using json=nlohmann::json;
json jf;
json jo;
using namespace std;
int score = 0;

/* MUTATION */
#define MUTATION_MIN  10
#define MUTATION_MAX  1000*2
#define MUTATION_BIAS 0.8

/* PENALITIES */
#define PENALITY_MANDATORY        1000000
#define PENALITY_STRONG_TEACHERS  50
#define PENALITY_MEDIUM_TEACHERS  10
#define PENALITY_WEAK_TEACHERS    3
#define PENALITY_MEDIUM_STUDENTS  3
#define PENALITY_WEAK_STUDENTS    1

/* EDT */
#define DAYS_PER_WEEK 5

clock_t begin_timer;
clock_t end_timer;
double  duration = 0.0;





// User functions

#line 62 "EZ_EDT.ez"

void init_json(){
    ifstream ifs("projet.json");
    jf = json::parse(ifs);
}

void init_day ( IndividualImpl * genome, int day_idx );
//float count_week_hours ( Genomeclass * s );


/* ==== CHOOSE ONE ==== */


int pick_a_teacher ( void )
{
  return globalRandomGenerator->random(0,10);
}

int pick_a_room ( void )
{
  return globalRandomGenerator->random(0,4);
}

int pick_a_course_type ( void ) 
{ 
return globalRandomGenerator->random(0, 5); 
}

int pick_an_hour ( void ) 
{ 
return globalRandomGenerator->random(0, 4); 
}

int pick_a_day ( void ) 
{ 
  return globalRandomGenerator->random(0, 5); 
}

/* ==== CALENDAR ==== */

void init_hour( IndividualImpl * genome, int day_idx, int hour_idx )
{
    for(int w = 0; w<11; w++)
    {
        genome->days[day_idx].hours[hour_idx].teacher[w] = false;
        genome->days[day_idx].hours[hour_idx].salles[w] = 0;
        genome->days[day_idx].hours[hour_idx].type[w] = 0;
        for(int g = 0; g<8 ;g++ )
        {
            genome->days[day_idx].hours[hour_idx].groupes[w].grp[g] = false;
        }
    }
}

void add_hour_exist(IndividualImpl * genome, int day_idx, int idx)
{
    int room_id    = -1;
    /*PROF*/
    int prof_id = pick_a_teacher();
    /*
      math      0  - 3
      physic    3 -  6
      info      6  - 9
      english   9 - 11
    */

    /* ROOM AND TEACHER*/
    
    if ( prof_id < 3)
    {
        room_id = globalRandomGenerator->random(0,2);
        genome->days[day_idx].hours[idx].teacher[prof_id]=true;
        genome->days[day_idx].hours[idx].salles[prof_id]=room_id;
        genome->days[day_idx].hours[idx].type[prof_id]= 0;
        int i = globalRandomGenerator->random(0,8);
        int k = 0;
        switch (i) 
        {
            case 0 :
                k = globalRandomGenerator->random(1,3);
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i] = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k] = true;
                break;
            case 1:
                if ( globalRandomGenerator->tossCoin() )
                {
                    k = 0;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[i] = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[k] = true;
                }
                else
                {
                    k = 2;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                }
                break;
            case 2:
                k = globalRandomGenerator->random(0,2);
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 3:
                k = 4;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 4:
                k = 3;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 5:
                k = 6;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 6:
                k = 5;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            default :
                break;
        }
    }
    else if(prof_id >2 && prof_id <6)
    {

        int i = globalRandomGenerator->random(0,8);
        room_id = globalRandomGenerator->random(0,3);

        genome->days[day_idx].hours[idx].teacher[prof_id]  = true;
        genome->days[day_idx].hours[idx].salles[prof_id]  = room_id;
        int k = 0;
        switch (i)
        {
            case 0 :
                k = globalRandomGenerator->random(1,3);
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 1:
                if ( globalRandomGenerator->tossCoin() ){
                    k = 0;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                }
                else{
                    k = 2;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                }
                break;
            case 2:
                k = globalRandomGenerator->random(0,2);
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 3:
                k = 4;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 4:
                k = 3;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 5:
                k = 6;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            case 6:
                k = 5;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[k]  = true;
                break;
            default :
                break;

        }
        if ( globalRandomGenerator->tossCoin() )
        {
            genome->days[day_idx].hours[idx].type[prof_id]  = 2;
        }
        else
        {
            genome->days[day_idx].hours[idx].type[prof_id]  = 3;
        }

    }
    else if(prof_id > 5 && prof_id < 9)
    {
        int i = globalRandomGenerator->random(0,8);
        room_id = 3 ;
        genome->days[day_idx].hours[idx].teacher[prof_id]  = true;
        genome->days[day_idx].hours[idx].salles[prof_id]  = room_id;
        genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;

        if ( globalRandomGenerator->tossCoin() )
        {
            genome->days[day_idx].hours[idx].type[prof_id]  = 3;
        }
        else
        {
            genome->days[day_idx].hours[idx].type[prof_id]  = 4;
        }
        

        
    }
    else if(prof_id > 8 && prof_id < 11)
    {
        int i = globalRandomGenerator->random(0,8);
        room_id = 4 ;
        genome->days[day_idx].hours[idx].teacher[prof_id]  = true;
        genome->days[day_idx].hours[idx].salles[prof_id]  = room_id;
        genome->days[day_idx].hours[idx].type[prof_id]  = 4;
        switch (i) 
        {
            case 0 :
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[1]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[2]  = true;
                break;
            case 1:
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[0]  = true;
                    genome->days[day_idx].hours[idx].groupes[prof_id].grp[2]  = true;
                break;
            case 2:
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[1]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[0]  = true;
                break;
            case 3:
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[4]  = true;
                break;
            case 4:
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[3]  = true;
                break;
            case 5:
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[6]  = true;
                break;
            case 6:
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[i]  = true;
                genome->days[day_idx].hours[idx].groupes[prof_id].grp[5]  = true;
                break;
            default :
                break;

        }

    }
}


void init_semaine(IndividualImpl * genome){
    for(int d=0;d<5;d++){
        for(int h=0;h<4;h++){
            init_hour(genome,d,h);
        }
    }
}


/* ==== EVALUTATE AND CHECK CONSTRAINTS ==== */
  
  /* == HOURS == */

int check_hour ( IndividualImpl * g, int day_idx, int hour_idx )
{
    int score = 0;
    // get all week course at the same time
    for ( int d = 0 ; d < 5 ; d++ )
    {
        int same_room_course = 0;
        int same_teacher_in_multiple_rooms = 0;
        for ( int d = 0 ; d < 5 ; d++ )
        {
            for (int h = 0 ; h < 4 ; h++)
            {
                for ( int k = 0 ; k < 5 ; k++ )
                {
                    for (int l = 0 ; l < 5 ; l++ )
                    {
                        if(g->days[d].hours[h].salles[k] == g->days[d].hours[h].salles[l])
                        {
                            same_room_course += 1;
                        }
                        else if(g->days[d].hours[h].teacher[k] == g->days[d].hours[h].teacher[l])
                        {
                            same_teacher_in_multiple_rooms += 1;
                        }
    
                    }
                }
            }
            if ( same_room_course > 5 )
            {
                score += PENALITY_MANDATORY;
            }
            if ( same_teacher_in_multiple_rooms > 5 )
            {
                score += PENALITY_MANDATORY;         
            }
        }
    }

    return score;
}


/* == TEACHERS == */
int check_teacher( const IndividualImpl * g, int days )
{
    int score = 0;
    //Penalité demi journée
    for ( int i = 0 ; i < 11 ; i++ )
    {
    if ((g->days[days].hours[0].teacher[i]) 
        || (g->days[days].hours[1].teacher[i]))
        {
          score += PENALITY_WEAK_TEACHERS;
        }
        if ((g->days[days].hours[1].teacher[i]) 
        || (g->days[days].hours[2].teacher[i]))
        {
          score += PENALITY_WEAK_TEACHERS;
        }     
    }
    //pénalité trou
    for ( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        || (g->days[days].hours[2].teacher[i]))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
        if ((g->days[days].hours[1].teacher[i]) 
        || (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
    }
    //pénalité grand trou
    for ( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        || (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_MEDIUM_TEACHERS;
        }
    } 
    //pénalité journée surchagé
    for ( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        && (g->days[days].hours[1].teacher[i])
        && (g->days[days].hours[2].teacher[i])
        && (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
    }
    //pénalité journée vide
    for( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i])
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i])
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_WEAK_TEACHERS;
        }
    }
    return score;
}
int check_total_prof(IndividualImpl * Genome){
    for ( int i = 0 ; i < 11 ; i++ )
    {
        int nb_heures = 0;
        for ( int d = 0 ; d < 5 ; d++ )
        {
            for (int h = 0 ; h < 4 ; h++)
            {
                if(Genome->days[d].hours[h].teacher[i])
                {
                    nb_heures +=2;
                }
            }
        }
        if (nb_heures < jf["prof"][i]["Restantes"].get<int>())
        {
            score += PENALITY_MANDATORY;
        }
        if (nb_heures > jf["prof"][i]["Restantes"].get<int>())
        {
            score+= jf["prof"][i]["Heuresupp"].get<int>();
        }
    }

    return score;
}

int verifcontraintesprof(IndividualImpl * Genome){
  int total=0;
  for(int d=0;d<5;d++){
    for(int h=0;h<4;h++){
      for(int j=0;j<11;j++){
        if(Genome->days[d].hours[h].teacher[j]){
          total=total + jf["prof"][j]["Contraintes"][0][d]["Heures"][h]["Dispo"].get<int>();
        }
      }
    }
  }
  return total;
}

int verifcontraintessalle(IndividualImpl * Genome){
  int total=0;
  int s = 0;
  for(int d=0;d<5;d++){
    for(int h=0;h<4;h++){
      for(int j=0;j<11;j++){
        if(Genome->days[d].hours[h].teacher[j]){
            s = Genome->days[d].hours[h].salles[j];
            total=total + jf["salle"][s]["Contraintes"][d]["Heures"][h]["Dispo"].get<int>();
        }
      }
    }
  }
  return total;
}

/* STUDENTS */

int check_crenau (IndividualImpl * genome)
{
    int score = 0;
    int res = 0 ;
        for (int g = 0; g < 8 ; g++ )
        {
            for ( int d = 0 ; d < 5 ; d++ )
            {
                for (int h = 0 ; h < 4 ; h++)
                {
                    res = 0;
                    for ( int i = 0 ; i < 11 ; i++ )
                    {
                        if(genome->days[d].hours[h].groupes[i].grp[g] )
                        {
                            res +=1;
                        }
                    }
                }
            }
        }
        if (res > 1)
        {
            score += PENALITY_MANDATORY;
        }
    return score;
}

int check_cours ( const IndividualImpl * g)
{
    int score = 0 ;
    for(int w = 0 ; w < 8; w++ )
    {
        int M = 0;
        int PTD = 0;
        int PTP = 0;
        int ITP = 0;
        int ITD = 0;
        int A = 0 ;
        for ( int i = 0 ; i < 11 ; i++ )
        {
            for ( int d = 0 ; d < 5 ; d++ )
            {
                for (int h = 0 ; h < 4 ; h++)
                {
                    if(g->days[d].hours[h].groupes[i].grp[w])
                    {
                        if (g->days[d].hours[h].type[i] == 0)
                        {
                            M += 2;
                        }
                        if (g->days[d].hours[h].type[i] == 1)
                        {
                            PTD +=2;
                        }
                        if (g->days[d].hours[h].type[i] == 2)
                        {
                            PTP += 2;
                        }
                        if (g->days[d].hours[h].type[i] == 3)
                        {
                            ITD += 2;
                        }
                        if (g->days[d].hours[h].type[i] == 4)
                        {
                            ITP += 2;
                        }
                        if (g->days[d].hours[h].type[i] == 5)
                        {
                            A += 2;
                        }
                    }
                }
            }
        }
        if (M - jf["groupe"][w]["Mrestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
        if (PTD - jf["groupe"][w]["PTDrestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
        if (PTP - jf["groupe"][w]["PTPrestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
        if (ITD - jf["groupe"][w]["ITDestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
        if (ITP - jf["groupe"][w]["ITPrestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
        if (A - jf["groupe"][w]["Arestantes"].get<int>() !=0)
        {
            score += PENALITY_MANDATORY;
        }
    }
    return score;
}

int check_trou(IndividualImpl * g, int days)
{
    int score = 0;
    //Penalité demi journée
    for ( int i = 0 ; i < 11 ; i++ )
    {
    if ((g->days[days].hours[0].teacher[i]) 
        || (g->days[days].hours[1].teacher[i]))
        {
          score += PENALITY_WEAK_STUDENTS;
        }
        if ((g->days[days].hours[1].teacher[i]) 
        || (g->days[days].hours[2].teacher[i]))
        {
          score += PENALITY_WEAK_STUDENTS;
        }     
    }
    //pénalité grand trou
    for ( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        || (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_MEDIUM_STUDENTS;
        }
    } 
    //pénalité journée surchagé
    for ( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        && (g->days[days].hours[1].teacher[i])
        && (g->days[days].hours[2].teacher[i])
        && (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_WEAK_STUDENTS;
        }
    }
    //pénalité journée vide
    for( int i = 0 ; i < 11 ; i++ )
    {
        if ((g->days[days].hours[0].teacher[i]) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_STUDENTS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i])
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_STUDENTS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i])
        && (g->days[days].hours[3].teacher[i]==false))
        {
            score += PENALITY_WEAK_STUDENTS;
        }
        if ((g->days[days].hours[0].teacher[i]==false) 
        && (g->days[days].hours[1].teacher[i]==false)
        && (g->days[days].hours[2].teacher[i]==false)
        && (g->days[days].hours[3].teacher[i]))
        {
            score += PENALITY_WEAK_STUDENTS;
        }
    }
    return score ;
}

void easeatojson(IndividualImpl * Genome){
  std::string heure;
  int a;
  int b;
  for(int i=0;i<5;i++){
    for(int h=0;h<4;h++){
      a=0;
      switch(h){
        case(0):
          heure="EARLY_MORNING";
          break;
        case(1):
          heure="LATE_MORNING";
          break;
        case(2):
          heure="EARLY_AFTERNOON";
          break;
        case(3):
          heure="LATE_AFTERNOON";
          break;
      }
      for(int j=0;j<11;j++){
        if(Genome->days[i].hours[h].teacher[j]){
          b=0;
          jo["days"][i][heure][a]["Prof"] = jf["prof"][j]["ID"].get<std::string>();
          jo["days"][i][heure][a]["Matiere"]= jf["prof"][j]["Matiere"].get<std::string>();
          jo["days"][i][heure][a]["Type"] = Genome->days[i].hours[h].type[j];
          jo["days"][i][heure][a]["Salle"] = Genome->days[i].hours[h].salles[j];
          for(int g=0;g<8;g++){
            if(Genome->days[i].hours[h].groupes[j].grp[g]){
              jo["days"][i][heure][a]["Groupes"][b] = jf["groupe"][g]["nom"].get<std::string>();
              b++;
            }
          }
          a++;
        }
      }
    }
  }
  ofstream file("output.json");
  file << setw(4) << jo << endl ;
}

/* ==== CROSSOVER ==== */

int count_week_hours ( IndividualImpl *s )
{
    int hours = 0;
    for ( int days = 0 ; days < 5 ; days++ )
    {
        for ( int hours = 0 ; hours < 4 ; hours++ )
        {
            for (int t = 0 ; t<11; t++)
            {
                if ( s->days[days].hours[hours].teacher[t]  )
                {
                    hours += 2;
                }
            }
        }
    }
    return hours;
}

void cross_day ( IndividualImpl * g, IndividualImpl * p1, IndividualImpl * p2)
    {
        for ( int d = 0 ; d < 5 ; d++ )
        {
            if(globalRandomGenerator->tossCoin()){
                g->days[d]=p1->days[d];
            }
            else{
                g->days[d]=p2->days[d];
            }
        }
    }



void cross_hour ( IndividualImpl * g, IndividualImpl * p1, IndividualImpl * p2)
{
    for (int d = 0; d <5; d++){
    for ( int h = 0 ; h < 4 ; h++ )
      {
        if(globalRandomGenerator->tossCoin()){
            g->days[d].hours[h]=p1->days[d].hours[h];
        }
        else{
            g->days[d].hours[h]=p2->days[d].hours[h];
        }
      }
    }
}
/* MUTATIONS */

void mutate_hour ( IndividualImpl * g )
{
    int days      = globalRandomGenerator->random(0, 5);
    int hours     = globalRandomGenerator->random(0, 4);
    int i = globalRandomGenerator->random(0,10);
    init_hour(g, days, hours);
    for(int j=0;j<i;j++)
    {
        add_hour_exist(g,days,hours);
    }
    
}



// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 812 "EZ_EDT.ez"

  init_json();
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 816 "EZ_EDT.ez"

}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void EZ_EDTInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void EZ_EDTFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 971 "EZ_EDT.ez"
{
#line 819 "EZ_EDT.ez"

// cout<<"(DEB) FITNESS : "<<bBest->evaluate()<<endl;
}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

// cout<<"(FIN) FITNESS : "<<bBest->evaluate()<<endl;
}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

//cout << "At each generation before replacement function called" << endl;
}
}


IndividualImpl::IndividualImpl() : CIndividual() {
   
  // Genome Initialiser
#line 863 "EZ_EDT.ez"

  /* init N empty calendar */
IndividualImpl (*this);
init_semaine(&(*this));
for(int d=0;d<5;d++)
{
    for(int h=0;h<4;h++)
    {
        init_hour(&(*this), d, h);
        int i = globalRandomGenerator->random(0,10);
        for(int j=0;j<i;j++)
        {
            add_hour_exist(&(*this),d,h);
        }
    }
}

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 908 "EZ_EDT.ez"
 // retourne le score
int score = 0;


// Application des contraintes
/* days */

for ( int days = 0 ; days < 5 ; days++ )
{
    score += check_teacher(&(*this), days);
    score += check_trou(&(*this), days);

    /* hours */
    for ( int hours = 0 ; hours < 4 ; hours++ )
    {
        score += check_hour(&(*this), days, hours);
    }
}

/* TEACHERS STUDENTS */
score += check_total_prof(&(*this));
score += check_crenau(&(*this)) ;
score += check_cours(&(*this));
score += verifcontraintessalle(&(*this));
score += verifcontraintesprof(&(*this));

easeatojson(&(*this));
return fitness =  score;


  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.

}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	for(int EASEA_Ndx=0; EASEA_Ndx<5; EASEA_Ndx++)
		EASEA_Line << this->days[EASEA_Ndx].serializer() <<" ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	for(int EASEA_Ndx=0; EASEA_Ndx<5; EASEA_Ndx++)
		this->days[EASEA_Ndx].deserializer(&EASEA_Line);

    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    {for(int EASEA_Ndx=0; EASEA_Ndx<5; EASEA_Ndx++)
       days[EASEA_Ndx]=genome.days[EASEA_Ndx];}



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 884 "EZ_EDT.ez"



    if( globalRandomGenerator->tossCoin() )
    {
        cross_day(&child, &parent1, &parent2);
    }
    else
    {
        cross_hour(&child, &parent1, &parent2);
    }




	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


void IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 898 "EZ_EDT.ez"


  for ( int i = 0 ; i < globalRandomGenerator->random(MUTATION_MIN, MUTATION_MAX) ; i++ )
  {
    mutate_hour(&(*this));
  }


}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = true;
	this->nbGen = setVariable("nbGen",(int)1000);
	this->nbCPUThreads = setVariable("nbCPUThreads", 1);
	this->reevaluateImmigrants = setVariable("reevaluateImmigrants", 0);

	omp_set_num_threads(this->nbCPUThreads);
	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)1000.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)1000.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)1000.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)1000.000000);
	pCrossover = 0.750000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)100);
	offspringPopulationSize = setVariable("nbOffspring",(int)40);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)0.900000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)0.900000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)1);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)1000));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",0);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",0);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",1);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"EZ_EDT";
	this->plotOutputFilename = (char*)"EZ_EDT.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",0);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.000000);
    this->serverPort = setVariable("serverPort",0);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",1000);
	EZ_current_generation=0;
  EZ_POP_SIZE = parentPopulationSize;
  OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("EZ_EDT.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}

