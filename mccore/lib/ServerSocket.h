//                              -*- Mode: C++ -*- 
// ServerSocket.h
// Copyright � 2001 Laboratoire de Biologie Informatique et Th�orique.
// Author           : Patrick Gendron <gendrop@iro.umontreal.ca>
// Created On       : Tue Apr 24 15:24:51 2001
// Last Modified By : Martin Larose
// Last Modified On : Fri May 11 18:04:22 2001
// Update Count     : 1
// Status           : Unknown.
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



#ifndef _ServerSocket_h_
#define _ServerSocket_h_

#include "sBinstream.h"

#define MAX_QUEUE_LEN 0

/**
 * @short Implementation of a server socket.
 *
 * This class implements a server socket on which we can listen and
 * wait for a connection from a client and returns a socket stream
 * (sBinstream).
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> 
 */
class ServerSocket
{
  int socket_id;

  ServerSocket () {}

public:

  /**
   * Creates a server socket on the specified port.
   */

  ServerSocket (int port);

  /**
   * Destructor.
   */
  ~ServerSocket ();


  /**
   * Listens for a connection to be made and accepts it.  This is a
   * blocking call on the listen(2) function.
   * @return a newly created stream (not destroyed here)
   */
  sBinstream* accept ();

  /**
   * Closes this socket.
   */
  void close ();

};

#endif
