#pragma once

#include <parse/syntax.h>
#include "../parse_astg/arc.h"
#include "../parse_astg/node.h"

namespace parse_astg
{

struct graph : parse::syntax
{
	graph();
	graph(tokenizer &tokens, void *data = NULL);
	~graph();

	string name;
	vector<parse_expression::expression> inputs;
	vector<parse_expression::expression> outputs;
	vector<parse_expression::expression> internal;
	vector<pair<node, parse_expression::expression> > predicate;
	vector<pair<node, parse_expression::expression> > effective;
	vector<arc> arcs;
	vector<pair<parse_expression::composition, vector<node> > > marking;
	vector<node> arbiter;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

