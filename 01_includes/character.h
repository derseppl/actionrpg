#ifndef CHARACTER_H
#define CHARACTER_H

namespace arpg {

	class Character {
		
		private:
			int x ;
			int y ;
			int moveSpeed ;

		public:
			void moveRight() ;
			void moveLeft() ;
			void moveUp() ;
			void moveDown() ;

	}

}

#endif
