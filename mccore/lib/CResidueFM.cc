//                              -*- Mode: C++ -*- 
// CResidueFM.cc
// Copyright � 2001 Laboratoire de Biologie Informatique et Th�orique.
//                  Universit� de Montr�al.
// Author           : Martin Larose <larosem@iro.umontreal.ca>
// Created On       : Fri Oct 12 15:08:48 2001
// Last Modified By : Martin Larose
// Last Modified On : Thu Oct 25 11:18:25 2001
// Update Count     : 2
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



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "CResidue.h"
#include "CResidueFM.h"



AbstractResidue*
CResidueFM::createResidue () const
{
  return new CResidue ();
}