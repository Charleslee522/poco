//
// ODBCColumn.h
//
// $Id: //poco/1.3/Data/ODBC/include/Poco/Data/ODBC/ODBCColumn.h#2 $
//
// Library: ODBC
// Package: ODBC
// Module:  ODBCColumn
//
// Definition of ODBCColumn.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef ODBC_ODBCColumn_INCLUDED
#define ODBC_ODBCColumn_INCLUDED


#include "Poco/Data/ODBC/ODBC.h"
#include "Poco/Data/ODBC/Error.h"
#include "Poco/Data/ODBC/Handle.h"
#include "Poco/Data/ODBC/ODBCException.h"
#include "Poco/Data/MetaColumn.h"
#ifdef POCO_OS_FAMILY_WINDOWS
#include <windows.h>
#endif
#include <sqlext.h>


namespace Poco {
namespace Data {
namespace ODBC {


class ODBC_API ODBCColumn: public MetaColumn
{
public:
	explicit ODBCColumn(const StatementHandle& rStmt, std::size_t position);
		/// Creates the ODBCColumn.
		
	~ODBCColumn();
		/// Destroys the ODBCColumn.

	std::size_t dataLength() const;
		/// A numeric value that is either the maximum or actual character length of a character 
		/// string or binary data type. It is the maximum character length for a fixed-length data type, 
		/// or the actual character length for a variable-length data type. Its value always excludes the 
		/// null-termination byte that ends the character string. 
		/// This information is returned from the SQL_DESC_LENGTH record field of the IRD.

private:
	ODBCColumn();

	static const int NAME_BUFFER_LENGTH = 2048;

	struct ColumnDescription
	{
		POCO_SQLCHAR name[NAME_BUFFER_LENGTH];
		SQLSMALLINT  nameBufferLength;
		SQLSMALLINT  dataType;
		SQLULEN      size;
		SQLSMALLINT  decimalDigits;
		SQLSMALLINT  isNullable;
	};

	void init();
	void getDescription();

	SQLLEN                 _dataLength;
	const StatementHandle& _rStmt;
	ColumnDescription      _columnDesc;
};


///
/// inlines
///
inline std::size_t ODBCColumn::dataLength() const
{
	return _dataLength;
}


} } } // namespace Poco::Data::ODBC


#endif
