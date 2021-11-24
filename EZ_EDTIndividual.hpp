

#ifndef PROBLEM_DEP_H
#define PROBLEM_DEP_H

//#include "CRandomGenerator.h"
#include <stdlib.h>
#include <iostream>
#include <CIndividual.h>
#include <Parameters.h>
#include <cstring>
#include <sstream>

using namespace std;

class CRandomGenerator;
class CSelectionOperator;
class CGenerationalCriterion;
class CEvolutionaryAlgorithm;
class CPopulation;
class Parameters;

extern int EZ_POP_SIZE;
extern int OFFSPRING_SIZE;

// User classes

class groupe {
public:
// Default methods for class groupe
  groupe(){  // Constructor
  }
  groupe(const groupe &EASEA_Var) {  // Copy constructor
    {for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
       grp[EASEA_Ndx]=EASEA_Var.grp[EASEA_Ndx];}
  }
  virtual ~groupe() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
		EASEA_Line << this->grp[EASEA_Ndx] <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
		(*EASEA_Line) >> this->grp[EASEA_Ndx];
  }
  groupe& operator=(const groupe &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    {for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
       grp[EASEA_Ndx] = EASEA_Var.grp[EASEA_Ndx];}
  return *this;
  }

  bool operator==(groupe &EASEA_Var) const {  // Operator==
    {for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
       if (grp[EASEA_Ndx]!=EASEA_Var.grp[EASEA_Ndx]) return false;}
  return true;
  }

  bool operator!=(groupe &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const groupe& EASEA_Var) { // Output stream insertion operator
    {os << "Array grp : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<8; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.grp[EASEA_Ndx] << "\t";}
    os << "\n";
    return os;
  }

// Class members 
  bool grp[8];
};

class hour {
public:
// Default methods for class hour
  hour(){  // Constructor
  }
  hour(const hour &EASEA_Var) {  // Copy constructor
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       salles[EASEA_Ndx]=EASEA_Var.salles[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       type[EASEA_Ndx]=EASEA_Var.type[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       groupes[EASEA_Ndx]=EASEA_Var.groupes[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       teacher[EASEA_Ndx]=EASEA_Var.teacher[EASEA_Ndx];}
  }
  virtual ~hour() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		EASEA_Line << this->salles[EASEA_Ndx] <<" ";
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		EASEA_Line << this->type[EASEA_Ndx] <<" ";
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		EASEA_Line << this->groupes[EASEA_Ndx].serializer() <<" ";
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		EASEA_Line << this->teacher[EASEA_Ndx] <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		(*EASEA_Line) >> this->salles[EASEA_Ndx];
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		(*EASEA_Line) >> this->type[EASEA_Ndx];
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		this->groupes[EASEA_Ndx].deserializer(EASEA_Line) ;
	for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
		(*EASEA_Line) >> this->teacher[EASEA_Ndx];
  }
  hour& operator=(const hour &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       salles[EASEA_Ndx] = EASEA_Var.salles[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       type[EASEA_Ndx] = EASEA_Var.type[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       groupes[EASEA_Ndx] = EASEA_Var.groupes[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       teacher[EASEA_Ndx] = EASEA_Var.teacher[EASEA_Ndx];}
  return *this;
  }

  bool operator==(hour &EASEA_Var) const {  // Operator==
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       if (salles[EASEA_Ndx]!=EASEA_Var.salles[EASEA_Ndx]) return false;}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       if (type[EASEA_Ndx]!=EASEA_Var.type[EASEA_Ndx]) return false;}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       if (groupes[EASEA_Ndx]!=EASEA_Var.groupes[EASEA_Ndx]) return false;}
    {for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       if (teacher[EASEA_Ndx]!=EASEA_Var.teacher[EASEA_Ndx]) return false;}
  return true;
  }

  bool operator!=(hour &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const hour& EASEA_Var) { // Output stream insertion operator
    {os << "Array salles : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.salles[EASEA_Ndx] << "\t";}
    os << "\n";
    {os << "Array type : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.type[EASEA_Ndx] << "\t";}
    os << "\n";
    {os << "Array groupes : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.groupes[EASEA_Ndx] << "\t";}
    os << "\n";
    {os << "Array teacher : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<11; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.teacher[EASEA_Ndx] << "\t";}
    os << "\n";
    return os;
  }

// Class members 
  int salles[11];
  int type[11];
  groupe groupes[11];
  bool teacher[11];
};

class day {
public:
// Default methods for class day
  day(){  // Constructor
  }
  day(const day &EASEA_Var) {  // Copy constructor
    {for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
       hours[EASEA_Ndx]=EASEA_Var.hours[EASEA_Ndx];}
  }
  virtual ~day() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
		EASEA_Line << this->hours[EASEA_Ndx].serializer() <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
		this->hours[EASEA_Ndx].deserializer(EASEA_Line) ;
  }
  day& operator=(const day &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    {for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
       hours[EASEA_Ndx] = EASEA_Var.hours[EASEA_Ndx];}
  return *this;
  }

  bool operator==(day &EASEA_Var) const {  // Operator==
    {for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
       if (hours[EASEA_Ndx]!=EASEA_Var.hours[EASEA_Ndx]) return false;}
  return true;
  }

  bool operator!=(day &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const day& EASEA_Var) { // Output stream insertion operator
    {os << "Array hours : ";
     for(int EASEA_Ndx=0; EASEA_Ndx<4; EASEA_Ndx++)
       os << "[" << EASEA_Ndx << "]:" << EASEA_Var.hours[EASEA_Ndx] << "\t";}
    os << "\n";
    return os;
  }

// Class members 
  hour hours[4];
};


class IndividualImpl : public CIndividual {

public: // in EZ_EDT the genome is public (for user functions,...)
	// Class members
  	// Class members 
  day days[5];


public:
	IndividualImpl();
	IndividualImpl(const IndividualImpl& indiv);
	virtual ~IndividualImpl();
	float evaluate();
	static unsigned getCrossoverArrity(){ return 2; }
	float getFitness(){ return this->fitness; }
	CIndividual* crossover(CIndividual** p2);
	void printOn(std::ostream& O) const;
	CIndividual* clone();

	void mutate(float pMutationPerGene);

	void boundChecking();      

	string serialize();
	void deserialize(string EASEA_Line);

	friend std::ostream& operator << (std::ostream& O, const IndividualImpl& B) ;
	void initRandomGenerator(CRandomGenerator* rg){ IndividualImpl::rg = rg;}

};


class ParametersImpl : public Parameters {
public:
	void setDefaultParameters(int argc, char** argv);
	CEvolutionaryAlgorithm* newEvolutionaryAlgorithm();
};

/**
 * @TODO ces functions devraient s'appeler weierstrassInit, weierstrassFinal etc... (en gros EZ_EDTFinal dans le tpl).
 *
 */

void EZ_EDTInit(int argc, char** argv);
void EZ_EDTFinal(CPopulation* pop);
void EZ_EDTBeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void EZ_EDTEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void EZ_EDTGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm);


class EvolutionaryAlgorithmImpl: public CEvolutionaryAlgorithm {
public:
	EvolutionaryAlgorithmImpl(Parameters* params);
	virtual ~EvolutionaryAlgorithmImpl();
	void initializeParentPopulation();
};

#endif /* PROBLEM_DEP_H */

