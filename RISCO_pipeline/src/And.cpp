#include "And.h"

void And::and_orProcess(){
	result = e1.read() & e2.read();
}