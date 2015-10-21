/*
 * graph.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse_ucs/variable_name.h>
#include "../parse_astg/graph.h"
#include <parse/default/instance.h>
#include <parse/default/symbol.h>
#include <parse/default/white_space.h>
#include <parse/default/new_line.h>

namespace parse_astg
{

graph::graph()
{
	debug_name = "graph";
}

graph::graph(tokenizer &tokens, void *data)
{
	debug_name = "graph";
	parse(tokens, data);
}

graph::~graph()
{
}

void graph::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(false);
	tokens.expect(".model");

	if (tokens.decrement(__FILE__, __LINE__, data))
	{
		tokens.next();

		tokens.increment(true);
		tokens.expect("\n");

		tokens.increment(true);
		tokens.expect<parse::instance>();

		if (tokens.decrement(__FILE__, __LINE__, data))
			name = tokens.next();

		if (tokens.decrement(__FILE__, __LINE__, data))
			tokens.next();
	}

	tokens.increment(true);
	tokens.expect(".end");

	tokens.increment(false);
	tokens.expect(".input");
	tokens.expect(".output");
	tokens.expect(".internal");
	tokens.expect(".dummy");
	tokens.expect(".graph");
	tokens.expect(".marking");

	while (tokens.decrement(__FILE__, __LINE__, data))
	{
		if (tokens.found(".input"))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("\n");

			tokens.increment(false);
			tokens.expect<variable_name>();

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				inputs.push_back(variable_name(tokens, data));

				tokens.increment(false);
				tokens.expect<variable_name>();
			}

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();
		}
		else if (tokens.found(".output"))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("\n");

			tokens.increment(false);
			tokens.expect<variable_name>();

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				internal.push_back(variable_name(tokens, data));

				tokens.increment(false);
				tokens.expect<variable_name>();
			}

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();
		}
		else if (tokens.found(".internal"))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("\n");

			tokens.increment(false);
			tokens.expect<variable_name>();

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				internal.push_back(variable_name(tokens, data));

				tokens.increment(false);
				tokens.expect<variable_name>();
			}

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();
		}
		else if (tokens.found(".dummy"))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("\n");

			tokens.increment(false);
			tokens.expect<variable_name>();

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				dummy.push_back(variable_name(tokens, data));

				tokens.increment(false);
				tokens.expect<variable_name>();
			}

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();
		}
		else if (tokens.found(".graph"))
		{
			tokens.next();

			tokens.increment(false);
			tokens.expect<arc>();

			tokens.increment(true);
			tokens.expect("\n");

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				arcs.push_back(arc(tokens, data));

				tokens.increment(true);
				tokens.expect("\n");

				if (tokens.decrement(__FILE__, __LINE__, data))
					tokens.next();

				tokens.increment(false);
				tokens.expect<arc>();
			}
		}
		else if (tokens.found(".marking"))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect("\n");

			tokens.increment(true);
			tokens.expect("{");

			while (tokens.decrement(__FILE__, __LINE__, data))
			{
				tokens.next();
				vector<node> nodes;

				tokens.increment(true);
				tokens.expect("}");

				tokens.increment(false);
				tokens.expect<node>();

				while (tokens.decrement(__FILE__, __LINE__, data))
				{
					nodes.push_back(node(tokens, data));

					tokens.increment(false);
					tokens.expect<node>();
				}

				if (tokens.decrement(__FILE__, __LINE__, data))
					tokens.next();

				marking.push_back(nodes);

				tokens.increment(false);
				tokens.expect("{");
			}

			if (tokens.decrement(__FILE__, __LINE__, data))
				tokens.next();
		}
	}

	tokens.syntax_end(this);
}

bool graph::is_next(tokenizer &tokens, int i, void *data)
{
	return (tokens.is_next(".model") ||
			tokens.is_next(".input") ||
			tokens.is_next(".output") ||
			tokens.is_next(".internal") ||
			tokens.is_next(".dummy") ||
			tokens.is_next(".graph") ||
			tokens.is_next(".end"));
}

void graph::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<graph>())
	{
		tokens.register_syntax<graph>();
		arc::register_syntax(tokens);
		node::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
		tokens.register_token<parse::white_space>(false);
		tokens.register_token<parse::new_line>();
	}
}

string graph::to_string(string tab) const
{
	string result = "";
	if (name != "")
		result += ".model " + name + "\n";

	if (inputs.size() > 0)
	{
		result += ".input";
		for (int i = 0; i < (int)inputs.size(); i++)
			result += " " + inputs[i].to_string(tab);
	}

	if (outputs.size() > 0)
	{
		result += ".output";
		for (int i = 0; i < (int)outputs.size(); i++)
			result += " " + outputs[i].to_string(tab);
	}

	if (internal.size() > 0)
	{
		result += ".internal";
		for (int i = 0; i < (int)internal.size(); i++)
			result += " " + internal[i].to_string(tab);
	}

	if (dummy.size() > 0)
	{
		result += ".dummy";
		for (int i = 0; i < (int)dummy.size(); i++)
			result += " " + dummy[i].to_string(tab);
	}

	result += ".graph\n";
	for (int i = 0; i < (int)arcs.size(); i++)
		result += arcs[i].to_string(tab) + "\n";

	if (marking.size() > 0)
	{
		result += ".marking";
		for (int i = 0; i < (int)marking.size(); i++)
		{
			result += " {";
			for (int j = 0; j < (int)marking[i].size(); j++)
			{
				if (j != 0)
					result += " ";

				result += marking[i][j].to_string(tab);
			}
			result += "}";
		}
		result += "\n";
	}

	result += ".end\n";
	return result;
}

parse::syntax *graph::clone() const
{
	return new graph(*this);
}

}
