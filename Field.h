#pragma once
#include "pch.h"

class Field
{

public:
	Field() = default;
	Field(const std::string& aName, const std::string& aValue);

	const std::string& GetName() const;
	const std::string& GetValue() const;

	void SetValue(const std::string& aValue);

private:
	std::string mName;
	std::string mValue;

};