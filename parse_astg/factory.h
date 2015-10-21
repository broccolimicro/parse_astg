/*
 * factory.h
 *
 *  Created on: Aug 16, 2015
 *      Author: nbingham
 */

#include "../parse_astg/graph.h"

#ifndef factory_h
#define factory_h

namespace parse_astg
{
	parse::syntax *factory(tokenizer &tokens, void *data)
	{
		return new graph(tokens, data);
	};
}

#endif
