//                              -*- Mode: C++ -*- 
// AtomSet.h
// Copyright � 2003 Laboratoire de Biologie Informatique et Th�orique
//                  Universit� de Montr�al.
// Author           : Patrick Gendron
// Created On       : Thu Mar 13 13:03:07 2003
// Last Modified By : Patrick Gendron
// Last Modified On : Thu Aug 21 19:33:23 2003
// Update Count     : 44
// Status           : Unknown.
// 


#ifndef _AtomSet_h_
#define _AtomSet_h_

#include <iostream>
#include <set>

#include "Atom.h"
#include "AtomType.h"

namespace mccore {

  class AtomType;

  /**
   * @short Base unary function for the atomset.
   *
   * Abstract class for filtering atom sets.  These classes are used in the
   * residues iterators.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSet
  {
  protected:

    static const int ATOMSET_ALL;
    static const int ATOMSET_NOT;
    static const int ATOMSET_AND;
    static const int ATOMSET_OR;
    static const int ATOMSET_SIDECHAIN;
    static const int ATOMSET_BACKBONE;
    static const int ATOMSET_PSE;
    static const int ATOMSET_HYDROGEN;
    static const int ATOMSET_LP;
    static const int ATOMSET_ATOM;

  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSet (const AtomSet &other) {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const = 0;

    /**
     * Destroys the object.
     */
    virtual ~AtomSet () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSet& operator= (const AtomSet &other) { return *this; }

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const = 0;

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const = 0;

  public:

    // I/O  -----------------------------------------------------------------
  
    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const = 0;

    /**
     * Inputs the atom from the binary stream.
     * @param ibs the input binary stream.
     * @param atom the atom to fill.
     * @return the input binary stream used.
     */
    friend iBinstream& operator>> (iBinstream &ibs, AtomSet *&as);

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const = 0;
  };

  /**
   * Ouputs the set to the stream.
   * @param os the output stream.
   * @param as the atomset.
   * @return the used output stream.
   */
  ostream& operator<< (ostream &os, const AtomSet &as);

  /**
   * Outputs the atom to the binary stream.
   * @param obs the output binary stream.
   * @param atom the atom.
   * @return the output binary stream used.
   */
  oBinstream& operator<< (oBinstream &obs, const Atom &atom);
 



  /**
   * @short All atom set unary function.
   *
   * No atoms are filtered.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetAll : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetAll () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAll (const AtomSetAll &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetAll (); }
    
    /**
     * Destroys the object.
     */
    virtual ~AtomSetAll () {
    }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetAll& operator= (const AtomSetAll &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return true; }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_NOT; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };
 



  /**
   * @short Not operator over atomset function objects.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetNot : public AtomSet
  {
    /**
     * The atomset function object.
     */
    AtomSet *op;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetNot () : AtomSet () {}

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetNot (AtomSet *x) 
      : AtomSet (), op(x) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetNot (const AtomSetNot &other) 
      : AtomSet (other), op (other.op->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetNot (op->clone ()); }
    
    /**
     * Destroys the object.
     */
    virtual ~AtomSetNot () {
      delete op;
    }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetNot& operator= (const AtomSetNot &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return ! op->operator() (atom); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_NOT; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short And operator over atomset function objects.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetAnd : public AtomSet
  {
    /**
     * The left atomset function object.
     */
    AtomSet *op1;

    /**
     * The right atomset function object.
     */
    AtomSet *op2;  

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetAnd () : AtomSet () {}

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetAnd (AtomSet *x, AtomSet *y) 
      : AtomSet (), op1(x), op2(y) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAnd (const AtomSetAnd &other) 
      : AtomSet (other), op1 (other.op1->clone ()), op2 (other.op2->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetAnd (op1->clone (), op2->clone ()); }
    
    /**
     * Destroys the object.
     */
    virtual ~AtomSetAnd () {
      delete op1;
      delete op2;
    }
    
    // OPERATORS ------------------------------------------------------------
    
    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetAnd& operator= (const AtomSetAnd &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return op1->operator() (atom) && op2->operator() (atom); }
    
    // METHODS --------------------------------------------------------------
    
  protected: 
    
    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_AND; }
    
  public:
    
    // I/O  -----------------------------------------------------------------
    
    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;
    
    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };
    
    
    
    
  /**
   * @short Or operator over atomset function objects.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetOr : public AtomSet
  {
    /**
     * The left atomset function object.
     */
    AtomSet *op1;
    
    /**
     * The right atomset function object.
     */
    AtomSet *op2;  

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetOr () : AtomSet () {}

  public:

    /**
     * Initializes the object with two functions.
     * @param x the left function object.
     * @param y the right function object.
     */
    AtomSetOr (AtomSet *x, AtomSet *y) 
      : AtomSet (), op1(x), op2(y) {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetOr (const AtomSetOr &other) 
      : AtomSet (other), op1 (other.op1->clone ()), op2 (other.op2->clone ())
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetOr (op1->clone (), op2->clone ()); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetOr () {
      delete op1;
      delete op2;
    }

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetOr& operator= (const AtomSetOr &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return op1->operator() (atom) || op2->operator() (atom); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_OR; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };



  
  /**
   * @short Base atom set unary function.
   *
   * Filters the atoms that are located on the side chain.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetSideChain : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetSideChain () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetSideChain (const AtomSetSideChain &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetSideChain (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetSideChain () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetSideChain& operator= (const AtomSetSideChain &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isSideChain (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_SIDECHAIN; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };



  
  /**
   * @short Backbone atom set unary function.
   *
   * Filters the atoms that are located on the backbone.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetBackbone : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetBackbone () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetBackbone (const AtomSetBackbone &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetBackbone (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetBackbone () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetBackbone& operator= (const AtomSetBackbone &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isBackbone (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_BACKBONE; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short PSE operator over atomset function objects.
   *
   * Filters the atoms that are pseudo atoms (pivots).
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetPSE : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetPSE () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetPSE (const AtomSetPSE &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetPSE (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetPSE () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetPSE& operator= (const AtomSetPSE &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isPseudo (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_PSE; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short LP operator over atomset function objects.
   *
   * Filters the atoms that are LonePairs.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetLP : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetLP () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetLP (const AtomSetLP &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetLP (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetLP () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetLP& operator= (const AtomSetLP &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isLonePair (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_LP; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short Hydrogen operator over atomset function objects.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetHydrogen : public AtomSet
  {
  public:

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object.
     */
    AtomSetHydrogen () : AtomSet () {}

    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetHydrogen (const AtomSetHydrogen &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetHydrogen (); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetHydrogen () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetHydrogen& operator= (const AtomSetHydrogen &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType ()->isHydrogen (); }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_HYDROGEN; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };




  /**
   * @short Atom operator over atomset function objects.
   *
   * @author Martin Larose <larosem@IRO.UMontreal.CA>
   */
  class AtomSetAtom : public AtomSet
  {
    /**
     * The AtomType.
     */
    const AtomType *type;

    // LIFECYCLE ------------------------------------------------------------

    /**
     * Initializes the object. Must not be used.
     */
    AtomSetAtom () : AtomSet () {}

  public:

    /**
     * Initializes the object.
     * @param anAtomType the AtomType.
     */
    AtomSetAtom(const AtomType *anAtomType) {
      type = anAtomType;
    }
    
    /**
     * Initializes the object with the other's content.
     * @param other the object to copy.
     */
    AtomSetAtom (const AtomSetAtom &other) 
      : AtomSet (other)
    {}

    /**
     * Copies the function object.
     * @return a copy of itself.
     */
    virtual AtomSet* clone () const
    { return new AtomSetAtom (type); }
  
    /**
     * Destroys the object.
     */
    virtual ~AtomSetAtom () {}

    // OPERATORS ------------------------------------------------------------

    /**
     * Assigns the object with the other's content.
     * @param other the object to copy.
     * @return itself.
     */
    virtual AtomSetAtom& operator= (const AtomSetAtom &other);

    /**
     * Tests wheter the atom is within the set.
     * @param atom the atom.
     * @return wheter the atom is within the set.
     */
    virtual bool operator() (const Atom &atom) const
    { return atom.getType () == type; }

    // METHODS --------------------------------------------------------------

  protected: 

    /**
     * Gets the set number of the AtomSet.
     * @return the set number.
     */
    virtual const int getSetNumber() const { return AtomSet::ATOMSET_ATOM; }

  public:

    // I/O  -----------------------------------------------------------------

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual ostream& output (ostream &os) const;

    /**
     * Ouputs the set to the stream.
     * @param os the output stream.
     * @return the used output stream.
     */
    virtual oBinstream& output (oBinstream &obs) const;
  };

}

#endif