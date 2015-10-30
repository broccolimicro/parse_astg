/*
 * graph.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/syntax.h>
#include <parse_ucs/variable_name.h>
#include "../parse_astg/arc.h"
#include "../parse_astg/node.h"

#ifndef parse_astg_graph_h
#define parse_astg_graph_h

namespace parse_astg
{

using parse_ucs::variable_name;

struct graph : parse::syntax
{
	graph();
	graph(tokenizer &tokens, void *data = NULL);
	~graph();

	string name;
	vector<variable_name> inputs;
	vector<variable_name> outputs;
	vector<variable_name> internal;
	vector<string> dummy;
	vector<pair<node, parse_expression::expression> > predicate;
	vector<pair<node, parse_expression::expression> > effective;
	vector<arc> arcs;
	vector<pair<parse_expression::expression, vector<node> > > marking;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
