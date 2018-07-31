#include <engine\objectmodel\componentholder.h>

namespace OK
{
    namespace ComponentHolderHelper
    {
        ComponentHolderID GetNextComponentHolderID()
        {
            static ComponentHolderID currentComponentHolderID;
            return ++currentComponentHolderID;
        }
    }
}