//                              -*- Mode: C++ -*- 
// CMessageQueue.h
// Copyright � 2000 Laboratoire de Biologie Informatique et Th�orique.
// Author           : S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Tue Oct 24 11:14:47 2000
// Update Count     : 1
// Status           : Ok.
// 


#ifndef _CMessageQueue_h_
#define _CMessageQueue_h_


#include <iostream.h>
#include <strstream.h>



/**
 * @short 
 *
 * Version plus flexible de 'cout' pour g�rer le niveau de verbose.
 * Un objet global est cr�� dans McCore (gOut) et est utilis� de la
 * fa�on suivante:  gOut(2) << "error!" << endl;
 * Indique une erreur de niveau 2.  S�mantique des niveaux:
 * <pre>
 *   0 : Doit �tre affich� � tout prix (silent).
 *   1 : Erreur importante pouvant compromettre l'int�grit� des
 *       r�sultats � venir. (normal)
 *   2 : Avertissement de toute forme.  Erreur de s�mantique
 *       potentielles. (debug)
 *   3 : Toute traces disponibles.  (verbose)
 *
 * @author S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CMessageQueue 
{
  ostream *mStream;
  int mVerbose;
  int mCurrentVerbose;
  ostrstream *mOst;
  char mBuf[262144];

public:

  // LIFECYCLE ------------------------------------------------------------

  CMessageQueue (ostream &nStream, int nVerbose) 
    : mStream (&nStream), mVerbose (nVerbose) { mOst = 0; }

  // OPERATORS ------------------------------------------------------------

  CMessageQueue& operator() (int nNewLevel)
  { mCurrentVerbose = nNewLevel; return *this; }

  template< class T >
  CMessageQueue& operator<< (const T &o)
  { return output (o); }

  // ACCESS ---------------------------------------------------------------

  void SetVerbose (int nVerbose) { mVerbose = nVerbose; }
  const char* GetStr ();
  void Record () { if (mOst) delete mOst;  mOst = new ostrstream; }
  void Stop () { if (mOst) delete mOst;  mOst = 0; }

  // METHODS --------------------------------------------------------------

  CMessageQueue& output (const char *s);

  template< class T >
  CMessageQueue& output (const T &o)
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << o;
	*mStream << o;
      }
    return *this;
  }
};

#endif
