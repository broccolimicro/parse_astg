#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include <parse_astg/expression.h>

namespace parse_astg
{

struct node : parse::syntax
{
	node();
	node(tokenizer &tokens, void *data = NULL);
	node(expression guard, composition assign, string id = "");
	node(string place, string id = "");
	~node();

	composition assign;
	expression guard;
	string place;
	string id;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
