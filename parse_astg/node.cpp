/*
 * node.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "../parse_astg/node.h"

#include <parse/default/instance.h>
#include <parse/default/symbol.h>
#include <parse/default/number.h>

namespace parse_astg
{

node::node()
{
	debug_name = "node";
}

node::node(tokenizer &tokens, void *data)
{
	debug_name = "node";
	parse(tokens, data);
}

node::~node()
{
}

void node::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<parse_expression::assignment>();
	tokens.expect("[");
	tokens.expect<parse::instance>();

	if (tokens.decrement(__FILE__, __LINE__, data))
	{
		if (tokens.found<parse_expression::assignment>())
		{
			assign = parse_expression::assignment(tokens, data);

			tokens.increment(false);
			tokens.expect("/");

			if (tokens.decrement(__FILE__, __LINE__, data))
			{
				tokens.next();

				tokens.increment(true);
				tokens.expect<parse::number>();

				if (tokens.decrement(__FILE__, __LINE__, data))
					id = tokens.next();
			}
		}
		else if (tokens.found("["))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("]");

			tokens.increment(true);
			tokens.expect<parse_expression::expression>();

			if (tokens.decrement(__FILE__, __LINE__, data))
				guard = parse_expression::expression(tokens, 0, data);

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();

			tokens.increment(false);
			tokens.expect("/");

			if (tokens.decrement(__FILE__, __LINE__, data))
			{
				tokens.next();

				tokens.increment(true);
				tokens.expect<parse::number>();

				if (tokens.decrement(__FILE__, __LINE__, data))
					id = tokens.next();
			}
		}
		else if (tokens.found<parse::instance>())
			place = tokens.next();
	}

	tokens.syntax_end(this);
}

bool node::is_next(tokenizer &tokens, int i, void *data)
{
	return (tokens.is_next("[", i) || parse_expression::assignment::is_next(tokens, i, data) || tokens.is_next<parse::instance>(i));
}

void node::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<node>())
	{
		tokens.register_syntax<node>();
		parse_expression::assignment::register_syntax(tokens);
		parse_expression::expression::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string node::to_string(string tab) const
{
	string result = "";
	if (assign.valid)
		result += assign.to_string(tab);
	else if (guard.valid)
		result += "[" + guard.to_string(tab) + "]";
	else
		result += place;

	if (id != "")
		result += "/" + id;

	return result;
}

parse::syntax *node::clone() const
{
	return new node(*this);
}

}
