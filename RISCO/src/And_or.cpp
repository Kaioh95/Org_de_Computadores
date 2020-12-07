#include "And_or.h"

void And_or::and_orProcess(){
	condResult = (pcwc.read() & zero.read()) | pcw.read();
}