/*
 * arc.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>
#include "../parse_astg/node.h"

#ifndef parse_astg_arc_h
#define parse_astg_arc_h

namespace parse_astg
{

struct arc : parse::syntax
{
	arc();
	arc(tokenizer &tokens, void *data = NULL);
	arc(node n0, node n1);
	~arc();

	vector<node> nodes;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
