//                              -*- Mode: C++ -*- 
// CHBond.h
// Copyright � 2000-02 Laboratoire de Biologie Informatique et Th�orique.
//                     Universit� de Montr�al.
// Author           : S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Thu Oct 25 11:17:57 2001
// Update Count     : 9
// Status           : Ok.
// 
//  This file is part of mccore.
//  
//  mccore is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  mccore is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with mccore; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef _CHBond_h
#define _CHBond_h

#include <stdlib.h>

class AbstractResidue;
class t_Atom;
class CAtom;
class ostream;


/**
 * @short Describes the H-bond between atoms.
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class HBond
{
protected:
  /**
   * The donor atom type implicated in the bond.
   */
  t_Atom *donor;

  /**
   * The hydrogen type implicated in the bond.
   */
  t_Atom *hydro;

  /**
   * The acceptor type implicated in the bond.
   */
  t_Atom *acceptor;

  /**
   * The lone pair type implicated in the bond.
   */
  t_Atom *lonepair;

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.  Every pointer is set to 0.
   */
  HBond ();

  /**
   * Initializes the object.
   * @param donor the donor atom type.
   * @param hydro the hydrogen type.
   * @param acceptor the acceptor atom type.
   * @param loneair the lonepair implicated.
   */
  HBond (t_Atom *donor, t_Atom *hydro, 
	 t_Atom *acceptor, t_Atom *lonepair);

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  HBond (const HBond &other);

  /**
   * Destructs the object.  Nothing to do.
   */
  virtual ~HBond () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the other's content to the object.
   * @param other the object to copy.
   * @return itself.
   */
  const HBond& operator= (const HBond &other);

  /**
   * Tests the equality between two HBond objects.
   * @param other the object to test.
   * @return the truth value.
   */
  virtual bool operator== (const HBond &other) const;

  t_Atom* getDonor () { return donor; }
  t_Atom* getAcceptor () { return acceptor; }
  t_Atom* getHydro () { return hydro; }
  t_Atom* getLonePair () { return lonepair; }

  /**
   * Outputs the H-bond in human readable format.
   * @param os the output stream.
   * @param theBond the H-bond to display.
   * @return the used output stream.
   */
  friend ostream &operator<< (ostream &os, const HBond &theBond);
};



/**
 * @short Describes the H-bond between atoms in two residues.
 *
 * As I can see, it is implied that the donor is on mResidueA and that the acceptor
 * is on mResidueB. --Pat
 *
 * @author S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CHBond : public HBond
{
  /**
   * The left residue in the bond.
   */
  const AbstractResidue *mResidueA;

  /**
   * The right residue in the bond.
   */
  const AbstractResidue *mResidueB;

  /**
   * The penality associated with the bond.  It is calculated once and then
   * cached in this variable.  Initial value -1.
   */
  mutable float cache_penality;

public:

  /**
   * Parameters (mean, variance, weight, prob H-bond) for each measure.
   */
  
  static const int sNbGauss;
  static const float sProbH[7];
  static const float sWeight[7];
  static const float sMean[7][3];
  static const float sCovarInv[7][3][3];
  static const float sCovarDet[7];

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the object.  Every pointer is set to 0 and the
   * cache_penalty is set to -1.
   */
  CHBond ();

  /**
   * Initializes the object.
   * @param nResidueA the left residue.
   * @param nResidueB the right residue.
   * @param nDonor the donor atom type.
   * @param nHydro the hydrogen type.
   * @param nAcceptor the acceptor atom type.
   * @param nLonePair the lonepair implicated.
   */
  CHBond (const AbstractResidue *nResidueA, const AbstractResidue *nResidueB,
	  t_Atom *nDonor, t_Atom *nHydro, 
	  t_Atom *nAcceptor, t_Atom *nLonePair);

  /**
   * Initializes the object with the other's content.
   * @param other the object to copy.
   */
  CHBond (const CHBond &other);

  /**
   * Destructs the object.  Nothing to do.
   */
  virtual ~CHBond () { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Assigns the other's content to the object.
   * @param other the object to copy.
   * @return itself.
   */
  const CHBond& operator= (const CHBond &other);

  /**
   * Calculates the penalty for the actual H-bond.  The result is cached
   * into cache_penalty.
   */
  operator float () const;
  
  // ACCESS ---------------------------------------------------------------

  /**
   * Sets the CHBond slots.
   * @param nResidueA the left residue.
   * @param nResidueB the right residue.
   * @param nDonor the donor atom type.
   * @param nHydro the hydrogen type.
   * @param nAcceptor the acceptor atom type.
   * @param nLonePair the lonepair implicated.
   */
  void SetHBond (const AbstractResidue *nResidueA,
		 const AbstractResidue *nResidueB,
		 t_Atom *nDonor, t_Atom *nHydro,
		 t_Atom *nAcceptor, t_Atom *nLonePair);
  const AbstractResidue *GetResidueA () const { return mResidueA; }
  const AbstractResidue *GetResidueB () const { return mResidueB; }
  const CAtom &GetDonor (const AbstractResidue *r = NULL) const;
  const CAtom &GetHydrogen (const AbstractResidue *r = NULL) const;
  const CAtom &GetAcceptor (const AbstractResidue *r = NULL) const;
  const CAtom &GetLonePair (const AbstractResidue *r = NULL) const;

  // METHODS --------------------------------------------------------------

  static float Eval (float dist, float angle_h, float angle_l, bool decision = false);

  // I/O  -----------------------------------------------------------------

  /**
   * Outputs the H-bond in Amber restraint format.
   * @param os the output stream.
   */
  void DumpAmberRestraint (ostream &os);

  /**
   * Outputs the H-bond in human readable format.
   * @param os the output stream.
   * @param theBond the H-bond to display.
   * @return the used output stream.
   */
  friend ostream &operator<< (ostream &os, const CHBond &theBond);
};

#endif








