#include "Row.h"
#include "Field.h"

Row::Row(const std::vector<Field>& aFields)
	:mFields(aFields)
{
}

/*
	return all fields of a Row as a vector<Field>
*/
const std::vector<Field> Row::GetFields() const
{
	return mFields;
}
