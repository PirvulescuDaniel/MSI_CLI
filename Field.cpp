#include "Field.h"

Field::Field(const std::string& aName, const std::string& aValue)
	: mName(aName)
	, mValue(aValue)
{
}

/*
	@return the name of the field as a std::string
*/
const std::string& Field::GetName() const
{
	return mName;
}

/*
	@return the value of the field as a std::string
*/
const std::string& Field::GetValue() const
{
	return mValue;
}

/*
	changes the value of the field
*/
void Field::SetValue(const std::string& aValue)
{
	mValue = aValue;
}

bool Field::operator ==(Field aField) const
{
	return ((mName == aField.GetName()) && (mValue == aField.GetValue()));
}
