#include "Basic.h"

int Basic::End()
{
    if (ErrorCall()) return 1;

    return SuccessCall();
}

int Basic::ErrorCall()
{
    if (error.isExists())
    {
        error.Print();
        return 1;
    }
    return 0;
}

int Basic::SuccessCall()
{
    return 0;
}