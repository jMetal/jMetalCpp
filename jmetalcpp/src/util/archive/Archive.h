/**
 * @file Archive.h
 * @author Esteban López
 * @version 1.0
 * @date 13 December 2011
 */

#ifndef __ARCHIVE__
#define __ARCHIVE__

#include <SolutionSet.h>

/**
 * This class represents the super class for archive objects.
 */
class Archive : public SolutionSet {

public:
  Archive(int size);

};


#endif
