#include "Condition.h"
#include "pch.h"

Condition::Condition(
    const std::string& aLeftArgument,
    const std::string& aComparator,
    const std::string& aRightArgument)
    :mLeftArgument(aLeftArgument)
    ,mComparator(aComparator)
    ,mRightArgument(aRightArgument)
{
}

/*
    @return left argument of the condition as std::string
*/
const std::string& Condition::GetLeftArgument() const
{
    return mLeftArgument;
}

/*
    @return right argument of the condition as std::string
*/
const std::string& Condition::GetRightArgument() const
{
    return mRightArgument;
}

/*
    @return the comparator of the condition as std::string
*/
const std::string& Condition::GetComparator() const
{
    return mComparator;
}

bool Condition::operator==(const Condition aCondition) const
{
  return this->mLeftArgument  == aCondition.GetLeftArgument() &&
         this->mComparator    == aCondition.GetComparator()   &&
         this->mRightArgument == aCondition.GetRightArgument();
}
