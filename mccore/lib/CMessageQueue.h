//                              -*- Mode: C++ -*- 
// CMessageQueue.h
// Copyright � 2000-01 Laboratoire de Biologie Informatique et Th�orique.
// Author           : S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
// Created On       : 
// Last Modified By : Martin Larose
// Last Modified On : Fri Feb  9 11:12:32 2001
// Update Count     : 4
// Status           : Ok.
// 


#ifndef _CMessageQueue_h_
#define _CMessageQueue_h_


#include <iostream.h>
#include <strstream.h>



/**
 * @short Console output facility.
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
 * </pre>
 *
 * @author S�bastien Lemieux <lemieuxs@iro.umontreal.ca>
 */
class CMessageQueue 
{
  /**
   * The stream where the ouput is displayed.
   */
  ostream *mStream;

  /**
   * Verbose level of the message queue.
   */
  int mVerbose;

  /**
   * Verbose level of the last entered message.
   */
  int mCurrentVerbose;

  /**
   * String stream where the messages are kept for further display.
   */
  ostrstream *mOst;

  /**
   * Internal buffer.
   */
  char mBuf[262144];

public:

  // LIFECYCLE ------------------------------------------------------------

  /**
   * Initializes the message queue.
   * @param nStream the stream where the messages are displayed.
   * @param nVerbose the initial verbose level of the message queue.
   */
  CMessageQueue (ostream &nStream, int nVerbose) 
    : mStream (&nStream), mVerbose (nVerbose), mOst (0) { }

  // OPERATORS ------------------------------------------------------------

  /**
   * Changes the verbose level of the future entered messages.
   * @param nNewLevel the level.
   * @return itself.
   */
  CMessageQueue& operator() (int nNewLevel)
  { mCurrentVerbose = nNewLevel; return *this; }

  /**
   * Outputs the messages.
   * @param o the object or type to display.
   * @return itself.
   */
  template< class T >
  CMessageQueue& operator<< (const T &o) { output (o); return *this; }

  /**
   * Modifies the CMessageQueue's stream.
   * @param func the ios manipulator function.
   * @return itself.
   */
  CMessageQueue& operator<< (ios& (*func)(ios&))
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << func;
	*mStream << func;
      }
    return *this;
  }

  /**
   * Modifies the CMessageQueue's stream.
   * @param func the ostream manipulator function.
   * @return itself.
   */
  CMessageQueue& operator<< (ostream& (*func)(ostream&))
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << func;
	*mStream << func;
      }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  /**
   * Sets the verbose level of the message queue.
   * @param nVerbose the new verbose level.
   */
  void SetVerbose (int nVerbose) { mVerbose = nVerbose; }

  /**
   * Gets the messages stored in the stream.
   * @return the message string.
   */
  const char* GetStr ();

  // METHODS --------------------------------------------------------------

  /**
   * Starts recording the messages in the message buffer.
   */
  void Record () { if (mOst) delete mOst;  mOst = new ostrstream; }

  /**
   * Stops recording the messages in the message buffer.
   */
  void Stop () { if (mOst) delete mOst;  mOst = 0; }

  // I/O ------------------------------------------------------------------
  
  /**
   * Outputs a character string to the message queue.
   * @param s the string to display.
   */
  void output (const char *s);

  /**
   * Outputs an object or a type to the message queue.
   * @param o the object to display.
   */
  template< class T >
  void output (const T &o)
  {
    if (mCurrentVerbose <= mVerbose)
      {
	if (mOst)
	  *mOst << o;
	*mStream << o;
      }
  }
};

#endif
