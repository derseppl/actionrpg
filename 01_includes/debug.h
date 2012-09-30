#include <iostream>
#include <string>
using namespace std ;

#ifndef DEBUG_H
#define DEBUG_H

namespace arpg {

	class Debug {

		public:
			static int anzMessage;
			void message(string msg) ;
			Debug() ;

	} ;

}

#endif
