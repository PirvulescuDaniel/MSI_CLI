#pragma once
#include "pch.h"

class Condition
{
public:
	Condition(const std::string& aLeftArgument,
			  const std::string& aComparator,
			  const std::string& aRightArgument);

	const std::string& GetLeftArgument() const;
	const std::string& GetRightArgument() const;
	const std::string& GetComparator() const;

	bool operator == (const Condition aCondition) const ;

private:
	std::string mLeftArgument;
	std::string mRightArgument;
	std::string mComparator;

};
