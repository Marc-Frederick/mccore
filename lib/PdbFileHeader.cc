//                              -*- Mode: C++ -*- 
// PdbFileHeader.cc
// Copyright � 2003-06 Laboratoire de Biologie Informatique et Th�orique
//                     Universit� de Montr�al
// Author           : Patrick Gendron
// Created On       : Tue Mar 11 18:45:58 2003
// $Revision: 1.13 $
// $Id: PdbFileHeader.cc,v 1.13 2006-11-15 19:44:45 larosem Exp $
// 
// This file is part of mccore.
// 
// mccore is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// mccore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with mccore; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


// cmake generated defines
#include <config.h>

#include <stdlib.h>
#include <time.h>
#include <sstream>

#include "Pdbstream.h"
#include "Binstream.h"
#include "Exception.h"
#include "Messagestream.h"
#include "PdbFileHeader.h"


namespace mccore
{
  const size_t PdbFileHeader::linelength = 70;

  const string PdbFileHeader::ElectronDiffraction = "ELECTRON DIFFRACTION";
  const string PdbFileHeader::FiberDiffraction = "FIBER DIFFRACTION";
  const string PdbFileHeader::FluorescenceTransfer = "FLUORESCENCE TRANSFER";
  const string PdbFileHeader::NeutronDiffraction = "NEUTRON DIFFRACTION";
  const string PdbFileHeader::NMR = "NMR";
  const string PdbFileHeader::TheoreticalModel = "THEORETICAL MODEL";
  const string PdbFileHeader::XRayDiffraction = "X-RAY DIFFRACTION";

  // LIFECYCLE ------------------------------------------------------------

  PdbFileHeader::PdbFileHeader (bool reset)
  {
    clear (reset);
  }


  PdbFileHeader::PdbFileHeader (const PdbFileHeader &other) 
    : classification (other.classification),
      date (other.date),
      pdbId (other.pdbId),
      title (other.title),
      methods (other.methods),
      authors (other.authors),
      resolution (other.resolution),
      remarks (other.remarks),
      unclassified (other.unclassified)
  {

  }

  // OPERATORS ------------------------------------------------------------

  PdbFileHeader&
  PdbFileHeader::operator= (const PdbFileHeader &other) 
  {
    if (this != &other) 
    {
      classification = other.classification;
      date = other.date;
      pdbId = other.pdbId;
      title = other.title;
      methods = other.methods;
      authors = other.authors;
      resolution = other.resolution;
      remarks = other.remarks;
      unclassified = other.unclassified;
    }
    return *this;
  }

  // ACCESS ---------------------------------------------------------------

  void 
  PdbFileHeader::setClassification (const string &s) 
  { 
    classification = Pdbstream::trim (s);
    classification.resize (40, ' ');
  }


  void PdbFileHeader::setDate () 
  {
    time_t now = time (0);
    
    setDate (localtime (&now)->tm_mday,
	     localtime (&now)->tm_mon + 1,
	     localtime (&now)->tm_year+1900);
  }


  void 
  PdbFileHeader::setDate (unsigned int day, unsigned int month, unsigned int year) 
  {
    ostringstream oss;
    static const char* mnames[13] =  
      { "???", "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };

    // -- validation
    if (day > 31) day = 0;
    if (month > 12) month = 0;
    if (year > 9999) year = 0;

    oss.width (2);
    oss.fill ('0');
    oss << day << "-" << mnames[month]  << "-";
    oss.width (4);
    oss << year;
    date = oss.str ();
  }


  void 
  PdbFileHeader::setDate (const string &s) 
  { 
    date = Pdbstream::trim (s);
    date.resize (11, ' ');
  }


  void 
  PdbFileHeader::setPdbId (const string &s) 
  { 
    pdbId = Pdbstream::trim (s);
    pdbId.resize (4, ' ');
  }


  void 
  PdbFileHeader::setTitle (const string &s)
  { 
    title = s;
  }
   

  void
  PdbFileHeader::setMethods (const map< string, string >& mlist)
  {
//     map< string, string >::const_iterator it;

//     methods.clear ();
//     for (it = mlist.begin (); it != mlist.end (); ++it)
//       addMethod (it->first, it->second);

    methods = mlist;
  }


  void
  PdbFileHeader::setAuthors (const list< string >& alist)
  {
    authors = alist;
  }


  void 
  PdbFileHeader::setResolution (float f)
  {
    resolution = f > 99.94 ? 99.94 : f;
  }


  void
  PdbFileHeader::setUnclassified (const list< string >& ulist)
  {
    unclassified = ulist;
  }

 
  void
  PdbFileHeader::setRemarks (const list< pair< unsigned int, string > >& remlist)
  {
    remarks = remlist;
  }


  void 
  PdbFileHeader::addMethod (const string& n)
  {
    string es;
    addMethod (n, es);
  }


  void 
  PdbFileHeader::addMethod (const string& n, const string& c)
  {
    pair< map< string, string >::iterator, bool > inserted = 
      methods.insert (make_pair (Pdbstream::trim (n), c));

    if (!inserted.second && !c.empty ())
      inserted.first->second += ", " + c;
  }


  void 
  PdbFileHeader::addAuthor (const string& a)
  {
    authors.push_back (a);
  }


  void PdbFileHeader::addUnclassified (const string& str)
  {
    unclassified.push_back (str);
  }


  void
  PdbFileHeader::addRemark (unsigned int no, const string &str)
  {
    remarks.push_back (make_pair (no, str));
  }


  void 
  PdbFileHeader::clear (bool reset)
  {
    title.clear ();
    methods.clear ();
    authors.clear ();
    remarks.clear ();
    unclassified.clear ();
    resolution = -1.0;

    if (reset)
      {
	setClassification ("Unclassified");
	setDate ();
	setPdbId ("Void");
      
	string com = "File generated using ";
	com += PACKAGE_NAME;
	com += " ";
	com += PACKAGE_VERSION_STRING;
	com += " by ";
	const char* cs = getenv ("USER");
	com += 0 == cs ? "anonymous" : cs;
	cs = getenv ("HOST");
	com += "@";
	com += 0 == cs ? "nohost" : cs;
	addUnclassified (com);
      }
    else
      {
	string es;
	setClassification (es);
	setDate (es);
	setPdbId (es);
      }
  }


  ostream& 
  PdbFileHeader::write (ostream& os) const
  {
    map< string, string >::const_iterator psit;
    list< string >::const_iterator sit;
    list< pair< unsigned int, string > >::const_iterator rit;

    os << "Classification: " << classification << endl
       << "PDB ID: " << pdbId <<  endl
       << "Date: " << date <<  endl
       << "Title: " << title << endl
       << "Methods:" << endl;

    for (psit = methods.begin (); psit != methods.end (); ++psit)
      os << "\t- " << psit->first << ", " << psit->second << endl; 
    
    os << "Authors: ";

    for (sit = authors.begin (); sit != authors.end (); ++sit)
      os << *sit << ", ";

    os << endl << "Resolution: " << resolution << endl
       << "Unclassified remarks:" << endl;

    for (sit = unclassified.begin (); sit != unclassified.end (); ++sit)
      os << "\t- " << *sit << endl;

    for (rit = remarks.begin (); remarks.end () != rit; ++rit)
      {
	os << rit->first << "\t" << rit->second << endl;
      }

    return os;
  }

  
  oPdbstream&
  PdbFileHeader::write (oPdbstream& ops) const
  {
    map< string, string >::const_iterator psit;
    list< string >::const_iterator sit;
    list< pair< unsigned int, string > >::const_iterator rit;
    string es, rectext;

    // -- header
    if (!Pdbstream::trim (classification).empty ())
    {
      ops.setf (ios::left, ios::adjustfield);
      ops.width (10);
      //        10               40                  11         1         4       = 66
      ops << "HEADER" << classification << date << ' ' << pdbId;
      ops.width (Pdbstream::LINELENGTH - 66);
      ops << ' ' << endl;
    }

    // -- title
    if (!title.empty ())
      ops.writeRecord ("TITLE", title, PdbFileHeader::linelength);

    // -- methods
    if (!methods.empty ())
    {
      rectext.clear ();
      psit = methods.begin ();

      while (true)
      {
	rectext += psit->first + (psit->second.empty () ? 
				  psit->second : 
				  (psit->second[0] == ' ' ? "," : ", ") + psit->second);

	if (methods.end () == ++psit)
	  break;

	rectext += "; ";
      }

      ops.writeRecord ("EXPDTA", rectext, PdbFileHeader::linelength);
    }

    // -- authors
    if (!authors.empty ())
    {
      rectext.clear ();
      sit = authors.begin ();

      while (true)
      {
	rectext += *sit; 

	if (authors.end () == ++sit)
	  break;

	rectext += sit->empty () || (*sit)[0] == ' ' ? "," : ", ";
      }

      ops.writeRecord ("AUTHOR", rectext, PdbFileHeader::linelength);
    }


    // -- resolution

    ostringstream rs;
    
    rs << "RESOLUTION.";

    if (resolution > 0.0)
    {
      rs.setf (ios::fixed);
      rs.width (5);
      rs.precision (2);
      rs << resolution << " Angstroms.";
    }
    else
      rs << " NOT APPLICABLE.";
    
    ops.writeRemark (rs.str (), 2);

		       
    // -- unclassified remarks
    
    for (sit = unclassified.begin (); sit != unclassified.end (); ++sit)
      ops.writeRemark (*sit, 99);

    for (rit = remarks.begin (); remarks.end () != rit; ++rit)
      {
	ops.writeRemark (rit->second, rit->first);
      }

    return ops;
  }


  oBinstream&
  PdbFileHeader::write (oBinstream& obs) const
  {
    map< string, string >::const_iterator mit;
    list< string >::const_iterator lit;

    obs << classification << date << pdbId << title 
	<< resolution
	<< (mccore::bin_ui64)methods.size ();
    for (mit = methods.begin (); methods.end () != mit; ++mit)
      obs << mit->first << mit->second;
    obs << (mccore::bin_ui64)authors.size ();
    for (lit = authors.begin (); authors.end () != lit; ++lit)
      obs << *lit;
    obs << (mccore::bin_ui64)unclassified.size ();
    for (lit = unclassified.begin (); unclassified.end () != lit; ++lit)
      obs << *lit;
    return obs;
  }


  iPdbstream&
  PdbFileHeader::read (iPdbstream& ips)
  {
    string line, rectype, methodtext, authortext, remtext;
    int remid;
    list< pair< string, int > > remholder;
    list< pair< string, int > >::iterator it;
    istringstream iss;

    clear ();

    //while (getline (ips, line).good ())
    while (!ips.readLine (line).eof ())
    {
      if (ips.fail ())
      {
	IntLibException ex ("read failed", __FILE__, __LINE__);
	throw ex;
      }

      //line.resize (Pdbstream::LINELENGTH, ' ');
      line.resize (PdbFileHeader::linelength, ' ');
      rectype = Pdbstream::trim (line.substr (0, 6));
      
      if (!rectype.empty ())
      {
	if ("HEADER" == rectype)
	{
	  setClassification (line.substr (10, 40));
	  setDate (line.substr (50, 11));
	  setPdbId (line.substr (62, 4));
	}
	else if ("OBSLTE" == rectype)
	{
	  gErr (4) << "skipped OBSLTE record in PDB header" << endl;
	}
	else if ("TITLE" == rectype)
	{
	  title += 
	    (title.empty () ? "" : "\n") + Pdbstream::trim (line.substr (10));
	}
	else if ("CAVEAT" == rectype)
	{
	  gErr (4) << "skipped CAVEAT record in PDB header" << endl;
	}
	else if ("COMPND" == rectype)
	{
	  gErr (4) << "skipped COMPND record in PDB header" << endl;
	}
	else if ("SOURCE" == rectype)
	{
	  gErr (4) << "skipped SOURCE record in PDB header" << endl;
	}
	else if ("KEYWDS" == rectype)
	{
	  gErr (4) << "skipped KEYWDS record in PDB header" << endl;
	}
	else if ("EXPDTA" == rectype)
	{
	  methodtext += 
	    (methodtext.empty () ? "" : "\n") + line.substr (10) + " ";
	}
	else if ("AUTHOR" == rectype)
	{
	  authortext += 
	    (authortext.empty () ? "" : "\n") + line.substr (10) + " ";
	}
	else if ("REVDAT" == rectype)
	{
	  gErr (4) << "skipped REVDAT record in PDB header" << endl;
	}
	else if ("SPRSDE" == rectype)
	{
	  gErr (4) << "skipped SPRSDE record in PDB header" << endl;
	}
	else if ("JRNL" == rectype)
	{
	  gErr (4) << "skipped JRNL record in PDB header" << endl;
	}
	else if ("REMARK" == rectype)
	  {
	    string remline = Pdbstream::trim (line.substr (11, 59));
	    
	    if (remline.empty ()) // new remark
	      {
		if (! remtext.empty ()) // save if not first remark read
		  {
		    remholder.push_back (make_pair (remtext, remid));
		  }

		iss.clear ();
		iss.str (line.substr (7, 3));
		remtext.clear ();
		iss >> remid;
	      }
	    else
	      {
		// concatenate remark line to current remark text (assumed
		// same id)
		string s;

		s = remtext.empty () ? "" : "\n";
		remtext += s + remline;
	      }
	  }
	else
	{
	  ips.unreadLine ();
	  break;
	}
      }
    }

    // -- add last remark (if any read)
    if (!remtext.empty ())
      remholder.push_back (make_pair (remtext, remid));


    // -- parse methods: NAME1, comments1; NAME2, comments2; ...

    string::size_type beg, com_beg, end;

    beg = 0;
    do
    {
      end = methodtext.find_first_of (';', beg);
      if ((com_beg = methodtext.find_first_of (',', beg)) < end)
	addMethod (methodtext.substr (beg, com_beg - beg),
			 methodtext.substr (com_beg + 1, end - com_beg - 1));
      else
	addMethod (methodtext.substr (beg, end - beg));
      beg = end + 1;
    }
    while (string::npos != end);


    // -- parse authors: comma separated list

    beg = 0;
    do
    {
      end = authortext.find_first_of (',', beg);
      addAuthor (Pdbstream::trim (authortext.substr (beg, end - beg)));
      beg = end + 1;
    }
    while (string::npos != end);


    // -- parse remarks by remid (record text starts at column 12)
    //    for now only #2 is handled

    for (it = remholder.begin (); it != remholder.end (); ++it)
      {
	switch (it->second)
	  {
	  case 2: // resolution: 000000000111111111122222222223
	    //             123456789012345678901234567890 
	    // -> record:  REMARK   2 RESOLUTION.xx.xx Angstroms 
	    // -> string:             01234567890123456789
	    //                        00000000001111111111
	    iss.clear ();
	    iss.str (it->first.substr (11, 5));
	    if ((iss >> resolution).fail ())
	      resolution = -1.0;
	    break;

	  default:
	    remarks.push_back (make_pair (it->second, it->first));
	    break;
	  }
      }    
    return ips;
  }


  iBinstream&
  PdbFileHeader::read (iBinstream& ibs)
  {
    mccore::bin_ui64 qty = 0;
    string s1, s2;
    
    clear ();
    ibs >> classification >> date >> pdbId >> title 
	>> resolution;

    for (ibs >> qty; ibs.good () && qty > 0; --qty) 
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

      ibs >> s1 >> s2;
      methods.insert (make_pair (s1, s2));
    }

    qty = 0;
    for (ibs >> qty; ibs.good () && qty > 0; --qty)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

      ibs >> s1;
      authors.push_back (s1);
    }

    qty = 0;
    for (ibs >> qty; ibs.good () && qty > 0; --qty)
    {
      if (!ibs.good ())
      {
	FatalIntLibException ex ("", __FILE__, __LINE__);
	ex << "read failure, " << (unsigned)qty << " to go.";
	throw ex;
      }

      ibs >> s1;
      unclassified.push_back (s1);
    }

    return ibs;
  }


  oPdbstream& 
  operator<< (oPdbstream &ops, const PdbFileHeader& obj)
  {
    return obj.write (ops);
  }


  oBinstream& 
  operator<< (oBinstream &obs, const PdbFileHeader& obj)
  {
    return obj.write (obs);
  }


  iPdbstream& 
  operator>> (iPdbstream& ips, PdbFileHeader& obj)
  {
    return obj.read (ips);
  }


  iBinstream& 
  operator>> (iBinstream &ibs, PdbFileHeader& obj)
  {
    return obj.read (ibs);
  }
}


namespace std
{

  ostream &
  operator<< (ostream &out, const mccore::PdbFileHeader &h)
  {
    return h.write (out);
  }

}
