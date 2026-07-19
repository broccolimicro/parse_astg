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
	graph(tokenizer &tokens, std::any data=std::any());
	~graph();

	string name;
	vector<lvalue> inputs;
	vector<lvalue> outputs;
	vector<lvalue> internal;
	vector<pair<node, expression> > predicate;
	vector<pair<node, expression> > effective;
	vector<arc> arcs;
	vector<pair<composition, vector<node> > > marking;
	vector<node> arbiter;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

