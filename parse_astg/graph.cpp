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
#include <parse/default/number.h>
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

	tokens.increment(true);
	tokens.expect(".");
	tokens.expect("\n");

	bool done = false;
	while (!done && tokens.decrement(__FILE__, __LINE__, data))
	{
		if (tokens.next() == ".")
		{
			tokens.increment(false);
			tokens.expect("model");
			tokens.expect("input");
			tokens.expect("output");
			tokens.expect("internal");
			tokens.expect("dummy");
			tokens.expect("predicate");
			tokens.expect("effective");
			tokens.expect("graph");
			tokens.expect("marking");
			tokens.expect("end");

			if (tokens.decrement(__FILE__, __LINE__, data))
			{
				if (tokens.found("model"))
				{
					tokens.next();

					tokens.increment(true);
					tokens.expect<parse::instance>();

					if (tokens.decrement(__FILE__, __LINE__, data))
						name = tokens.next();
				}
				if (tokens.found("input"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<variable_name>();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						inputs.push_back(variable_name(tokens, data));

						tokens.increment(false);
						tokens.expect<variable_name>();
					}
				}
				else if (tokens.found("output"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<variable_name>();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						internal.push_back(variable_name(tokens, data));

						tokens.increment(false);
						tokens.expect<variable_name>();
					}
				}
				else if (tokens.found("internal"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<variable_name>();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						internal.push_back(variable_name(tokens, data));

						tokens.increment(false);
						tokens.expect<variable_name>();
					}
				}
				else if (tokens.found("dummy"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<parse::instance>();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						dummy.push_back(tokens.next());

						tokens.increment(false);
						tokens.expect("/");

						if (tokens.decrement(__FILE__, __LINE__, data))
						{
							tokens.next();

							tokens.increment(true);
							tokens.expect<parse::number>();

							if (tokens.decrement(__FILE__, __LINE__, data))
								dummy.back() += "/" + tokens.next();
						}

						tokens.increment(false);
						tokens.expect<parse::instance>();
					}
				}
				else if (tokens.found("predicate"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<parse::instance>();

					tokens.increment(true);
					tokens.expect("\n");

					if (tokens.decrement(__FILE__, __LINE__, data))
						tokens.next();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						predicate.push_back(pair<node, parse_expression::expression>(node(tokens, dummy, data), parse_expression::expression()));

						tokens.increment(false);
						tokens.expect<parse::instance>();

						tokens.increment(true);
						tokens.expect("\n");

						tokens.increment(true);
						tokens.expect<parse_expression::expression>();

						if (tokens.decrement(__FILE__, __LINE__, data))
							predicate.back().second = parse_expression::expression(tokens, 0, data);

						if (tokens.decrement(__FILE__, __LINE__, data))
							tokens.next();
					}
				}
				else if (tokens.found("effective"))
				{
					tokens.next();

					tokens.increment(false);
					tokens.expect<parse::instance>();

					tokens.increment(true);
					tokens.expect("\n");

					if (tokens.decrement(__FILE__, __LINE__, data))
						tokens.next();

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						effective.push_back(pair<node, parse_expression::expression>(node(tokens, dummy, data), parse_expression::expression()));

						tokens.increment(false);
						tokens.expect<parse::instance>();

						tokens.increment(true);
						tokens.expect("\n");

						tokens.increment(true);
						tokens.expect<parse_expression::expression>();

						if (tokens.decrement(__FILE__, __LINE__, data))
							effective.back().second = parse_expression::expression(tokens, 0, data);

						if (tokens.decrement(__FILE__, __LINE__, data))
							tokens.next();
					}
				}
				else if (tokens.found("graph"))
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
						arcs.push_back(arc(tokens, dummy, data));

						tokens.increment(true);
						tokens.expect("\n");

						if (tokens.decrement(__FILE__, __LINE__, data))
							tokens.next();

						tokens.increment(false);
						tokens.expect<arc>();
					}
				}
				else if (tokens.found("marking"))
				{
					tokens.next();

					tokens.increment(true);
					tokens.expect("{");

					while (tokens.decrement(__FILE__, __LINE__, data))
					{
						tokens.next();

						tokens.increment(true);
						tokens.expect("}");

						tokens.increment(false);
						tokens.expect("[");

						pair<parse_expression::expression, vector<node> > mark;
						if (tokens.decrement(__FILE__, __LINE__, data))
						{
							tokens.next();

							tokens.increment(true);
							tokens.expect("]");

							tokens.increment(true);
							tokens.expect<parse_expression::expression>();

							if (tokens.decrement(__FILE__, __LINE__, data))
								mark.first = parse_expression::expression(tokens, 0, data);

							if (tokens.decrement(__FILE__, __LINE__, data))
								tokens.next();
						}

						tokens.increment(false);
						tokens.expect<node>();

						while (tokens.decrement(__FILE__, __LINE__, data))
						{
							mark.second.push_back(node(tokens, dummy, data));

							tokens.increment(false);
							tokens.expect<node>();
						}

						if (tokens.decrement(__FILE__, __LINE__, data))
							tokens.next();

						marking.push_back(mark);

						tokens.increment(false);
						tokens.expect("{");
					}
				}
				else if (tokens.found("end"))
				{
					tokens.next();
					done = true;
				}
			}
			else while (tokens.peek(1) != "." && tokens.peek(1) != "")
				tokens.next();
		}

		if (!done)
		{
			tokens.increment(true);
			tokens.expect(".");
			tokens.expect("\n");
		}
	}

	tokens.syntax_end(this);
}

bool graph::is_next(tokenizer &tokens, int i, void *data)
{
	while (tokens.is_next("\n", i))
		i++;

	return tokens.is_next(".", i) &&
			(tokens.is_next("model", i+1) ||
			tokens.is_next("input", i+1) ||
			tokens.is_next("output", i+1) ||
			tokens.is_next("internal", i+1) ||
			tokens.is_next("dummy", i+1) ||
			tokens.is_next("predicate", i+1) ||
			tokens.is_next("effective", i+1) ||
			tokens.is_next("graph", i+1) ||
			tokens.is_next("end", i+1));
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
		tokens.register_token<parse::number>();
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
		result += "\n";
	}

	if (outputs.size() > 0)
	{
		result += ".output";
		for (int i = 0; i < (int)outputs.size(); i++)
			result += " " + outputs[i].to_string(tab);
		result += "\n";
	}

	if (internal.size() > 0)
	{
		result += ".internal";
		for (int i = 0; i < (int)internal.size(); i++)
			result += " " + internal[i].to_string(tab);
		result += "\n";
	}

	if (dummy.size() > 0)
	{
		result += ".dummy";
		for (int i = 0; i < (int)dummy.size(); i++)
			result += " " + dummy[i];
		result += "\n";
	}

	if (predicate.size() > 0)
	{
		result += ".predicate\n";
		for (int i = 0; i < (int)predicate.size(); i++)
			result += predicate[i].first.to_string() + " " + predicate[i].second.to_string() + "\n";
	}

	if (effective.size() > 0)
	{
		result += ".effective\n";
		for (int i = 0; i < (int)effective.size(); i++)
			result += effective[i].first.to_string() + " " + effective[i].second.to_string() + "\n";
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
			if (marking[i].first.valid)
				result += "[" + marking[i].first.to_string(tab) + "] ";

			for (int j = 0; j < (int)marking[i].second.size(); j++)
			{
				if (j != 0)
					result += " ";

				result += marking[i].second[j].to_string(tab);
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
