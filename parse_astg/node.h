/*
 * node.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>
#include <parse_expression/assignment.h>
#include <parse_expression/expression.h>

#ifndef parse_astg_node_h
#define parse_astg_node_h

namespace parse_astg
{

struct node : parse::syntax
{
	node();
	node(tokenizer &tokens, void *data = NULL);
	~node();

	parse_expression::assignment assign;
	parse_expression::expression guard;
	string place;
	string id;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
