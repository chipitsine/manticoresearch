//
// Copyright (c) 2008-2022, Manticore Software LTD (http://manticoresearch.com)
// Copyright (c) 2001-2016, Andrew Aksyonoff
// Copyright (c) 2008-2016, Sphinx Technologies Inc
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org
//

#pragma once

#include "sphinxstd.h"
#include "searchdaemon.h"
#include "http/http_parser.h"

using OptionsHash_t = SmallStringHash_T<CSphString>;
class AsyncNetInputBuffer_c;

class HttpRequestParser_c : public ISphNoncopyable
{
public:
	HttpRequestParser_c();
	void Reinit();
	bool ParseHeader ( ByteBlob_t tData );
	bool ProcessClientHttp ( AsyncNetInputBuffer_c& tIn, CSphVector<BYTE>& dResult );

	int ParsedBodyLength() const;
	bool Expect100() const;
	bool KeepAlive() const;
	const char* Error() const;

private:
	void ParseList ( Str_t sData );

	// callbacks
	int ParserUrl ( Str_t sData );
	int ParserHeaderField ( Str_t sData );
	int ParserHeaderValue ( Str_t sData );
	int ParserBody ( Str_t sData );
	int ParseHeaderCompleted ();
	int MessageComplete();

	void FinishParserUrl();
	void FinishParserKeyVal();

private:
	// callbacks
	static int cbParserUrl ( http_parser* pParser, const char* sAt, size_t iLen );
	static int cbParserHeaderField ( http_parser* pParser, const char* sAt, size_t iLen );
	static int cbParserHeaderValue ( http_parser* pParser, const char* sAt, size_t iLen );
	static int cbParseHeaderCompleted ( http_parser* pParser );
	static int cbParserBody ( http_parser* pParser, const char* sAt, size_t iLen );
	static int cbMessageComplete ( http_parser* pParser );

	static int cbMessageBegin ( http_parser* pParser );
	static int cbMessageStatus ( http_parser* pParser, const char* sAt, size_t iLen );

private:
	bool m_bKeepAlive = false;
	const char* m_szError = nullptr;
	CSphString m_sEndpoint;
	StringBuilder_c m_sUrl;
	StringBuilder_c m_sCurField;
	StringBuilder_c m_sCurValue;
	OptionsHash_t m_hOptions;

	http_method m_eType = HTTP_GET;
	bool m_bHeaderDone = false;
	bool m_bBodyDone = false;
	CSphVector<Str_t> m_dParsedBodies;
	int m_iParsedBodyLength;
	int m_iLastParsed = 0;

	http_parser_settings m_tParserSettings;
	http_parser m_tParser;
};

void HttpBuildReply ( CSphVector<BYTE>& dData, ESphHttpStatus eCode, Str_t sReply, bool bHtml );