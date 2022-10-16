#pragma once
#include "Utility.h"
#include "Table.h"

namespace Parser
{
	/*
		@return a Table, after string parsing
	*/
	Table ParseCreateTable(const std::string& aInput);

}