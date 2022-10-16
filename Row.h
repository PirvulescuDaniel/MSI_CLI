#pragma once
#include "Field.h"

class Row
{
public:
	Row() = default;
	Row(const std::vector<Field>& aFields);

	const std::vector<Field> GetFields() const;

private:
	std::vector<Field> mFields;

};