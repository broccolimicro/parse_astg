/*
 * arc.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "../parse_astg/arc.h"

#include <parse/default/instance.h>
#include <parse/default/symbol.h>

namespace parse_astg
{

arc::arc()
{
	debug_name = "arc";
}

arc::arc(tokenizer &tokens, void *data)
{
	debug_name = "arc";
	parse(tokens, data);
}

arc::arc(node n0, node n1)
{
	debug_name = "src";
	nodes.push_back(n0);
	nodes.push_back(n1);
}

arc::~arc()
{
}

void arc::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect<node>();

	while (tokens.decrement(__FILE__, __LINE__, data)) {
		nodes.push_back(node(tokens, data));

		tokens.increment(false);
		tokens.expect<node>();
	}

	tokens.syntax_end(this);
}

bool arc::is_next(tokenizer &tokens, int i, void *data)
{
	return node::is_next(tokens, i, data);
}

void arc::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<arc>())
	{
		tokens.register_syntax<arc>();
		node::register_syntax(tokens);
	}
}

string arc::to_string(string tab) const
{
	string result = "";
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		if (i != 0)
			result += " ";

		result += nodes[i].to_string(tab);
	}

	return result;
}

parse::syntax *arc::clone() const
{
	return new arc(*this);
}

}
