#include "VarManager.h"

VarManager::VarManager(bool expandable, int size) : memory(new Memory(expandable, size)){};