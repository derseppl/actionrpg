#include "../01_includes/debug.h"
using namespace arpg ;
using namespace std ;

arpg::Debug::Debug()
{
	// bei jeder Erstellung eines Debug-Objekts wird der Zähler hinaufgezählt
	anzMessage++ ;
}

void arpg::Debug::message(string msg)
{
	cout << "[DEBUG " << anzMessage  << "] " << msg << endl ;
}

// Debug-Message Zähler zurücksetzen
int arpg::Debug::anzMessage = 0 ;
