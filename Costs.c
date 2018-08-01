#include "Costs.h"
#include "UserDefine.h"


TRANS_TYPE_ENTRY *getCostForTransType(unsigned int uiTransType)
{
    return &define_type[uiTransType];
}
