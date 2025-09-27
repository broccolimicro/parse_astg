#pragma once

#include <parse/syntax.h>
#include <parse_astg/arc.h>
#include <parse_astg/node.h>
#include <parse_astg/expression.h>

namespace parse_astg
{

struct graph : parse::syntax
{
	graph();
	graph(tokenizer &tokens, void *data = NULL);
	~graph();

	string name;
	vector<expression> inputs;
	vector<expression> outputs;
	vector<expression> internal;
	vector<pair<node, expression> > predicate;
	vector<pair<node, expression> > effective;
	vector<arc> arcs;
	vector<pair<composition, vector<node> > > marking;
	vector<node> arbiter;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

